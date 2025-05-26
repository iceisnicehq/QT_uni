import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    property int hours: 0
    property int minutes: 0
    property int seconds: 10

    property int countdown: hours * 3600 + minutes * 60 + seconds
    property int timeLeft: countdown

    function formatTime(sec) {
        var h = Math.floor(sec / 3600)
        var m = Math.floor((sec % 3600) / 60)
        var s = sec % 60
        if (h > 0)
            return ("0"+h).slice(-2) + ":" + ("0"+m).slice(-2) + ":" + ("0"+s).slice(-2)
        else if (m > 0)
            return ("0"+m).slice(-2) + ":" + ("0"+s).slice(-2)
        else
            return "00:" + ("0"+s).slice(-2)
    }

    Timer {
        id: countdownTimer
        interval: 1000
        repeat: true
        running: false
        onTriggered: {
            if (timeLeft > 0) {
                timeLeft--
            } else {
                running = false
            }
        }
    }

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Таймер")
        extraContent.children: [
            IconButton {
                objectName: "aboutButton"
                icon.source: "image://theme/icon-m-about"
                anchors.verticalCenter: parent.verticalCenter
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        ]
    }

    Column {
        anchors.centerIn: parent
        spacing: Theme.paddingLarge

        Row {
            spacing: Theme.paddingLarge

            // Часы
            Column {
                spacing: Theme.paddingSmall
                width: Theme.itemSizeLarge * 1.5
                Label {
                    text: qsTr("Часы")
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }
                ComboBox {
                    id: hoursCombo
                    width: Theme.itemSizeLarge * 1.5
                    currentIndex: hours
                    menu: ContextMenu {
                        Repeater {
                            model: 24
                            MenuItem {
                                text: index.toString()
                                onClicked: {
                                    hoursCombo.currentIndex = index
                                    hours = index
                                    if (!countdownTimer.running)
                                        timeLeft = hours * 3600 + minutes * 60 + seconds
                                }
                            }
                        }
                    }
                }
            }

            // Минуты
            Column {
                spacing: Theme.paddingSmall
                width: Theme.itemSizeLarge * 1.5
                Label {
                    text: qsTr("Минуты")
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }
                ComboBox {
                    id: minutesCombo
                    width: Theme.itemSizeLarge * 1.5
                    currentIndex: minutes
                    menu: ContextMenu {
                        Repeater {
                            model: 60
                            MenuItem {
                                text: index.toString()
                                onClicked: {
                                    minutesCombo.currentIndex = index
                                    minutes = index
                                    if (!countdownTimer.running)
                                        timeLeft = hours * 3600 + minutes * 60 + seconds
                                }
                            }
                        }
                    }
                }
            }

            // Секунды
            Column {
                spacing: Theme.paddingSmall
                width: Theme.itemSizeLarge * 1.5
                Label {
                    text: qsTr("Секунды")
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }
                ComboBox {
                    id: secondsCombo
                    width: Theme.itemSizeLarge * 1.5
                    currentIndex: seconds
                    menu: ContextMenu {
                        Repeater {
                            model: 60
                            MenuItem {
                                text: index.toString()
                                onClicked: {
                                    secondsCombo.currentIndex = index
                                    seconds = index
                                    if (!countdownTimer.running)
                                        timeLeft = hours * 3600 + minutes * 60 + seconds
                                }
                            }
                        }
                    }
                }
            }
        }

        Label {
            objectName: "timerLabel"
            text: qsTr("Осталось: %1").arg(formatTime(timeLeft))
            font.pixelSize: Theme.fontSizeHuge
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        Button {
            text: countdownTimer.running ? qsTr("Сбросить") : qsTr("Старт")
            width: parent.width
            onClicked: {
                if (countdownTimer.running) {
                    countdownTimer.stop()
                    timeLeft = hours * 3600 + minutes * 60 + seconds
                } else {
                    countdown = hours * 3600 + minutes * 60 + seconds
                    timeLeft = countdown
                    if (timeLeft > 0)
                        countdownTimer.start()
                }
            }
        }
    }
}
