import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: qsTr("Библиотека")

    property int currentBookId: -1
    property int currentAvailabilityFilter: 0
    property int yearFrom: 0
    property int yearTo: 0
    property int currentReaderId: -1
    property int selectedBookId: -1
    property int selectedReaderId: -1

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            TabButton { text: "Книги" }
            TabButton { text: "Читатели" }
            TabButton { text: "Учет книг" }
        }

        StackLayout {
            id: stackLayout
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex

            ColumnLayout {
                spacing: 10
                Layout.fillWidth: true
                Layout.fillHeight: true

                RowLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    spacing: 10

                    TextField {
                            id: authorField2
                            placeholderText: "Автор"
                            Layout.fillWidth: true
                    }

                    TextField {
                        id: genreField2
                        placeholderText: "Жанр"
                        Layout.fillWidth: true
                    }

                    TextField {
                        id: yearFromField2
                        placeholderText: "Год от"
                        validator: IntValidator { bottom: 0; top: 9999 }
                        Layout.preferredWidth: 100
                        onTextChanged: yearFrom = text ? parseInt(text) : 0
                    }

                    TextField {
                        id: yearToField2
                        placeholderText: "Год до"
                        validator: IntValidator { bottom: 0; top: 9999 }
                        Layout.preferredWidth: 100
                        onTextChanged: yearTo = text ? parseInt(text) : 0
                    }

                    ComboBox {
                        id: availabilityCombo
                        model: ["Все", "Доступные", "Недоступные"]
                        Layout.preferredWidth: 150
                        onCurrentIndexChanged: currentAvailabilityFilter = currentIndex
                    }

                    Button {
                        text: "Поиск"
                        onClicked: refreshBookList()
                    }

                    Button {
                        text: "Сброс"
                        onClicked: {
                            authorField2.text = ""
                            genreField2.text = ""
                            yearFromField2.text = ""
                            yearToField2.text = ""
                            availabilityCombo.currentIndex = 0
                            refreshBookList()
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

                    Button {
                        text: "Экспорт в Excel"
                        onClicked: {
                            var savePath = Qt.openUrlExternally("file://" + Qt.resolvedUrl("."))
                            fileDialog.open()
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

            ColumnLayout {
                            spacing: 10
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            RowLayout {
                                Layout.fillWidth: true
                                Layout.leftMargin: 10
                                Layout.rightMargin: 10
                                spacing: 10

                                Button {
                                    text: "Добавить читателя"
                                    onClicked: {
                                        currentReaderId = -1
                                        readerNameField.text = ""
                                        readerContactField.text = ""
                                        addReaderDialog.title = "Добавить читателя"
                                        addReaderDialog.open()
                                    }
                                }

                                Button { text: "Обновить список"; onClicked: refreshReadersList() }
                            }

                            ScrollView {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Layout.leftMargin: 10
                                Layout.rightMargin: 10

                                ListView {
                                    id: readerListView
                                    model: ListModel { id: readerModel }
                                    spacing: 5
                                    clip: true
                                    width: parent.width
                                    height: parent.height
                                    delegate: ItemDelegate {
                                        width: readerListView.width
                                        height: 60
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
                                                Label { text: name; font.bold: true; elide: Text.ElideRight; Layout.fillWidth: true }
                                                Label { text: contact; color: "gray"; elide: Text.ElideRight; Layout.fillWidth: true}
                                            }

                                            RowLayout {
                                                spacing: 5
                                                Button {
                                                    text: "Изменить"
                                                    onClicked: {
                                                        currentReaderId = id
                                                        readerNameField.text = name
                                                        readerContactField.text = contact
                                                        addReaderDialog.title = "Изменить читателя"
                                                        addReaderDialog.open()
                                                    }
                                                }

                                                Button {
                                                    text: "Удалить"
                                                    onClicked: {
                                                        deleteReaderDialog.readerId = id
                                                        deleteReaderDialog.open()
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    Component.onCompleted: refreshReadersList()
                                }
                            }
                        }

            ColumnLayout {
                    spacing: 10
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    RowLayout {
                        spacing: 10

                        ComboBox {
                            id: bookSelector
                            Layout.fillWidth: true
                            model: availableBooksModel
                            textRole: "display"
                            delegate: ItemDelegate {
                                text: model.display
                            }
                            onActivated: function(index) {
                                selectedBookId = model.get(index).id;
                            }
                        }

                        ComboBox {
                            id: readerSelector
                            Layout.fillWidth: true
                            model: readerModel
                            textRole: "name"
                            delegate: ItemDelegate {
                                text: model.name
                            }
                            onActivated: function(index) {
                                selectedReaderId = model.get(index).id;
                            }
                        }

                        Button {
                            text: "Выдать книгу"
                            enabled: selectedBookId > 0 && selectedReaderId > 0
                            onClicked: {
                                if (database.issueBook(selectedBookId, selectedReaderId)) {
                                    refreshLoans()
                                    refreshAvailableBooks()
                                    selectedBookId = -1
                                    selectedReaderId = -1
                                    bookSelector.currentIndex = -1
                                    readerSelector.currentIndex = -1
                                }
                            }
                        }
                    }

                    ListView {
                        id: loanList
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 6
                        clip: true
                        model: loanModel
                        delegate: ItemDelegate {
                            width: loanList.width
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
                                        text: `${bookTitle} — ${readerName}`
                                        font.bold: true
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }

                                    Label {
                                        text: `Выдана: ${issueDate}`
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }

                                    Label {
                                        text: returnDate !== "" ? `Возврат: ${returnDate}` : "На руках"
                                        color: "gray"
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }
                                }

                                RowLayout {
                                    visible: returnDate === ""
                                    spacing: 5
                                    Button {
                                        text: "Вернуть"
                                        onClicked: {
                                            if (database.returnBook(id)) {
                                                refreshLoans()
                                                refreshAvailableBooks()
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    property int selectedBookId: -1
                    property int selectedReaderId: -1

                    ListModel {
                        id: availableBooksModel
                    }

                    ListModel {
                        id: loanModel
                    }

                    Component.onCompleted: {
                        refreshAvailableBooks()
                        refreshReadersList()
                        refreshLoans()
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
        id: addReaderDialog
        modal: true
        title: "Добавить читателя"
        width: 400
        x: (window.width - width) / 2
        y: (window.height - height) / 2

        ColumnLayout {
            width: parent.width
            spacing: 10
            TextField { id: readerNameField; placeholderText: "ФИО"; Layout.fillWidth: true }
            TextField { id: readerContactField; placeholderText: "Контакт"; Layout.fillWidth: true }
        }

        footer: DialogButtonBox {
            Button {
                text: "Отмена"
                DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
                onClicked: addReaderDialog.close()
            }

            Button {
                text: addReaderDialog.title === "Добавить читателя" ? "Добавить" : "Сохранить"
                DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                onClicked: {
                    if (readerNameField.text.trim() === "" || readerContactField.text.trim() === "") return;

                    if (currentReaderId === -1) {
                        if (database.addReader(readerNameField.text, readerContactField.text)) {
                            refreshReadersList()
                            addReaderDialog.close();
                        }
                    } else {
                        if (database.updateReader(currentReaderId, readerNameField.text, readerContactField.text)) {
                            refreshReadersList()
                            addReaderDialog.close();
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

    Dialog {
        id: deleteReaderDialog
        modal: true
        title: "Удаление читателя"
        standardButtons: Dialog.Ok | Dialog.Cancel
        x: (window.width - width) / 2
        y: (window.height - height) / 2
        property int readerId: -1

        Label { text: "Вы уверены, что хотите удалить этого читателя?" }

        onAccepted: {
            if (database.deleteReader(readerId)) {
                refreshReadersList()
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Сохранить файл Excel"
        fileMode: FileDialog.SaveFile
        nameFilters: ["Excel files (*.xlsx)", "All files (*)"]
        defaultSuffix: "xlsx"

        onAccepted: {
            var filePath = selectedFile.toString().replace("file://", "")
            database.exportToExcel(filePath)
        }
    }

    function refreshBookList() {
        bookModel.clear()
        var books = database.searchBooksCombined(
            authorField2.text,
            genreField2.text,
            yearFrom,
            yearTo,
            currentAvailabilityFilter
        )
        for (var i = 0; i < books.length; i++) {
            bookModel.append(books[i])
        }
    }

    function refreshReadersList() {
        readerModel.clear();
        var readers = database.getAllReaders();
        for (var i = 0; i < readers.length; i++) {
            readerModel.append(readers[i]);
        }
    }

    function refreshAvailableBooks() {
        availableBooksModel.clear()
        const books = database.getAvailableBooks()
        for (var i = 0; i < books.length; ++i) {
            const book = books[i]
            availableBooksModel.append({
                id: book.id,
                display: book.title + " (" + book.author + ")"
            })
        }
    }

    function refreshLoans() {
        loanModel.clear()
        const loans = database.getAllLoans()
        for (var i = 0; i < loans.length; ++i) {
            loanModel.append(loans[i])
        }
    }

    Component.onCompleted: refreshBookList()
}
