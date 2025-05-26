import QtQuick 2.6
import Sailfish.Silica 1.0
import "WeatherGlitcher.js" as WeatherFetcher
Page {
    id: root
    property string lastCity: ""

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        Column {
            id: column
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.52
            spacing: Theme.paddingLarge
            y: Theme.paddingLarge

            TextField {
                id: cityInput
                label: qsTr("Город")
                placeholderText: qsTr("Введите город")
                width: parent.width
                EnterKey.onClicked: {
                    WeatherFetcher.fetchWeather(cityInput.text)
                    root.lastCity = cityInput.text
                }
            }

            Button {
                text: qsTr("Обновить погоду")
                width: parent.width
                onClicked: {
                    WeatherFetcher.fetchWeather(cityInput.text)
                    root.lastCity = cityInput.text
                }
            }

            Column {
                id: weatherBlock
                spacing: Theme.paddingMedium
                opacity: 0.0

                Behavior on opacity { NumberAnimation { duration: 500 } }

                Label {
                    id: cityName
                    text: qsTr("Город: -")
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.primaryColor
                }

                Label {
                    id: temperature
                    text: qsTr("Температура: -")
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.highlightColor
                }

                Label {
                    id: description
                    text: qsTr("Описание: -")
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                }

                Label {
                    id: humidity
                    text: qsTr("Влажность: -")
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                }

                Label {
                    id: wind
                    text: qsTr("Ветер: -")
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                }
            }

            Label {
                id: errorMessage
                color: Theme.errorColor
                font.pixelSize: Theme.fontSizeExtraSmall
                wrapMode: Text.Wrap
                visible: false
                width: parent.width
                horizontalAlignment: Qt.AlignHCenter
            }
        }
    }


    Component.onCompleted: {
        if (root.lastCity !== "") {
            cityInput.text = root.lastCity
            WeatherFetcher.fetchWeather(root.lastCity)
        }
    }
}
