import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15
import QtCore
import "WeatherFetcher.js" as WeatherFetcher

ApplicationWindow {
    visible: true
    width: 400
    height: 1200
    title: qsTr("Погодный информатор")

    Settings {
        id: appSettings
        property string lastCity: ""
        property string tempUnit: "metric"
    }

    ListModel {
        id: forecastModel
    }

    ListModel {
        id: hourlyModel
    }

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"

        Flickable {
            anchors.fill: parent
            contentHeight: contentColumn.height + 20
            clip: true

            ColumnLayout {
                id: contentColumn
                width: parent.width
                spacing: 15
                anchors.top: parent.top
                anchors.topMargin: 10

                TextField {
                    id: cityInput
                    placeholderText: qsTr("Введите город")
                    Layout.preferredWidth: parent.width - 40
                    Layout.alignment: Qt.AlignHCenter
                    font.pointSize: 16
                    background: Rectangle {
                        color: "#ffffff"
                        radius: 10
                        border.color: "#cccccc"
                    }
                }

                Button {
                    text: qsTr("Обновить погоду")
                    font.pointSize: 16
                    Layout.preferredWidth: parent.width - 40
                    Layout.alignment: Qt.AlignHCenter
                    background: Rectangle {
                        color: "#4caf50"
                        radius: 10
                    }
                    onClicked: {
                        WeatherFetcher.fetchWeather(cityInput.text)
                        appSettings.lastCity = cityInput.text
                    }
                }

                RowLayout {
                    Layout.preferredWidth: parent.width - 40
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 15

                    Text {
                        text: qsTr("Единицы:")
                        font.pointSize: 14
                        color: "#333"
                    }


                    RadioButton {
                        id: celsiusButton
                        text: "°C"
                        checked: appSettings.tempUnit === "metric"
                        onClicked: {
                            appSettings.tempUnit = "metric"
                            if (cityInput.text) {
                                WeatherFetcher.fetchWeather(cityInput.text)
                            }
                        }
                    }

                    RadioButton {
                        id: fahrenheitButton
                        text: "°F"
                        checked: appSettings.tempUnit === "imperial"
                        onClicked: {
                            appSettings.tempUnit = "imperial"
                            if (cityInput.text) {
                                WeatherFetcher.fetchWeather(cityInput.text)
                            }
                        }
                    }
                }

                ColumnLayout {
                    id: weatherBlock
                    spacing: 10
                    opacity: 0.0
                    Layout.preferredWidth: parent.width - 40
                    Layout.alignment: Qt.AlignHCenter

                    Behavior on opacity {
                        NumberAnimation { duration: 500 }
                    }

                    Text {
                        id: cityName
                        text: qsTr("Город: -")
                        font.pointSize: 18
                        font.bold: true
                        color: "#212121"
                    }

                    Text {
                        id: temperature
                        text: qsTr("Температура: -")
                        font.pointSize: 18
                        color: "#e53935"
                        font.bold: true
                    }

                    Text {
                        id: description
                        text: qsTr("Описание: -")
                        font.pointSize: 14
                        color: "#9e9e9e"
                    }

                    Text {
                        id: humidity
                        text: qsTr("Влажность: -")
                        font.pointSize: 14
                        color: "#9e9e9e"
                    }

                    Text {
                        id: wind
                        text: qsTr("Ветер: -")
                        font.pointSize: 14
                        color: "#9e9e9e"
                    }

                    Rectangle {
                        Layout.topMargin: 20
                        Layout.preferredWidth: parent.width
                        height: 1
                        color: "#cccccc"
                    }

                    Text {
                        text: qsTr("Прогноз на 5 дней")
                        font.pointSize: 16
                        font.bold: true
                        color: "#212121"
                        horizontalAlignment: Text.AlignHCenter
                    }

                    ListView {
                        id: forecastListView
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: 200
                        model: forecastModel
                        spacing: 10
                        clip: true

                        delegate: RowLayout {
                            width: forecastListView.width
                            spacing: 15

                            Text {
                                text: date
                                font.pointSize: 14
                                font.bold: true
                                Layout.preferredWidth: 60
                            }

                            Image {
                                source: icon
                                Layout.preferredWidth: 30
                                Layout.preferredHeight: 30
                                fillMode: Image.PreserveAspectFit
                            }

                            Text {
                                text: temp
                                font.pointSize: 14
                                color: "#e53935"
                                Layout.preferredWidth: 60
                            }

                            Text {
                                text: description
                                font.pointSize: 14
                                color: "#9e9e9e"
                                Layout.fillWidth: true
                                wrapMode: Text.Wrap
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.topMargin: 20
                        spacing: 5
                        Layout.preferredWidth: parent.width

                        Text {
                            text: qsTr("Температура (°C)")
                            font.pointSize: 14
                            font.bold: true
                            color: "#e53935"
                        }

                        Rectangle {
                            id: tempChartContainer
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 150
                            color: "#ffffff"
                            border.color: "#cccccc"
                            border.width: 1
                            radius: 10

                            Shape {
                                id: tempChart
                                anchors.fill: parent
                                anchors.margins: 10

                                ShapePath {
                                    id: tempPath
                                    strokeColor: "#e53935"
                                    strokeWidth: 3
                                    fillColor: "transparent"
                                    capStyle: ShapePath.RoundCap
                                }

                                Repeater {
                                    model: 5
                                    delegate: Shape {
                                        ShapePath {
                                            strokeColor: "#eeeeee"
                                            strokeWidth: 1
                                            startX: 0; startY: tempChart.height * index / 4
                                            PathLine { x: tempChart.width; y: tempChart.height * index / 4 }
                                        }
                                    }
                                }

                                Repeater {
                                    model: appSettings.tempUnit === "metric" ? [-20, -10, 0, 10, 20, 30, 40] : [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
                                    delegate: Text {
                                        x: 5
                                        y: tempChart.height * (1 - (modelData + (appSettings.tempUnit === "metric" ? 20 : 0)) /
                                           (appSettings.tempUnit === "metric" ? 60 : 120)) - 5
                                        text: modelData
                                        color: "#e53935"
                                        font.pixelSize: 10
                                    }
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 5
                        Layout.preferredWidth: parent.width

                        Text {
                            text: qsTr("Влажность (%)")
                            font.pointSize: 14
                            font.bold: true
                            color: "#2196F3"
                        }

                        Rectangle {
                            id: humidityChartContainer
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 150
                            color: "#ffffff"
                            border.color: "#cccccc"
                            border.width: 1
                            radius: 10

                            Shape {
                                id: humidityChart
                                anchors.fill: parent
                                anchors.margins: 10

                                ShapePath {
                                    id: humidityPath
                                    strokeColor: "#2196F3"
                                    strokeWidth: 3
                                    fillColor: "transparent"
                                    capStyle: ShapePath.RoundCap
                                }

                                Repeater {
                                    model: 5
                                    delegate: Shape {
                                        ShapePath {
                                            strokeColor: "#eeeeee"
                                            strokeWidth: 1
                                            startX: 0; startY: humidityChart.height * index / 4
                                            PathLine { x: humidityChart.width; y: humidityChart.height * index / 4 }
                                        }
                                    }
                                }

                                Repeater {
                                    model: [0, 25, 50, 75, 100]
                                    delegate: Text {
                                        x: 5
                                        y: humidityChart.height * (1 - modelData / 100) - 5
                                        text: modelData
                                        color: "#2196F3"
                                        font.pixelSize: 10
                                    }
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 5
                        Layout.preferredWidth: parent.width

                        Text {
                            text: qsTr("Скорость ветра (м/с)")
                            font.pointSize: 14
                            font.bold: true
                            color: "#4CAF50"
                        }

                        Rectangle {
                            id: windChartContainer
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 150
                            color: "#ffffff"
                            border.color: "#cccccc"
                            border.width: 1
                            radius: 10

                            Shape {
                                id: windChart
                                anchors.fill: parent
                                anchors.margins: 10

                                ShapePath {
                                    id: windPath
                                    strokeColor: "#4CAF50"
                                    strokeWidth: 3
                                    fillColor: "transparent"
                                    capStyle: ShapePath.RoundCap
                                }

                                Repeater {
                                    model: 5
                                    delegate: Shape {
                                        ShapePath {
                                            strokeColor: "#eeeeee"
                                            strokeWidth: 1
                                            startX: 0; startY: windChart.height * index / 4
                                            PathLine { x: windChart.width; y: windChart.height * index / 4 }
                                        }
                                    }
                                }

                                Repeater {
                                    model: [0, 5, 10, 15, 20]
                                    delegate: Text {
                                        x: 5
                                        y: windChart.height * (1 - modelData / 20) - 5
                                        text: modelData
                                        color: "#4CAF50"
                                        font.pixelSize: 10
                                    }
                                }
                            }
                        }
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
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }

        Component.onCompleted: {
            if (appSettings.lastCity !== "") {
                cityInput.text = appSettings.lastCity
                WeatherFetcher.fetchWeather(appSettings.lastCity)
            }
        }
    }

    Connections {
        target: hourlyModel
        onCountChanged: {
            if (hourlyModel.count > 0) {
                updateChart(tempPath, tempChartContainer, "temp", -20, 40, 60)
                updateChart(humidityPath, humidityChartContainer, "humidity", 0, 100, 100)
                updateChart(windPath, windChartContainer, "wind", 0, 20, 20)
            }
        }
    }

    function updateChart(path, container, propertyName, minValue, maxValue, range) {
        path.pathElements = []
        var stepX = (container.width - 20) / (hourlyModel.count - 1)
        var startX = 10
        var chartHeight = container.height - 20

        if (propertyName === "temp" && appSettings.tempUnit === "imperial") {
            minValue = 0
            maxValue = 100
            range = 120
        }

        for (var i = 0; i < hourlyModel.count; i++) {
            var item = hourlyModel.get(i)
            var x = startX + i * stepX
            var y = chartHeight * (1 - (item[propertyName] - minValue) / range)

            if (i === 0) {
                path.pathElements.push(Qt.createQmlObject(
                    'import QtQuick 2.15; import QtQuick.Shapes 1.15; PathMove { x: ' + x + '; y: ' + y + ' }',
                    path))
            } else {
                path.pathElements.push(Qt.createQmlObject(
                    'import QtQuick 2.15; import QtQuick.Shapes 1.15; PathLine { x: ' + x + '; y: ' + y + ' }',
                    path))
            }
        }
    }
}
