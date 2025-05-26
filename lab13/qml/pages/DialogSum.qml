import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: dialog

    property string value1: ""
    property string value2: ""
    property string result: ""

    property bool field1Error: false
    property bool field2Error: false

    canAccept: !field1Error && !field2Error &&
               field1.text !== "" && field2.text !== ""

    Column {
        width: parent.width
        spacing: Theme.paddingLarge * 1.5

        DialogHeader {
            title: "Сумма чисел"
            acceptText: "Подтвердить"
        }

        TextField {
            id: field1
            width: parent.width * 0.92
            placeholderText: "Введите первое число"
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            color: field1Error ? Theme.errorColor : Theme.primaryColor

            onTextChanged: validateInput(field1, 1)
        }

        Label {
            text: "Введите число"
            color: Theme.errorColor
            font.pixelSize: Theme.fontSizeExtraSmall
            visible: field1Error
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
        }

        TextField {
            id: field2
            width: parent.width * 0.92
            placeholderText: "Введите второе число"
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            color: field2Error ? Theme.errorColor : Theme.primaryColor

            onTextChanged: validateInput(field2, 2)
        }

        Label {
            text: "Введите число"
            color: Theme.errorColor
            font.pixelSize: Theme.fontSizeExtraSmall
            visible: field2Error
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
        }
    }

    onAccepted: {
        value1 = field1.text
        value2 = field2.text
        var num1 = parseFloat(value1)
        var num2 = parseFloat(value2)
        result = (num1 + num2).toString()
    }

    function validateInput(field, fieldNumber) {
        var text = field.text
        var isValid = text !== "" && !isNaN(text)

        if (fieldNumber === 1) {
            field1Error = !isValid
        } else {
            field2Error = !isValid
        }
    }
}
