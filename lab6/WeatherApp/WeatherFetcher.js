var apiKey = "53f2e1b43a53b9ec86018cdf1e816cfa"
var baseUrl = "https://api.openweathermap.org/data/2.5/weather"

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

