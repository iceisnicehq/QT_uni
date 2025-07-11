import QtQuick 2.6
import Sailfish.Silica 1.0
import "WeatherFetcher.js" as WeatherFetcher
import QtQuick.Layouts 1.1
import QtQuick.LocalStorage 2.0

Page {

    Rectangle {
        id: bgGradient
        anchors.fill: parent
        z: -1
        gradient: Gradient {
            GradientStop { position: 0.0; color: bgColor1 }
            GradientStop { position: 0.7; color: Qt.darker(bgColor2, 1.2) }
            GradientStop { position: 1.0; color: bgColor2 }
        }
    }
    property string lastFrogCity: ""
    property string frogImage: ""
    property color bgColor1: WeatherFetcher.getBgColor(mainTempCelsius)
    property color bgColor2: WeatherFetcher.getBgColor2(mainTempCelsius)
    property int mainTempCelsius: 0
    Behavior on bgColor1 { ColorAnimation { duration: 700; easing.type: Easing.InOutQuad } }
    Behavior on bgColor2 { ColorAnimation { duration: 700; easing.type: Easing.InOutQuad } }
    property int mainTemp: {
        var t = parseInt(temperature.text)
        return isNaN(t) ? 0 : t
    }
    id: root
    property string lastCity: WeatherFetcher.loadLastCity()
    property string currentUnits: "metric"
    ListModel { id: forecastModel }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge * 2
        Column {
            id: column
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.9
            spacing: Theme.paddingLarge
            y: Theme.paddingLarge * 2

            Rectangle {
                id: inputBar
                width: parent.width
                height: 90
                radius: height / 2
                color: Qt.rgba(0, 0, 0, 0.28)
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var page = pageStack.push(Qt.resolvedUrl("CitySearchPage.qml"));
                        page.citySelected.connect(function(city) {
                            cityInput.text = city;
                            WeatherFetcher.fetchWeather(city, root.currentUnits);
                            root.lastCity = city;
                            WeatherFetcher.saveLastCity(city);
                        });
                    }
                    cursorShape: Qt.PointingHandCursor
                }

                Row {
                    id: inputRow
                    anchors.fill: parent
                    anchors.margins: 8
                    spacing: 8

                    Image {
                        source: "../icons/pin.png"
                        width: 75
                        height: 47
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    TextField {
                        id: cityInput
                        placeholderText: qsTr("Введите город")
                        font.pixelSize: Theme.fontSizeHuge
                        color: "white"
                        background: null
                        Layout.fillWidth: true
                        width: Math.max(1, parent.width - 24 - height - 32)
                        EnterKey.onClicked: {
                            WeatherFetcher.fetchWeather(cityInput.text, root.currentUnits)
                            root.lastCity = cityInput.text
                            WeatherFetcher.saveLastCity(cityInput.text)
                        }
                    }

                    Rectangle {
                        id: unitsBtn
                        width: 60
                        height: 60
                        radius: 60
                        color: Qt.rgba(255,255,255,0.18)
                        border.color: "white"
                        border.width: 1
                        anchors.verticalCenter: parent.verticalCenter

                        Text {
                            id: unitsText
                            anchors.centerIn: parent
                            text: root.currentUnits === "metric" ? qsTr("°C") : qsTr("°F")
                            color: "white"
                            font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onPressed:   unitsBtn.scale = 0.85
                            onReleased:  unitsBtn.scale = 1.0
                            onClicked: {
                                root.currentUnits = (root.currentUnits === "metric") ? "imperial" : "metric"
                                unitsText.text = (root.currentUnits === "metric") ? "°C" : "°F"
                                if (cityInput.text) WeatherFetcher.fetchWeather(cityInput.text, root.currentUnits)
                            }
                            Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }
                        }
                    }
                }
            }

            RowLayout {
                id: weatherBlock
                width: parent.width
                opacity: 0.0
                spacing: Theme.paddingLarge
                Behavior on opacity { NumberAnimation { duration: 500 } }

                ColumnLayout {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    spacing: 0

                    Label {
                        text: qsTr("Сейчас")
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                        Layout.alignment: Qt.AlignLeft
                    }

                    RowLayout {
                        spacing: Theme.paddingSmall
                        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                        Label {
                            id: temperature
                            text: "-"
                            font.pixelSize: 100
                            font.bold: true
                            color: "white"
                            verticalAlignment: Text.AlignVCenter
                        }
                        Rectangle {
                            width: Theme.itemSizeLarge
                            height: Theme.itemSizeLarge
                            color: "transparent"
                            radius: width / 2
                            Image {
                                id: weatherIcon
                                anchors.centerIn: parent
                                width: parent.width * 0.8
                                height: parent.height * 0.8
                                fillMode: Image.PreserveAspectFit
                            }
                        }
                    }

                    Label {
                        id: highLow
                        text: qsTr("Макс.: -") + " • " + qsTr("Мин.: -")
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                        Layout.alignment: Qt.AlignLeft
                    }
                    Label {
                        id: feelsLike
                        text: qsTr("Ощущается как: -")
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                        Layout.alignment: Qt.AlignLeft
                    }
                }

                ColumnLayout {
                    Layout.preferredHeight: implicitHeight
                    Layout.fillWidth: true

                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    spacing: 2

                    Label {
                        id: description
                        text: "-"
                        font.pixelSize: Theme.fontSizeSmall
                        font.bold: true
                        color: Theme.primaryColor

                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignRight

                        Layout.preferredHeight: implicitHeight
                        Layout.alignment: Qt.AlignRight
                    }
                }
            }
            ListModel { id: hourlyModel }
            Item {
                width: root.width + 30
                x: -45
                height: Theme.itemSizeExtraLarge + 30
                visible: hourlyModel.count > 0

                Image {
                    id: frogImage
                    anchors.fill: parent
                    source: root.frogImage
                    fillMode: Image.PreserveAspectFit
                    visible: root.frogImage !== ""
                    opacity: visible ? 1.0 : 0.0
                    Behavior on opacity {
                        NumberAnimation { duration: 600; easing.type: Easing.InOutQuad }
                    }
                }
            }
            Label {
                text: qsTr(" По трёхчасовой прогноз")
                font.pixelSize: Theme.fontSizeMedium
                topPadding: 10
                color: Theme.secondaryColor
                visible: forecastModel.count > 0
            }
            Rectangle {
                width: parent.width
                height: Theme.itemSizeExtraLarge * 2.3
                color: Qt.rgba(0,0,0,0.4)
                border.color: "transparent"
                border.width: 3
                radius: 35
                visible: hourlyModel.count > 0

                Flickable {
                    id: flick
                    anchors.fill: parent
                    contentWidth: hourlyRow.width
                    flickableDirection: Flickable.HorizontalFlick
                    interactive: true
                    clip: true

                    Row {
                        id: hourlyRow
                        spacing: Theme.paddingMedium
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.top: parent.top
                        Repeater {
                            model: hourlyModel
                            delegate: Column {
                                width: Theme.itemSizeLarge
                                height: parent.height

                                Label {
                                    text: model.hour
                                    topPadding: 35
                                    font.pixelSize: Theme.fontSizeSmall
                                    horizontalAlignment: Text.AlignHCenter
                                    width: parent.width
                                }
                                Label {
                                    text: model.date
                                    font.pixelSize: Theme.fontSizeSmall
                                    color: Theme.secondaryColor
                                    horizontalAlignment: Text.AlignHCenter
                                    width: parent.width
                                }

                                Image {
                                    source: model.icon
                                    width: Theme.iconSizeSmallPlus
                                    height: Theme.iconSizeSmallPlus
                                    fillMode: Image.PreserveAspectFit
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }

                                Label {
                                    text: model.temp
                                    font.pixelSize: Theme.fontSizeSmall
                                    horizontalAlignment: Text.AlignHCenter
                                    width: parent.width
                                }
                            }
                        }
                    }
                    Canvas {
                        id: tempGraphCanvas
                        width: parent.width
                        height: 100
                        y: 220
                        anchors.left: parent.left
                        visible: hourlyModel.count > 1

                        property real leftMargin: Theme.paddingLarge * 2
                        property real rightMargin: Theme.paddingLarge * 2
                        property real topMargin: Theme.paddingMedium
                        property real bottomMargin: Theme.paddingMedium

                        // Colors
                        property color lineColor: Theme.highlightColor
                        property color dotColor: Theme.highlightColor

                        onPaint: {
                            var ctx = getContext('2d');
                            ctx.clearRect(0, 0, width, height);

                            if (hourlyModel.count < 2) return;

                            var temps = [];
                            for (var i = 0; i < hourlyModel.count; ++i) {
                                var item = hourlyModel.get(i);
                                var tempStr = item.temp.toString().replace(/[^0-9.-]+/g, "");
                                var tempVal = parseFloat(tempStr);
                                if (!isNaN(tempVal)) temps.push(tempVal);
                            }

                            if (temps.length < 2) return;

                            var minTemp = Math.min.apply(null, temps);
                            var maxTemp = Math.max.apply(null, temps);
                            var tempRange = maxTemp - minTemp;

                            if (tempRange === 0) {
                                minTemp -= 2;
                                maxTemp += 2;
                                tempRange = 4;
                            }

                            var plotWidth = width - leftMargin - rightMargin;
                            var plotHeight = height - topMargin - bottomMargin;

                            function xScale(index) {
                                return leftMargin + (index / (temps.length - 1)) * plotWidth;
                            }

                            function yScale(tempValue) {
                                return topMargin + ((maxTemp - tempValue) / tempRange) * plotHeight;
                            }

                            ctx.strokeStyle = lineColor;
                            ctx.lineWidth = 2;
                            ctx.beginPath();
                            ctx.moveTo(xScale(0), yScale(temps[0]));
                            for (var i = 1; i < temps.length; i++) {
                                ctx.lineTo(xScale(i), yScale(temps[i]));
                            }
                            ctx.stroke();

                            ctx.fillStyle = dotColor;
                            for (var i = 0; i < temps.length; i++) {
                                ctx.beginPath();
                                ctx.arc(xScale(i), yScale(temps[i]), 7, 0, 2 * Math.PI);
                                ctx.fill();
                            }
                        }

                        Connections {
                            target: hourlyModel
                            function onCountChanged() { tempGraphCanvas.requestPaint(); }
                        }

                        Component.onCompleted: if (visible) requestPaint();
                        onVisibleChanged: if (visible) requestPaint();
                    }
                }
            }

            Column {
                id: forecastBlock
                width: parent.width
                spacing: Theme.paddingMedium
                opacity: 0.0
                Behavior on opacity { NumberAnimation { duration: 500 } }

                Label {
                    text: qsTr(" Прогноз на 5 дней")
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    topPadding: 10
                    color: Theme.primaryColor
                    visible: forecastModel.count > 0
                }

                Repeater {
                    model: forecastModel
                    delegate: Rectangle {
                        width: parent.width
                        height: Theme.itemSizeMedium
                        color: Qt.rgba(0,0,0,0.4)
                        border.color: "transparent"
                        border.width: 3
                        radius: 35
                        anchors.horizontalCenter: parent.horizontalCenter

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: Theme.paddingLarge
                            spacing: Theme.paddingLarge

                            // Date
                            Label { text: model.date; Layout.preferredWidth: parent.width * 0.2 }

                            // Icon
                            Item { Layout.fillWidth: true }
                            Rectangle {
                                width: Theme.itemSizeSmall * 0.8
                                height: Theme.itemSizeSmall * 0.8
                                color: "transparent"
                                radius: width / 2
                                Image {
                                    anchors.centerIn: parent
                                    source: model.icon
                                    width: parent.width * 0.8
                                    height: parent.height * 0.8
                                    fillMode: Image.PreserveAspectFit
                                }
                            }
                            Item { Layout.fillWidth: true }
                            ColumnLayout {
                                Label { text: model.tempMax + "/" + model.tempMin}
                            }
                        }
                    }
                }
                Column {
                    width: parent.width
                    spacing: Theme.paddingLarge

                    Grid {
                        columns: 3
                        width: parent.width
                        rowSpacing: Theme.paddingLarge
                        columnSpacing: Theme.paddingLarge

                        Rectangle {
                            width: (parent.width - 2 * Theme.paddingLarge) / 3
                            height: Theme.itemSizeExtraLarge * 0.9
                            color: Qt.rgba(0,0,0,0.4)
                            border.color: "transparent"
                            border.width: 3
                            radius: 35


                            Label {
                                text: qsTr("Ветер")
                                font.pixelSize: Theme.fontSizeExtraSmallBase
                                color: Theme.secondaryColor
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.leftMargin: Theme.paddingMedium
                                anchors.topMargin: Theme.paddingMedium
                            }
                            // Value label centered
                            Label {
                                id: wind
                                anchors.centerIn: parent
                                text: "-"
                                font.pixelSize: Theme.fontSizeMedium
                                color: Theme.primaryColor
                            }
                        }
                        Rectangle {
                            width: (parent.width - 2 * Theme.paddingLarge) / 3
                            height: Theme.itemSizeExtraLarge * 0.9
                            color: Qt.rgba(0,0,0,0.4)
                            border.color: "transparent"
                            border.width: 3
                            radius: 35

                            Label {
                                text: qsTr("Влажность")
                                font.pixelSize: Theme.fontSizeExtraSmallBase
                                color: Theme.secondaryColor
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.leftMargin: Theme.paddingMedium
                                anchors.topMargin: Theme.paddingMedium
                            }
                            Label {
                                id: humidity
                                anchors.centerIn: parent
                                text: "-"
                                font.pixelSize: Theme.fontSizeMedium
                                color: Theme.primaryColor
                            }
                        }
                        Rectangle {
                            width: (parent.width - 2 * Theme.paddingLarge) / 3
                            height: Theme.itemSizeExtraLarge * 0.9
                            color: Qt.rgba(0,0,0,0.4)
                            border.color: "transparent"
                            border.width: 3
                            radius: 35

                            Label {
                                text: qsTr("Давление")
                                font.pixelSize: Theme.fontSizeExtraSmallBase
                                color: Theme.secondaryColor
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.leftMargin: Theme.paddingMedium
                                anchors.topMargin: Theme.paddingMedium
                            }
                            Label {
                                id: pressure
                                anchors.centerIn: parent
                                text: "-"
                                font.pixelSize: Theme.fontSizeMedium
                                color: Theme.primaryColor
                            }
                        }
                    }

                    Rectangle {
                        id: rootRect
                        width: parent.width
                        height: 180
                        color: Qt.rgba(0, 0, 0, 0.4)
                        radius: 35
                        border.color: "transparent"

                        Row {
                            anchors.fill: parent
                            anchors.margins: Theme.paddingLarge
                            spacing: Theme.paddingLarge

                            Rectangle {
                                id: sunriseRect
                                color: Qt.rgba(0, 0, 0, 0.2)
                                border.color: "transparent"
                                radius: 35
                                width: (rootRect.width - 2 * Theme.paddingLarge) * 0.20
                                height: parent.height

                                Column {
                                    anchors.fill: parent
                                    anchors.margins: Theme.paddingMedium
                                    spacing: Theme.paddingLarge

                                    Label {
                                        text: qsTr("Восход")
                                        font.pixelSize: Theme.fontSizeExtraSmallBase
                                        color: Theme.secondaryColor
                                    }
                                    Label {
                                        id: sunriseLabel
                                        font.pixelSize: Theme.fontSizeMedium
                                        color: Theme.primaryColor
                                    }
                                }
                            }

                            Rectangle {
                                id: sunsetRect
                                color: Qt.rgba(0, 0, 0, 0.2)
                                border.color: "transparent"
                                radius: 35
                                width: (rootRect.width - 2 * Theme.paddingLarge) * 0.20
                                height: parent.height

                                Column {
                                    anchors.fill: parent
                                    anchors.margins: Theme.paddingMedium
                                    spacing: Theme.paddingLarge

                                    Label {
                                        text: qsTr("Закат")
                                        font.pixelSize: Theme.fontSizeExtraSmallBase
                                        color: Theme.secondaryColor
                                    }
                                    Label {
                                        id: sunsetLabel
                                        font.pixelSize: Theme.fontSizeMedium
                                        color: Theme.primaryColor
                                    }
                                }
                            }

                            Canvas {
                                id: sunGraph
                                width: (rootRect.width - 2 * Theme.paddingLarge) * 0.60
                                height: rootRect.height * 0.8
                                anchors.verticalCenter: parent.verticalCenter

                                property int sunriseSec: {
                                    var txt = sunriseLabel.text
                                    if (!txt || txt.indexOf(":") < 0) return 0
                                    var parts = txt.split(":")
                                    var h = parseInt(parts[0], 10)
                                    var m = parseInt(parts[1], 10)
                                    return (isNaN(h) || isNaN(m)) ? 0 : h * 3600 + m * 60
                                }
                                property int sunsetSec: {
                                    var txt = sunsetLabel.text
                                    if (!txt || txt.indexOf(":") < 0) return 24 * 3600
                                    var parts = txt.split(":")
                                    var h = parseInt(parts[0], 10)
                                    var m = parseInt(parts[1], 10)
                                    return (isNaN(h) || isNaN(m)) ? 24 * 3600 : h * 3600 + m * 60
                                }
                                property int nowSec: {
                                    var d = new Date()
                                    return d.getHours() * 3600 + d.getMinutes() * 60 + d.getSeconds()
                                }

                                onPaint: {
                                    var ctx = getContext("2d")
                                    ctx.clearRect(0, 0, width, height)

                                    var left = 30
                                    var right = width - 30
                                    var top = 30
                                    var bottom = height - 30
                                    var baseY = bottom

                                    ctx.beginPath()
                                    for (var i = 0; i <= 100; i++) {
                                        var t = i / 100
                                        var x = left + t * (right - left)
                                        var y = baseY - Math.sin(Math.PI * t) * (baseY - top)
                                        if (i === 0) ctx.moveTo(x, y)
                                        else ctx.lineTo(x, y)
                                    }
                                    ctx.strokeStyle = "#FFD700"
                                    ctx.lineWidth = 2
                                    ctx.stroke()

                                    var totalSec = sunsetSec - sunriseSec
                                    if (totalSec <= 0) totalSec = 1
                                    var rawT = (nowSec - sunriseSec) / totalSec
                                    var nowT = Math.max(0, Math.min(1, rawT))

                                    ctx.beginPath()
                                    if (nowT <= 0) {
                                    } else if (nowT >= 1) {
                                        for (var i = 0; i <= 100; i++) {
                                            var t = i / 100
                                            var x = left + t * (right - left)
                                            var y = baseY - Math.sin(Math.PI * t) * (baseY - top)
                                            if (i === 0) ctx.moveTo(x, baseY)
                                            ctx.lineTo(x, y)
                                        }
                                        ctx.lineTo(right, baseY)
                                        ctx.closePath()
                                        ctx.fillStyle = "rgba(70, 130, 255, 0.3)"
                                        ctx.fill()
                                    } else {
                                        var maxIdx = Math.floor(100 * nowT)
                                        for (var i = 0; i <= maxIdx; i++) {
                                            var t = i / 100
                                            var x = left + t * (right - left)
                                            var y = baseY - Math.sin(Math.PI * t) * (baseY - top)
                                            if (i === 0) ctx.moveTo(x, baseY)
                                            ctx.lineTo(x, y)
                                        }
                                        var endX = left + nowT * (right - left)
                                        ctx.lineTo(endX, baseY)
                                        ctx.closePath()
                                        ctx.fillStyle = "rgba(70, 130, 255, 0.3)"
                                        ctx.fill()
                                    }

                                    var sunX = left + nowT * (right - left)
                                    var sunY = baseY - Math.sin(Math.PI * nowT) * (baseY - top)
                                    ctx.beginPath()
                                    ctx.arc(sunX, sunY, 12, 0, 2 * Math.PI)
                                    ctx.fillStyle = "#FFD700"
                                    ctx.shadowColor = "#FFD700"
                                    ctx.shadowBlur = 12
                                    ctx.fill()
                                    ctx.shadowBlur = 0
                                }

                                Timer {
                                    interval: 60000
                                    running: true
                                    repeat: true
                                    onTriggered: sunGraph.requestPaint()
                                }
                                Component.onCompleted: requestPaint()
                                onVisibleChanged: if (visible) requestPaint()
                            }

                            Connections {
                                target: sunriseLabel
                                onTextChanged: sunGraph.requestPaint()
                            }
                            Connections {
                                target: sunsetLabel
                                onTextChanged: sunGraph.requestPaint()
                            }
                        }
                    }
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
                y: Theme.paddingLarge
            }
        }
    }

    Component.onCompleted: {
        if (root.lastCity !== "") {
            cityInput.text = root.lastCity
            WeatherFetcher.fetchWeather(root.lastCity, root.currentUnits)
        }
    }
}
