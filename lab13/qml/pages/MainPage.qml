import QtQuick 2.0
import Sailfish.Silica 1.0
import QtMultimedia 5.6

Page {
    id: page

    property string value1: ""
    property string value2: ""
    property string result: ""

    Audio {
        id: buttonSound
        property bool wasPlayed: false
        source: "qrc:/sound/meow.wav"
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
    ListModel {
        id: historyModel
    }

    Column {
        width: parent.width
        spacing: Theme.paddingLarge * 1.5
        anchors.centerIn: parent

        Button {
            text: "Открыть диалог"
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                buttonSound.play()
                var dialog = pageStack.push("DialogSum.qml")
                dialog.accepted.connect(function() {
                    value1 = dialog.value1
                    value2 = dialog.value2
                    result = dialog.result

                    historyModel.insert(0, {
                        value1: value1,
                        value2: value2,
                        result: result,
                        timestamp: new Date().toLocaleTimeString(Qt.locale(), "hh:mm:ss")
                    })
                })
            }
        }

        SectionHeader {
            text: "Последнее вычисление"
            visible: result !== ""
        }

        Label {
            text: "Первое число: " + value1
            visible: value1 !== ""
            anchors.horizontalCenter: parent.horizontalCenter
            color: Theme.secondaryHighlightColor
        }

        Label {
            text: "Второе число: " + value2
            visible: value2 !== ""
            anchors.horizontalCenter: parent.horizontalCenter
            color: Theme.secondaryHighlightColor
        }

        Label {
            text: "Сумма: " + result
            visible: result !== ""
            anchors.horizontalCenter: parent.horizontalCenter
            color: Theme.highlightColor
            font.bold: true
        }

        SectionHeader {
            text: "История вычислений"
            visible: historyModel.count > 0
        }

        SilicaListView {
            width: parent.width
            height: Math.min(historyModel.count * Theme.itemSizeMedium, page.height / 2)
            visible: historyModel.count > 0
            model: historyModel

            delegate: BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium

                Column {
                    width: parent.width - 2*Theme.horizontalPageMargin
                    anchors.centerIn: parent
                    spacing: Theme.paddingSmall

                    Label {
                        text: value1 + " + " + value2 + " = " + result
                        width: parent.width
                        truncationMode: TruncationMode.Fade
                        color: Theme.primaryColor
                    }

                    Label {
                        text: timestamp
                        width: parent.width
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                        horizontalAlignment: Text.AlignRight
                    }
                }

                Separator {
                    width: parent.width
                    color: Theme.primaryColor
                    anchors.bottom: parent.bottom
                }
            }

            VerticalScrollDecorator {}
        }
    }
}
