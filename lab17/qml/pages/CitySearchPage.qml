import QtQuick 2.6
import Sailfish.Silica 1.0
import QtQuick.LocalStorage 2.0
import "WeatherFetcher.js" as WeatherFetcher

Page {
    id: citySearchPage
    signal citySelected(string cityName)
    property var lastSearches: []
    property var favoriteCities: []
    property var cityWeatherCache: ({}) // { cityName: {icon, temp, desc} }

    Rectangle {
        anchors.fill: parent
        z: -1
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#121C42" }
            GradientStop { position: 1.0; color: "#7A4E5B" }
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge
            anchors.top: parent.top
            anchors.margins: Theme.paddingLarge

            Label {
                text: qsTr("Последние города")
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.secondaryColor
                visible: lastSearches.length > 0
            }

            Repeater {
                model: lastSearches
                delegate: Rectangle {
                    width: parent.width
                    height: 70
                    radius: 12
                    color: Qt.rgba(1, 1, 1, 0.10)
                    border.color: Theme.primaryColor
                    border.width: 1
                    anchors.horizontalCenter: parent.horizontalCenter

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            citySelected(modelData)
                            pageStack.pop()
                        }
                    }

                    Row {
                        anchors.fill: parent
                        anchors.margins: Theme.paddingMedium
                        spacing: Theme.paddingMedium

                        Image {
                            source: cityWeatherCache[modelData] ? cityWeatherCache[modelData].icon : "../icons/weather_icons/clear_day.svg"
                            width: 40
                            height: 40
                            fillMode: Image.PreserveAspectFit
                        }
                        Column {
                            spacing: 2
                            Label {
                                text: modelData
                                font.pixelSize: Theme.fontSizeMedium
                                font.bold: true
                                color: Theme.primaryColor
                            }
                            Label {
                                text: cityWeatherCache[modelData]
                                    ? cityWeatherCache[modelData].temp + "  " + cityWeatherCache[modelData].desc
                                    : "-"
                                font.pixelSize: Theme.fontSizeSmall
                                color: Theme.secondaryColor
                            }
                        }
                    }
                }
            }

            Label {
                text: qsTr("Избранные города")
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.secondaryColor
                visible: favoriteCities.length > 0
                topPadding: Theme.paddingLarge
            }

            Repeater {
                model: favoriteCities
                delegate: Rectangle {
                    width: parent.width
                    height: 70
                    radius: 12
                    color: Qt.rgba(1, 1, 1, 0.10)
                    border.color: Theme.secondaryColor
                    border.width: 1
                    anchors.horizontalCenter: parent.horizontalCenter

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            citySelected(modelData.name)
                            pageStack.pop()
                        }
                    }

                    Row {
                        anchors.fill: parent
                        anchors.margins: Theme.paddingMedium
                        spacing: Theme.paddingMedium

                        Image {
                            source: cityWeatherCache[modelData.name] ? cityWeatherCache[modelData.name].icon : "../icons/weather_icons/clear_day.svg"
                            width: 40
                            height: 40
                            fillMode: Image.PreserveAspectFit
                        }
                        Column {
                            spacing: 2
                            Label {
                                text: modelData.name
                                font.pixelSize: Theme.fontSizeMedium
                                font.bold: true
                                color: Theme.primaryColor
                            }
                            Label {
                                text: cityWeatherCache[modelData.name]
                                    ? cityWeatherCache[modelData.name].temp + "  " + cityWeatherCache[modelData.name].desc
                                    : "-"
                                font.pixelSize: Theme.fontSizeSmall
                                color: Theme.secondaryColor
                            }
                        }
                    }
                }
            }
        }
    }

    // Storage and Weather Fetch Logic
    function loadLastSearches() {
        var db = LocalStorage.openDatabaseSync("WeatherApp", "1.0", "Weather DB", 10000);
        var arr = [];
        db.transaction(function(tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS last_searches(city TEXT UNIQUE, ts INTEGER)');
            var rs = tx.executeSql('SELECT city FROM last_searches ORDER BY ts DESC LIMIT 3');
            for (var i = 0; i < rs.rows.length; i++)
                arr.push(rs.rows.item(i).city);
        });
        lastSearches = arr;
    }

    function fetchWeatherForCities(cities) {
        for (var i = 0; i < cities.length; ++i) {
            let city = cities[i];
            WeatherFetcher.fetchWeatherData(city, "metric", function(data) {
                if (data) {
                    cityWeatherCache[city] = {
                        icon: WeatherFetcher.mapIcon(data.weather[0].icon),
                        temp: Math.round(data.main.temp) + "°",
                        desc: data.weather[0].description
                    };
                } else {
                    cityWeatherCache[city] = {
                        icon: "../icons/weather_icons/clear_day.svg",
                        temp: "-",
                        desc: "-"
                    };
                }
            });
        }
    }

    Component.onCompleted: {
        // You should implement FavoriteStorage.getFavorites() if you want saved cities
        // For now, just load last searches
        loadLastSearches();
        fetchWeatherForCities(lastSearches.concat(favoriteCities.map(function(f){return f.name;})));
    }
}
