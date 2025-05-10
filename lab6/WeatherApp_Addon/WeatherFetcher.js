var apiKey = "53f2e1b43a53b9ec86018cdf1e816cfa"
var baseUrl = "https://api.openweathermap.org/data/2.5/weather"
var forecastUrl = "https://api.openweathermap.org/data/2.5/forecast"
var units = "metric"

function setUnits(newUnits) {
    units = newUnits
}

function fetchWeather(city) {
    if (!city) {
        errorMessage.text = qsTr("Введите город")
        errorMessage.visible = true
        return
    }

    var xhr = new XMLHttpRequest()
    var url = baseUrl + "?q=" + encodeURIComponent(city) +
              "&appid=" + apiKey + "&units=" + units + "&lang=ru"

    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE) {
            if (xhr.status === 200) {
                var response = JSON.parse(xhr.responseText)
                cityName.text = qsTr("Город: ") + response.name
                temperature.text = qsTr("Температура: ") + response.main.temp +
                                   (units === "metric" ? "°C" : "°F")
                description.text = qsTr("Описание: ") + response.weather[0].description
                humidity.text = qsTr("Влажность: ") + response.main.humidity + "%"
                wind.text = qsTr("Ветер: ") + response.wind.speed + " м/с"
                errorMessage.visible = false
                weatherBlock.opacity = 1.0
            } else {
                errorMessage.text = qsTr("Ошибка: проверьте название города")
                errorMessage.visible = true
                weatherBlock.opacity = 0.0
            }
        }
    }

    xhr.open("GET", url)
    xhr.send()
}

function fetchForecast(city) {
    if (!city) {
        errorMessage.text = qsTr("Введите город")
        errorMessage.visible = true
        return
    }

    var xhr = new XMLHttpRequest()
    var url = forecastUrl + "?q=" + encodeURIComponent(city) +
              "&appid=" + apiKey + "&units=metric&lang=ru"

    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE) {
            if (xhr.status === 200) {
                var response = JSON.parse(xhr.responseText)
                forecastModel.clear()
                for (var i = 0; i < response.list.length; i += 8) { // 8 data points per day
                    var item = response.list[i]
                    forecastModel.append({
                        date: item.dt_txt.split(" ")[0],
                        temp: item.main.temp,
                        description: item.weather[0].description
                    })
                }
                errorMessage.visible = false
            } else {
                errorMessage.text = qsTr("Ошибка: проверьте название города")
                errorMessage.visible = true
            }
        }
    }
    for (var i = 0; i < response.list.length; i++) {
        var item = response.list[i]
        tempSeries.append(i, item.main.temp)
    }
    xhr.open("GET", url)
    xhr.send()
}

function fetchWeather(city) {
    if (!city) {
        errorMessage.text = qsTr("Введите город")
        errorMessage.visible = true
        return
    }

    var xhr = new XMLHttpRequest()
    var url = baseUrl + "?q=" + encodeURIComponent(city) +
              "&appid=" + apiKey + "&units=metric&lang=ru"

    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE) {
            if (xhr.status === 200) {
                var response = JSON.parse(xhr.responseText)
                cityName.text = qsTr("Город: ") + response.name
                temperature.text = qsTr("Температура: ") + response.main.temp + "°C"
                description.text = qsTr("Описание: ") + response.weather[0].description
                humidity.text = qsTr("Влажность: ") + response.main.humidity + "%"
                wind.text = qsTr("Ветер: ") + response.wind.speed + " м/с"
                errorMessage.visible = false
                weatherBlock.opacity = 1.0
            } else {
                errorMessage.text = qsTr("Ошибка: проверьте название города")
                errorMessage.visible = true
                weatherBlock.opacity = 0.0
            }
        }
    }

    xhr.open("GET", url)
    xhr.send()
}

