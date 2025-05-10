import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtCore
import "WeatherFetcher.js" as WeatherFetcher

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: qsTr("Погодный информатор")

    Settings {
        id: appSettings
        property string lastCity: ""
    }

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 15

            TextField {
                id: cityInput
                placeholderText: qsTr("Введите город")
                Layout.preferredWidth: 300
                font.pointSize: 16
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#cccccc"
                }
            }

            Button {
                text: qsTr("Обновить погоду")
                font.pointSize: 16
                Layout.preferredWidth: 300
                background: Rectangle {
                    color: "#4caf50"
                    radius: 5
                }
                onClicked: {
                    WeatherFetcher.fetchWeather(cityInput.text)
                    appSettings.lastCity = cityInput.text
                }
            }

            ColumnLayout {
                id: weatherBlock
                spacing: 10
                opacity: 0.0

                Behavior on opacity {
                    NumberAnimation { duration: 500 }
                }

                Text {
                    id: cityName
                    text: qsTr("Город: -")
                    font.pointSize: 18
                    font.bold: true
                    color: "#333"
                }

                Text {
                    id: temperature
                    text: qsTr("Температура: -")
                    font.pointSize: 18
                    color: "#ff5722"
                    font.bold: true
                    Behavior on text {
                        NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
                    }
                }

                Text {
                    id: description
                    text: qsTr("Описание: -")
                    font.pointSize: 14
                    color: "#757575"
                }

                Text {
                    id: humidity
                    text: qsTr("Влажность: -")
                    font.pointSize: 14
                    color: "#757575"
                }

                Text {
                    id: wind
                    text: qsTr("Ветер: -")
                    font.pointSize: 14
                    color: "#757575"
                }
            }
            
            Text {
                id: errorMessage
                color: "red"
                font.pointSize: 12
                wrapMode: Text.Wrap
                visible: false
                width: parent.width * 0.8
                horizontalAlignment: Text.AlignHCenter
            }
        }
        
        Component.onCompleted: {
            if (appSettings.lastCity !== "") {
                cityInput.text = appSettings.lastCity
                WeatherFetcher.fetchWeather(appSettings.lastCity)
            }
        }
    }
}

ttings.lastCity
                WeatherFetcher.fetchWeather(appSettings.lastCity)
            }
        }
    }
}
