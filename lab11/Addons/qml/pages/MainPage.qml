import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: timerPage
    allowedOrientations: Orientation.All

    property int hours: 0
    property int minutes: 0
    property int seconds: 0
    property int totalSeconds: 0
    property int timeLeft: 0

    Timer {
        id: countdownTimer
        interval: 1000
        repeat: true
        running: false
        onTriggered: {
            if (timeLeft > 0) {
                timeLeft--
            } else {
                countdownTimer.stop()
                console.log("Таймер завершён")

            }
        }
    }

    function formatTime(sec) {
        var h = Math.floor(sec / 3600)
        var m = Math.floor((sec % 3600) / 60)
        var s = sec % 60
        return ("%1:%2:%3")
                .arg(h < 10 ? "0"+h : h)
                .arg(m < 10 ? "0"+m : m)
                .arg(s < 10 ? "0"+s : s)
    }

    PageHeader {
        title: qsTr("Таймер")
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -Theme.itemSizeExtraLarge
        spacing: Theme.paddingLarge


        Row {
            spacing: Theme.paddingLarge
            anchors.horizontalCenter: parent.horizontalCenter

            TimePickerColumn {
                from: 0
                to: 23
                currentValue: hours
                onValueChanged: hours = value
            }

            Item {
                width: Theme.paddingLarge
                height: Theme.itemSizeLarge * 5
                Label {
                    anchors.centerIn: parent
                    text: ":"
                    font.pixelSize: Theme.fontSizeExtraLarge
                }
            }

            TimePickerColumn {
                from: 0
                to: 59
                currentValue: minutes
                onValueChanged: minutes = value
            }

            Item {
                width: Theme.paddingLarge
                height: Theme.itemSizeLarge * 5
                Label {
                    anchors.centerIn: parent
                    text: ":"
                    font.pixelSize: Theme.fontSizeExtraLarge
                }
            }

            TimePickerColumn {
                from: 0
                to: 59
                currentValue: seconds
                onValueChanged: seconds = value
            }
        }


        Item {
            height: Theme.paddingExtraLarge * 3
            width: 1
        }

        Row {
            width: parent.width
            height: 100
             }
        Label {
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
                    timeLeft = 0
                } else {
                    totalSeconds = hours * 3600 + minutes * 60 + seconds
                    if (totalSeconds > 0) {
                        timeLeft = totalSeconds
                        countdownTimer.start()
                    }
                }
            }
        }
    }
}
