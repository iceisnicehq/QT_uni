// SPDX-FileCopyrightText: 2023 Open Mobile Platform LLC <edu@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

import QtQuick 2.0

Item {
    width: 400; height: 600

    // Фон на весь экран
    Rectangle {
        anchors.fill: parent
        color: starMouseArea.pressed ? "#c612ee" : "#ffe604"
        z: -1
        Behavior on color { ColorAnimation { duration: 700 } }
    }

    // Верхнее изображение (не перекрывает центр)
    Image {
        id: image
        source: Qt.resolvedUrl("images/ya.svg")
        fillMode: Image.PreserveAspectFit
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        width: parent.width
        height: parent.height / 3
        rotation: 0
        MouseArea {
            anchors.fill: parent
            onClicked: rotAnim.running = true
        }
        PropertyAnimation {
            id: rotAnim
            target: image
            property: "rotation"
            to: image.rotation + 360
            duration: 2000
            running: false
        }
    }

    // Звезда с кругом по центру
    Item {
        width: 120; height: 120
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        z: 1

        // Круг появляется при нажатии
        Rectangle {
            width: 110; height: 110
            anchors.centerIn: parent
            color: "transparent"
            border.color: "#f80000"
            border.width: 6
            radius: 55
            opacity: starMouseArea.pressed ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: 300 } }
        }

        // звезда (по умолчанию)
        Image {
            source: Qt.resolvedUrl("images/star.svg")
            anchors.centerIn: parent
            width: 90; height: 90
            fillMode: Image.PreserveAspectFit
            visible: !starMouseArea.pressed
        }
        // звезда (при нажатии)
        Image {
            source: Qt.resolvedUrl("images/star2.svg")
            anchors.centerIn: parent
            width: 90; height: 90
            fillMode: Image.PreserveAspectFit
            visible: starMouseArea.pressed
        }
        MouseArea {
            id: starMouseArea
            anchors.fill: parent
        }
    }

    // Кнопка для вращения SVG
    Rectangle {
        id: rotateBtn
        width: 80; height: 80
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.verticalCenter
        anchors.topMargin: 150
        z: 2
        color: btnPressed ? "#FF0900" : "#00ff15"
        radius: 40
        border.color: "#00ffdd"
        border.width: 2
        property bool btnPressed: false
        property real btnRotation: 0
        Behavior on color { ColorAnimation { duration: 200; easing.type: Easing.InOutQuad } }
        Behavior on btnRotation { NumberAnimation { duration: 2000; easing.type: Easing.InOutQuad } }
        Behavior on scale { NumberAnimation { duration: 200; easing.type: Easing.InOutQuad } }
        scale: btnPressed ? 1.15 : 1.0
        Image {
            source: Qt.resolvedUrl("images/arrow.svg")
            anchors.centerIn: parent
            width: 48; height: 48
            fillMode: Image.PreserveAspectFit
            rotation: rotateBtn.btnRotation
        }
        MouseArea {
            anchors.fill: parent
            onPressed: rotateBtn.btnPressed = true
            onReleased: rotateBtn.btnPressed = false
            onClicked: {
                rotAnim.running = true;
                rotateBtn.btnRotation += 360;
            }
        }
    }
}
