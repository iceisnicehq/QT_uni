import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: qsTr("Библиотека")

    property int currentBookId: -1

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            spacing: 10

            TextField {
                id: searchField
                placeholderText: "Поиск по названию, автору или жанру"
                Layout.fillWidth: true
                onTextChanged: {
                    bookModel.clear()
                    var books = database.searchBooks(text)
                    for (var i = 0; i < books.length; i++) {
                        bookModel.append(books[i])
                    }
                }
            }

            Button {
                text: "Добавить книгу"
                onClicked: {
                    currentBookId = -1
                    titleField.text = ""
                    authorField.text = ""
                    yearField.text = ""
                    genreField.text = ""
                    availableCheckBox.checked = true
                    bookFormPopup.open()
                }
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: 10
            Layout.rightMargin: 10

            ListView {
                id: bookListView
                width: parent.width
                height: parent.height
                clip: true
                spacing: 5
                model: ListModel { id: bookModel }

                delegate: ItemDelegate {
                    width: bookListView.width
                    height: 80
                    leftPadding: 10
                    rightPadding: 10

                    background: Rectangle {
                        color: "transparent"
                        border.color: "#eee"
                        radius: 5
                    }

                    RowLayout {
                        anchors.fill: parent
                        spacing: 10

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 5

                            Label {
                                text: title
                                font.bold: true
                                elide: Text.ElideRight
                                Layout.fillWidth: true
                            }

                            Label {
                                text: author + " (" + year + ")"
                                elide: Text.ElideRight
                                Layout.fillWidth: true
                            }

                            Label {
                                text: genre
                                color: "gray"
                                elide: Text.ElideRight
                                Layout.fillWidth: true
                            }
                        }

                        Label {
                            text: available ? "Доступна" : "Недоступна"
                            color: available ? "green" : "red"
                        }

                        RowLayout {
                            spacing: 5

                            Button {
                                text: "Изменить"
                                onClicked: {
                                    currentBookId = id
                                    titleField.text = title
                                    authorField.text = author
                                    yearField.text = year
                                    genreField.text = genre
                                    availableCheckBox.checked = available
                                    bookFormPopup.open()
                                }
                            }

                            Button {
                                text: "Удалить"
                                onClicked: {
                                    deleteDialog.bookId = id
                                    deleteDialog.open()
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: bookFormPopup
        width: Math.min(window.width * 0.9, 400)
        height: Math.min(window.height * 0.9, 350)
        x: (window.width - width) / 2
        y: (window.height - height) / 2
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        padding: 10

        ColumnLayout {
            anchors.fill: parent
            spacing: 10

            Label {
                text: currentBookId === -1 ? "Добавить книгу" : "Изменить книгу"
                font.bold: true
                font.pixelSize: 18
            }

            TextField {
                id: titleField
                placeholderText: "Название"
                Layout.fillWidth: true
            }

            TextField {
                id: authorField
                placeholderText: "Автор"
                Layout.fillWidth: true
            }

            TextField {
                id: yearField
                placeholderText: "Год издания"
                validator: IntValidator { bottom: 0; top: 2100 }
                Layout.fillWidth: true
            }

            TextField {
                id: genreField
                placeholderText: "Жанр"
                Layout.fillWidth: true
            }

            CheckBox {
                id: availableCheckBox
                text: "Доступна"
                checked: true
            }

            RowLayout {
                Button {
                    text: "Отмена"
                    Layout.fillWidth: true
                    onClicked: bookFormPopup.close()
                }

                Button {
                    text: currentBookId === -1 ? "Добавить" : "Сохранить"
                    Layout.fillWidth: true
                    onClicked: {
                        if (currentBookId === -1) {
                            if (database.addBook(titleField.text, authorField.text,
                                               parseInt(yearField.text),
                                               genreField.text,
                                               availableCheckBox.checked)) {
                                refreshBookList()
                                bookFormPopup.close()
                            }
                        } else {
                            if (database.updateBook(currentBookId, titleField.text,
                                                   authorField.text,
                                                   parseInt(yearField.text),
                                                   genreField.text,
                                                   availableCheckBox.checked)) {
                                refreshBookList()
                                bookFormPopup.close()
                            }
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: deleteDialog
        modal: true
        title: "Удаление книги"
        standardButtons: Dialog.Ok | Dialog.Cancel
        x: (window.width - width) / 2
        y: (window.height - height) / 2

        property int bookId: -1

        Label {
            text: "Вы уверены, что хотите удалить эту книгу?"
        }

        onAccepted: {
            if (database.deleteBook(bookId)) {
                refreshBookList()
            }
        }
    }

    function refreshBookList() {
        bookModel.clear()
        var books = database.getAllBooks()
        for (var i = 0; i < books.length; i++) {
            bookModel.append(books[i])
        }
    }

    Component.onCompleted: refreshBookList()
}
