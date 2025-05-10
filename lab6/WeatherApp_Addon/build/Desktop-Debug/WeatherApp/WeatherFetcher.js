var apiKey = "53f2e1b43a53b9ec86018cdf1e816cfa"
var currentWeatherUrl = "https://api.openweathermap.org/data/2.5/weather"
var forecastUrl = "https://api.openweathermap.org/data/2.5/forecast"

function fetchWeather(city) {
    if (!city) {
        errorMessage.text = qsTr("Введите город")
        errorMessage.visible = true
        return
    }

    var unit = appSettings.tempUnit === "metric" ? "metric" : "imperial"
    var currentXhr = new XMLHttpRequest()
    var currentUrl = currentWeatherUrl + "?q=" + encodeURIComponent(city) +
                        "&appid=" + apiKey + "&units=" + unit + "&lang=ru"

    currentXhr.onreadystatechange = function() {
        if (currentXhr.readyState === XMLHttpRequest.DONE) {
            if (currentXhr.status === 200) {
                var response = JSON.parse(currentXhr.responseText)
                updateCurrentWeather(response)
                errorMessage.visible = false
                weatherBlock.opacity = 1.0
            } else {
                showError(qsTr("Ошибка: проверьте название города"))
            }
        }
    }

    var forecastXhr = new XMLHttpRequest()
    var forecastUrlWithParams = forecastUrl + "?q=" + encodeURIComponent(city) +
                              "&appid=" + apiKey + "&units=" + unit + "&lang=ru&cnt=40"

    forecastXhr.onreadystatechange = function() {
        if (forecastXhr.readyState === XMLHttpRequest.DONE) {
            if (forecastXhr.status === 200) {
                var forecastResponse = JSON.parse(forecastXhr.responseText)
                updateForecast(forecastResponse)
            }
        }
    }

    currentXhr.open("GET", currentUrl)
    currentXhr.send()

    forecastXhr.open("GET", forecastUrlWithParams)
    forecastXhr.send()
}

function updateCurrentWeather(data) {
    cityName.text = qsTr("Город: ") + data.name
    var unitSymbol = appSettings.tempUnit === "metric" ? "°C" : "°F"
    temperature.text = qsTr("Температура: ") + data.main.temp + unitSymbol
    description.text = qsTr("Описание: ") + data.weather[0].description
    humidity.text = qsTr("Влажность: ") + data.main.humidity + "%"
    wind.text = qsTr("Ветер: ") + data.wind.speed + " м/с"
}

function updateForecast(data) {
    forecastModel.clear()
    hourlyModel.clear()

    var hourly = processHourlyData(data)
    for (var i = 0; i < hourly.length; i++) {
        hourlyModel.append(hourly[i])
    }

    var unitSymbol = appSettings.tempUnit === "metric" ? "°C" : "°F"
    for (var i = 0; i < data.list.length; i++) {
        var item = data.list[i]
        var date = new Date(item.dt * 1000)
        if (date.getHours() === 12) {
            forecastModel.append({
                date: Qt.formatDate(date, "dd.MM"),
                temp: item.main.temp + unitSymbol,
                icon: getWeatherIcon(item.weather[0].icon),
                description: item.weather[0].description
            })
        }
    }
}

function getWeatherIcon(iconCode) {
    return "http://openweathermap.org/img/wn/" + iconCode + ".png"
}

function showError(message) {
    errorMessage.text = message
    errorMessage.visible = true
    weatherBlock.opacity = 0.0
    forecastModel.clear()
}

function processHourlyData(data) {
    var hourlyData = []
    var now = new Date()
    var currentHour = now.getHours()

    for (var i = 0; i < 8; i++) {
        var item = data.list[i]
        var date = new Date(item.dt * 1000)
        hourlyData.push({
            time: Qt.formatTime(date, "hh:mm"),
            temp: item.main.temp,
            humidity: item.main.humidity,
            wind: item.wind.speed,
            icon: getWeatherIcon(item.weather[0].icon)
        })
    }
    return hourlyData
}
