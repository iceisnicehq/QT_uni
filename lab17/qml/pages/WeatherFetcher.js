var apiKey = "53f2e1b43a53b9ec86018cdf1e816cfa";
var currentWeatherUrl = "https://api.openweathermap.org/data/2.5/weather";
var forecastUrl = "https://api.openweathermap.org/data/2.5/forecast";

function getUnits(units) {
    return {
        temp: (units === "metric") ? "°C" : "°F",
        speed: (units === "metric") ? " м/с" : " миль/ч"
    };
}

function fetchWeather(city, units) {
    if (!city) {
        showError(qsTr("Введите город"));
        return;
    }

    var currentXhr = new XMLHttpRequest();
    var currentUrl = currentWeatherUrl + "?q=" + encodeURIComponent(city) +
                     "&appid=" + apiKey + "&units=" + units + "&lang=ru";

    currentXhr.onreadystatechange = function() {
        if (currentXhr.readyState === XMLHttpRequest.DONE) {
            if (currentXhr.status === 200) {
                console.log("Raw API response:", currentXhr.responseText);
                var data = JSON.parse(currentXhr.responseText);
                updateCurrentWeather(data, units, city);
                errorMessage.visible = false;
                weatherBlock.opacity = 1.0;
                forecastBlock.opacity = 1.0;
            } else {
                showError(qsTr("Ошибка: проверьте название города"));
            }
        }
    };

    var forecastXhr = new XMLHttpRequest();
    var forecastUrlWithParams = forecastUrl + "?q=" + encodeURIComponent(city) +
                                "&appid=" + apiKey + "&units=" + units + "&lang=ru&cnt=40";

    forecastXhr.onreadystatechange = function() {
        if (forecastXhr.readyState === XMLHttpRequest.DONE) {
            if (forecastXhr.status === 200) {
                var data = JSON.parse(forecastXhr.responseText);
                updateHourly(data, units);
                updateForecast(data, units);
            } else {
                console.log("Forecast fetch error: " + forecastXhr.statusText);
            }
        }
    };

    currentXhr.open("GET", currentUrl);
    currentXhr.send();
    forecastXhr.open("GET", forecastUrlWithParams);
    forecastXhr.send();
}

function fetchWeatherData(city, units, callback) {
    if (!city) return;
    var xhr = new XMLHttpRequest();
    var url = currentWeatherUrl + "?q=" + encodeURIComponent(city) +
              "&appid=" + apiKey + "&units=" + units + "&lang=ru";
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.DONE) {
            if (xhr.status === 200) {
                var data = JSON.parse(xhr.responseText);
                callback(data);
            } else {
                callback(null);
            }
        }
    };
    xhr.open("GET", url);
    xhr.send();
}

function updateCurrentWeather(data, units, city) {
    var symbols = getUnits(units);
    root.mainTempCelsius = Math.round(units === "metric" ? data.main.temp : (data.main.temp - 32) * 5 / 9);
    temperature.text = Math.round(data.main.temp) + "° ";
    weatherIcon.source = mapIcon(data.weather[0].icon);
    description.text = data.weather[0].description;
    feelsLike.text = qsTr("Ощущается как: ") + Math.round(data.main.feels_like) + "°";
    highLow.text = qsTr("Макс.: ") + Math.round(data.main.temp_max) + "° • " +
                   qsTr("Мин.: ") + Math.round(data.main.temp_min) + "°";
    wind.text = data.wind.speed + symbols.speed;
    humidity.text = data.main.humidity + " %";
    pressure.text = data.main.pressure + " гПа";
    sunriseLabel.text = Qt.formatTime(new Date(data.sys.sunrise * 1000), "hh:mm");
    sunsetLabel.text = Qt.formatTime(new Date(data.sys.sunset * 1000), "hh:mm");
    if (root.lastFrogCity !== city) {
        root.frogImage = getRandomFrogImage(data.weather[0].icon);
        root.lastFrogCity = city;
    }
}

function updateHourly(data, units) {
    hourlyModel.clear();
    var symbols = getUnits(units);

    var now = new Date();
    var nowTimestamp = now.getTime();

    var endOfTomorrow = new Date(now);
    endOfTomorrow.setDate(now.getDate() + 4);
    endOfTomorrow.setHours(23, 59, 59, 999);
    var endTimestamp = endOfTomorrow.getTime();

    data.list.forEach(function(item) {
        var itemTimestamp = item.dt * 1000;
        if (itemTimestamp < nowTimestamp || itemTimestamp > endTimestamp) return;

        var dt = new Date(itemTimestamp);
        var hourText = (dt.getHours() < 10 ? "0" : "") + dt.getHours() + ":00";
        var dateText = (dt.getDate() < 10 ? "0" : "") + dt.getDate() + "." +
                       ((dt.getMonth() + 1) < 10 ? "0" : "") + (dt.getMonth() + 1);

        hourlyModel.append({
            hour: hourText,
            date: dateText,
            temp: Math.round(item.main.temp) + symbols.temp,
            icon: mapIcon(item.weather[0].icon)
        });
    });
}


function updateForecast(data, units) {
    forecastModel.clear();
    var symbols = getUnits(units);
    var today = new Date().getDate();

    var daysRu = ["вс","пн","вт","ср","чт","пт","сб"];

    var byDay = {};
    data.list.forEach(function(entry) {
        var dt = new Date(entry.dt * 1000);
        var day = dt.getDate();
        if (day === today) return;

        var dow = daysRu[ dt.getDay() ];
        var ddmmyy = Qt.formatDate(dt, "dd.MM");
        var label = dow + ", " + ddmmyy;

        if (!byDay[label]) byDay[label] = [];
        byDay[label].push({ dateObj: dt, entry: entry });
    });

    var daily = [];
    Object.keys(byDay).forEach(function(label) {
        var list = byDay[label];

        var tempMax = Math.max.apply(null, list.map(function(item) {
            return item.entry.main.temp_max;
        }));
        var tempMin = Math.min.apply(null, list.map(function(item) {
            return item.entry.main.temp_min;
        }));

        var best = list.reduce(function(a, b) {
            return (Math.abs(a.dateObj.getHours() - 12) <= Math.abs(b.dateObj.getHours() - 12))
                   ? a : b;
        });
        var e = best.entry;

        daily.push({
            date:   label,
            dateObj: best.dateObj,
            tempMax: Math.round(tempMax) + "°",
            tempMin: Math.round(tempMin) + "°",
            humidity: e.main.humidity,
            icon:    mapIcon(e.weather[0].icon)
        });
    });

    daily.sort(function(a, b) { return a.dateObj - b.dateObj; });
    for (var i = 0; i < Math.min(5, daily.length); i++) {
        forecastModel.append({
            date:    daily[i].date,
            tempMax: daily[i].tempMax,
            tempMin: daily[i].tempMin,
            humidity: daily[i].humidity,
            icon:    daily[i].icon
        });
    }
}

function showError(message) {
    errorMessage.text = message;
    errorMessage.visible = true;
    weatherBlock.opacity = 0.0;
    forecastBlock.opacity = 0.0;
    forecastModel.clear();
    hourlyModel.clear();
}

function saveLastCity(city) {
    var db = LocalStorage.openDatabaseSync("WeatherApp", "1.0", "Weather DB", 10000);
    db.transaction(function(tx) {
        tx.executeSql('CREATE TABLE IF NOT EXISTS settings(key TEXT UNIQUE, value TEXT)');
        tx.executeSql('INSERT OR REPLACE INTO settings VALUES(?, ?)', ["lastCity", city]);
    });
}

function loadLastCity() {
    var db = LocalStorage.openDatabaseSync("WeatherApp", "1.0", "Weather DB", 10000);
    var city = "Moscow";
    db.transaction(function(tx) {
        tx.executeSql('CREATE TABLE IF NOT EXISTS settings(key TEXT UNIQUE, value TEXT)');
        var rs = tx.executeSql('SELECT value FROM settings WHERE key=?', ["lastCity"]);
        if (rs.rows.length > 0) city = rs.rows.item(0).value;
    });
    return city;
}

function mapIcon(code) {
    var map = {
        "01d": "../icons/weather_icons/clear_day.svg",
        "01n": "../icons/weather_icons/clear_night.svg",
        "02d": "../icons/weather_icons/mostly_clear_day.svg",
        "02n": "../icons/weather_icons/mostly_clear_night.svg",
        "03d": "../icons/weather_icons/partly_cloudy_day.svg",
        "03n": "../icons/weather_icons/partly_cloudy_night.svg",
        "04d": "../icons/weather_icons/mostly_cloudy_day.svg",
        "04n": "../icons/weather_icons/mostly_cloudy_night.svg",
        "09d": "../icons/weather_icons/scattered_showers_day.svg",
        "09n": "../icons/weather_icons/scattered_showers_night.svg",
        "10d": "../icons/weather_icons/showers_rain.svg",
        "10n": "../icons/weather_icons/showers_rain.svg",
        "11d": "../icons/weather_icons/strong_thunderstorms.svg",
        "11n": "../icons/weather_icons/strong_thunderstorms.svg",
        "13d": "../icons/weather_icons/snow_with_cloudy_light.svg",
        "13n": "../icons/weather_icons/snow_with_cloudy_dark.svg",
        "50d": "../icons/weather_icons/haze_fog_dust_smoke.svg",
        "50n": "../icons/weather_icons/haze_fog_dust_smoke.svg"
    };
    return map[code] || "../icons/weather_icons/clear_day.svg";
}

function getBgColor(temp) {

    if (temp <= 0) return "#1a237e";
    if (temp >= 30) return "#ffb300";
    var ratio = temp / 30.0;

    var r = Math.round(26 + (255-26)*ratio);
    var g = Math.round(35 + (179-35)*ratio);
    var b = Math.round(126 + (0-126)*ratio);
    return Qt.rgba(r/255, g/255, b/255, 1.0);
}

function getBgColor2(temp) {

    if (temp <= 0) return "#0d133d";
    if (temp >= 30) return "#7c4700";
    var ratio = temp / 30.0;
    var r = Math.round(13 + (124-13)*ratio);
    var g = Math.round(19 + (71-19)*ratio);
    var b = Math.round(61 + (0-61)*ratio);
    return Qt.rgba(r/255, g/255, b/255, 1.0);
}

function getRandomFrogImage(code) {
    var frogImages = {
        "01d": [
            "../icons/frog/01-sunny-beach-reading.png",
            "../icons/frog/01-sunny-beach-sandcastle.png",
            "../icons/frog/01-sunny-beach-sunscreen.png",
            "../icons/frog/01-sunny-citypark-sunbathing.png",
            "../icons/frog/01-sunny-field-kite.png",
            "../icons/frog/01-sunny-hills-sunbathing.png",
            "../icons/frog/01-sunny-home-laundry.png",
            "../icons/frog/01-sunny-orchard-picking.png",
            "../icons/frog/01-sunny-rooftop-pinacolada.png"
        ],
        "03d": [
            "../icons/frog/03-partly-cloudy-day-beach-shells.png",
            "../icons/frog/03-partly-cloudy-day-citypark-ukelele.png",
            "../icons/frog/03-partly-cloudy-day-creek-feet.png",
            "../icons/frog/03-partly-cloudy-day-field-biking.png",
            "../icons/frog/03-partly-cloudy-day-field-hiking.png",
            "../icons/frog/03-partly-cloudy-day-hills-painting.png",
            "../icons/frog/03-partly-cloudy-day-hills-reading.png",
            "../icons/frog/03-partly-cloudy-day-home-flowers.png",
            "../icons/frog/03-partly-cloudy-day-orchard-butterflies.png",
            "../icons/frog/03-partly-cloudy-day-orchard-treeswing.png"
        ],
        "04d": [
            "../icons/frog/04-mostly-cloudy-day-beach-shells.png",
            "../icons/frog/04-mostly-cloudy-day-citypark-ukelele.png",
            "../icons/frog/04-mostly-cloudy-day-creek-feet.png",
            "../icons/frog/04-mostly-cloudy-day-field-biking.png",
            "../icons/frog/04-mostly-cloudy-day-field-hiking.png",
            "../icons/frog/04-mostly-cloudy-day-hills-painting.png",
            "../icons/frog/04-mostly-cloudy-day-hills-reading.png",
            "../icons/frog/04-mostly-cloudy-day-home-flowers.png",
            "../icons/frog/04-mostly-cloudy-day-orchard-butterflies.png",
            "../icons/frog/04-mostly-cloudy-day-orchard-treeswing.png"
        ],
        "09d": [
            "../icons/frog/10-drizzle-creek-leaf.png",
            "../icons/frog/10-drizzle-field-leaf.png",
            "../icons/frog/10-drizzle-hills-umbrella.png",
            "../icons/frog/10-drizzle-home-laundry.png",
            "../icons/frog/10-drizzle-orchard-reading.png"
        ],
        "10d": [
            "../icons/frog/11-rain-creek-leaf.png",
            "../icons/frog/11-rain-hills-umbrella.png",
            "../icons/frog/11-rain-home-inside.png",
            "../icons/frog/11-rain-home-laundry.png"
        ],
        "13d": [
            "../icons/frog/13-flurries-citypark-snowman.png",
            "../icons/frog/13-flurries-creek-iceskating.png"
        ],
        "50d": [
            "../icons/frog/26-haze-fog-dust-smoke-bridge.png",
            "../icons/frog/26-haze-fog-dust-smoke-busstop-waiting.png",
            "../icons/frog/26-haze-fog-dust-smoke-field-lantern.png",
            "../icons/frog/26-haze-fog-dust-smoke-fruit-stand.png",
            "../icons/frog/26-haze-fog-dust-smoke-hills-cocoa.png",
            "../icons/frog/26-haze-fog-dust-smoke-mountain.png",
            "../icons/frog/26-haze-fog-dust-smoke-pier.png",
            "../icons/frog/26-haze-fog-dust-smoke-rooftop.png"
        ]

    };
    var list = frogImages[code] || [];
    if (list.length === 0) return "";
    var idx = Math.floor(Math.random() * list.length);
    return list[idx];
}
