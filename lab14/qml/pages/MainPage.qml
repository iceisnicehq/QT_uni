import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    property bool authenticated: systemService.authenticated

    PageHeader {
        id: mainHeader
        title: "Системная информация"
    }

    // Внутреннее уведомление через Dialog (универсально для любой версии Sailfish)
    Dialog {
        id: localNotificationDialog
        property string notificationText: ""
        Label {
            anchors.centerIn: parent
            text: localNotificationDialog.notificationText
            wrapMode: Text.Wrap
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: Math.max(authBlock.height, mainBlock.height, page.height)

        // Блок аутентификации
        Item {
            id: authBlock
            visible: !authenticated
            width: parent.width
            height: page.height

            Column {
                anchors.centerIn: parent
                width: Math.min(parent.width * 0.7, 350)
                spacing: Theme.paddingLarge

                TextField {
                    id: passField
                    width: parent.width
                    placeholderText: "Введите пароль"
                    echoMode: TextInput.Password
                    EnterKey.onClicked: loginBtn.clicked()
                }
                Button {
                    id: loginBtn
                    text: "Войти"
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width * 0.65
                    onClicked: {
                        if (!systemService.checkPassword(passField.text)) {
                            notificationDialog.notificationText = "Неверный пароль"
                            notificationDialog.open()
                        } else {
                            passField.text = ""
                        }
                    }
                }
            }
        }

        // Основной блок для авторизованных
        Item {
            id: mainBlock
            visible: authenticated
            width: parent.width
            height: page.height

            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingLarge * 2 + mainHeader.height
                width: Math.min(parent.width * 0.9, 420)
                spacing: Theme.paddingLarge

                Button {
                    text: "Показать системную информацию"
                    width: parent.width
                    onClicked: {
                        var info = systemService.getSystemInfo()
                        infoDialog.infoText = JSON.stringify(info, null, 2)
                        infoDialog.open()
                    }
                }

                SectionHeader {
                    text: "Параметры устройства"
                }

                Column {
                    width: parent.width
                    spacing: Theme.paddingSmall
                    Label {
                        text: "Яркость: " + Math.round(systemService.deviceParameters.brightness || 50)
                    }
                    Slider {
                        width: parent.width
                        minimumValue: 0
                        maximumValue: 100
                        value: systemService.deviceParameters.brightness || 50
                        stepSize: 1
                        onValueChanged: systemService.setDeviceParameter("brightness", value)
                    }
                }

                Column {
                    width: parent.width
                    spacing: Theme.paddingSmall
                    Label {
                        text: "Громкость: " + Math.round(systemService.deviceParameters.sound || 50)
                    }
                    Slider {
                        width: parent.width
                        minimumValue: 0
                        maximumValue: 100
                        value: systemService.deviceParameters.sound || 50
                        stepSize: 1
                        onValueChanged: systemService.setDeviceParameter("sound", value)
                    }
                }

                Column {
                    width: parent.width
                    spacing: Theme.paddingSmall
                    Label {
                        text: "Режим"
                    }
                    ComboBox {
                        width: parent.width * 0.92
                        label: ""
                        currentIndex: ["normal","silent","vibrate"].indexOf(systemService.deviceParameters.mode)
                        menu: ContextMenu {
                            MenuItem { text: "Обычный" }
                            MenuItem { text: "Без звука" }
                            MenuItem { text: "Вибро" }
                        }
                        onCurrentIndexChanged: {
                            var m = ["normal","silent","vibrate"][currentIndex]
                            systemService.setDeviceParameter("mode", m)
                        }
                    }
                }

                Button {
                    text: "Открыть окно уведомления"
                    width: parent.width
                    onClicked: notificationWindow.open()
                }
            }
        }
    }

    // Диалог для ошибок авторизации
    Dialog {
        id: notificationDialog
        property string notificationText: ""
        Label {
            anchors.centerIn: parent
            text: notificationDialog.notificationText
            wrapMode: Text.Wrap
        }
    }

    // Диалог для системной информации с прокруткой
    Dialog {
        id: infoDialog
        property string infoText: ""
        SilicaFlickable {
            anchors.fill: parent
            contentHeight: infoLabel.height + Theme.paddingLarge
            Label {
                id: infoLabel
                width: parent.width - 2*Theme.horizontalPageMargin
                text: infoDialog.infoText
                wrapMode: Text.Wrap
            }
        }
    }

    // Окно для ввода и отправки уведомления
    Dialog {
        id: notificationWindow
        property string notificationMessage: ""
        Column {
            anchors.centerIn: parent
            width: parent.width * 0.8
            spacing: Theme.paddingLarge

            Label {
                text: "Введите текст уведомления:"
            }
            TextField {
                id: notificationTextField
                width: parent.width
                placeholderText: "Текст уведомления"
                text: notificationWindow.notificationMessage
                onTextChanged: notificationWindow.notificationMessage = text
                EnterKey.onClicked: sendBtn.clicked()
            }
            Button {
                id: sendBtn
                text: "Отправить"
                onClicked: {
                    if (notificationWindow.notificationMessage.trim().length > 0) {
                        systemService.sendNotification(notificationWindow.notificationMessage)
                        localNotificationDialog.notificationText = notificationWindow.notificationMessage
                        localNotificationDialog.open()
                        notificationWindow.notificationMessage = ""
                        notificationWindow.close()
                    }
                }
            }
            Button {
                text: "Отмена"
                onClicked: notificationWindow.close()
            }
        }
    }
}
