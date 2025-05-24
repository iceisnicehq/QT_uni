// SPDX-FileCopyrightText: 2023 Open Mobile Platform LLC <edu@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

import QtQuick 2.0

Item {
    objectName: "Animations"

    Image {
        id: image
        objectName: "image"
        source: Qt.resolvedUrl("images/aurora.svg")
        fillMode: Image.PreserveAspectFit
        anchors { fill: parent; bottomMargin: parent.height / 2 }

        MouseArea {
            objectName: "imageMouseArea"
            anchors.fill: parent

            onClicked: imageAnimation.running = true
        }

        RotationAnimation on rotation {
            id: imageAnimation
            objectName: "imageAnimation"
            to: image.rotation + 360
            duration: 2000
            running: false
        }
    }

    Rectangle {
        id: rectangle
        objectName: "rectangle"
        color: "red"
        anchors { fill: parent; topMargin: parent.height / 2 }
        states: State {
            name: "blue"
            when: rectangleMouseArea.pressed

            PropertyChanges  { target: rectangle; color: "blue" }
        }
        transitions: [
            Transition {
                to: "blue"

                ColorAnimation { duration: 2000 }
            },
            Transition {
                from: "blue"

                ColorAnimation { duration: 500 }
            }
        ]

        MouseArea {
            id: rectangleMouseArea
            objectName: "rectangleMouseArea"
            anchors.fill: parent
        }
    }
}
