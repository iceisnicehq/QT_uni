import QtQuick 2.0
import Sailfish.Silica 1.0
import QtMultimedia 5.6

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    property color currentBgColor: "black"
    property string rect2Text: "Красный"
    property real elementsOpacity: 1.0
    property int rectSize: 200

    property var colorPool: ["red", "blue", "green"]
    property int rect1ColorIndex: 0
    property int rect2ColorIndex: 1
    property int rect3ColorIndex: 2


    Audio {
        id: buttonSound
        property bool wasPlayed: false
        source: "qrc:/sounds/meow.wav"
        volume: 1.0

        onPlaying: {
            wasPlayed = true;
            console.log("Начало воспроизведения");
        }

        onStopped: {
            if (wasPlayed) {
                console.log("Воспроизведение завершено успешно");
                wasPlayed = false;
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: currentBgColor
        z: -1
    }

    Column {
        width: parent.width
        spacing: Theme.paddingLarge
        anchors.top: parent.top
        anchors.topMargin: Theme.paddingLarge
        // Элементы управления теперь сверху

        PageHeader {
            objectName: "pageHeader"
            title: qsTr("LR 12")
        }

        Button {
            text: "Цвет фона"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                buttonSound.play()
                if (currentBgColor === Theme.highlightBackgroundColor) {
                    currentBgColor = "black"
                } else {
                    currentBgColor = Theme.highlightBackgroundColor
                }
            }
        }

        // Поле ввода и кнопка обновить на отдельных строках
        TextField {
            id: textInput
            width: parent.width - 2*Theme.paddingLarge
            placeholderText: "Rect_2 text"
            label: "Новый текст"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Button {
            id: updateButton
            text: "Обновить"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                buttonSound.play()
                if (textInput.text !== "") {
                    rect2Text = textInput.text
                }
            }
        }

        Slider {
            width: parent.width - 2*Theme.paddingLarge
            anchors.horizontalCenter: parent.horizontalCenter
            minimumValue: 0
            maximumValue: 1
            stepSize: 0.1
            value: elementsOpacity
            label: "Прозрачность элементов"
            onValueChanged: elementsOpacity = value
        }

        Row {
            width: parent.width - 2*Theme.paddingLarge
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: Theme.paddingMedium

            Button {
                text: "Уменьшить"
                width: parent.width / 2 - parent.spacing / 2
                onClicked: {
                    buttonSound.play()
                    if (rectSize > 100) {
                        rectSize -= 20
                    }
                }
            }

            Button {
                text: "Увеличить"
                width: parent.width / 2 - parent.spacing / 2
                onClicked: {
                    buttonSound.play()
                    if (rectSize < 300) {
                        rectSize += 20
                    }
                }
            }
        }
    }

    Rectangle {
        id: bottomBar
        width: parent.width
        height: rectSize + 2*Theme.paddingLarge
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        color: "transparent"
        z: 2
        opacity: elementsOpacity

        Row {
            id: rectContainer
            anchors.centerIn: parent
            spacing: Theme.paddingMedium

            Column {
                spacing: Theme.paddingSmall
                Rectangle {
                    id: rect1
                    width: rectSize
                    height: width
                    color: colorPool[rect1ColorIndex]
                }
                Button {
                    width: rect1.width
                    text: "Цвет: " + colorPool[rect1ColorIndex]
                    onClicked: {
                        buttonSound.play()
                        rect1ColorIndex = (rect1ColorIndex + 1) % colorPool.length
                    }
                }
            }

            Column {
                spacing: Theme.paddingSmall
                Rectangle {
                    id: rect2
                    width: rectSize
                    height: width
                    color: colorPool[rect2ColorIndex]
                    Text {
                        anchors.centerIn: parent
                        text: rect2Text
                        color: "white"
                        font.pixelSize: Theme.fontSizeLarge
                    }
                }
                Button {
                    width: rect2.width
                    text: "Цвет: " + colorPool[rect2ColorIndex]
                    onClicked: {
                        buttonSound.play()
                        rect2ColorIndex = (rect2ColorIndex + 1) % colorPool.length
                    }
                }
            }

            Column {
                spacing: Theme.paddingSmall
                Rectangle {
                    id: rect3
                    width: rectSize
                    height: width
                    color: colorPool[rect3ColorIndex]
                    property real baseY: 0
                    property int liftHeight: -100
                    y: baseY
                    Component.onCompleted: baseY = y
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            liftAnimation.start()
                        }
                    }
                    SequentialAnimation {
                        id: liftAnimation
                        running: false
                        NumberAnimation {
                            target: rect3
                            property: "y"
                            to: rect3.baseY + rect3.liftHeight
                            duration: 300
                            easing.type: Easing.OutQuad
                        }
                        NumberAnimation {
                            target: rect3
                            property: "y"
                            to: rect3.baseY
                            duration: 400
                            easing.type: Easing.OutBounce
                        }
                    }
                }
                Button {
                    width: rect3.width
                    text: "Цвет: " + colorPool[rect3ColorIndex]
                    onClicked: {
                        buttonSound.play()
                        rect3ColorIndex = (rect3ColorIndex + 1) % colorPool.length
                    }
                }
            }
        }
    }
}
