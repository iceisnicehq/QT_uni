#include "mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(const QString &userType, QWidget *parent)
    : QMainWindow(parent), currentUser(userType), connectedDeviceName("")
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *messageLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    userLabel = new QLabel(QString("Пользователь %1").arg(userType));
    chatDisplay = new QTextEdit();
    chatDisplay->setReadOnly(true);
    messageEdit = new QLineEdit();
    sendButton = new QPushButton("Отправить");
    scanButton = new QPushButton("Поиск устройств");
    disconnectButton = new QPushButton("Отключиться");
    connectionStatus = new QLabel("Не подключено");
    sendFileButton = new QPushButton("Отправить файл");
    sendFileButton->setEnabled(false);
    statusBar = new QStatusBar();
    setStatusBar(statusBar);

    messageLayout->addWidget(messageEdit);
    messageLayout->addWidget(sendButton);

    buttonLayout->addWidget(scanButton);
    buttonLayout->addWidget(disconnectButton);
    buttonLayout->addWidget(sendFileButton);

    mainLayout->addWidget(userLabel);
    mainLayout->addWidget(chatDisplay);
    mainLayout->addLayout(messageLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(connectionStatus);

    setWindowTitle(QString("Bluetooth эмулятор - Пользователь %1").arg(userType));
    resize(500, 400);

    deviceEmulator = new DeviceEmulator(userType, this);

    connect(scanButton, &QPushButton::clicked, this, &MainWindow::on_scanButton_clicked);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
    connect(disconnectButton, &QPushButton::clicked, this, &MainWindow::on_disconnectButton_clicked);
    connect(deviceEmulator, &DeviceEmulator::textReceived, this, &MainWindow::onTextReceived);
    connect(deviceEmulator, &DeviceEmulator::fileReceived, this, &MainWindow::onFileReceived);
    connect(deviceEmulator, &DeviceEmulator::connectionEstablished, this, &MainWindow::onConnectionEstablished);
    connect(deviceEmulator, &DeviceEmulator::connectionLost, this, &MainWindow::onConnectionLost);
    connect(sendFileButton, &QPushButton::clicked, this, &MainWindow::on_sendFileButton_clicked);
    sendButton->setEnabled(false);
    disconnectButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete deviceEmulator;
}

void MainWindow::on_scanButton_clicked()
{
    DeviceSelectionDialog dialog(currentUser, this);
    connect(&dialog, &DeviceSelectionDialog::deviceSelected, this, &MainWindow::onDeviceSelected);
    dialog.exec();
}

void MainWindow::on_sendButton_clicked()
{
    QString message = messageEdit->text();
    if (!message.isEmpty()) {
        deviceEmulator->sendText(message);
        chatDisplay->append(QString("[Вы]: %1").arg(message));
        messageEdit->clear();
    }
}

void MainWindow::on_disconnectButton_clicked()
{
    deviceEmulator->disconnect();
}

void MainWindow::onDeviceSelected(const QString &uuid)
{
    if (deviceEmulator->connectToDevice(uuid)) {
        connectedDeviceName = (uuid == "550e8400-e29b-41d4-a716-446655440000") ? "Устройство A" : "Устройство B";
        statusBar->showMessage(QString("Подключение к %1...").arg(connectedDeviceName));
    } else {
        statusBar->showMessage("Ошибка подключения", 3000);
    }
}

void MainWindow::onTextReceived(const QString &text) {
    chatDisplay->append(QString("[%1]: %2").arg(connectedDeviceName, text));
}

void MainWindow::onFileReceived(const QString &fileName, const QByteArray &fileData) {
    QString savePath = QDir::homePath() + "/" + fileName;
    QFile file(savePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(fileData);
        file.close();
        chatDisplay->append(QString("[Система]: Получен файл \"%1\", сохранён").arg(fileName));
    } else {
        chatDisplay->append(QString("[Система]: Не удалось сохранить файл \"%1\"").arg(fileName));
    }
}


void MainWindow::onConnectionEstablished()
{
    if (connectedDeviceName.isEmpty()) {
        connectedDeviceName = (currentUser == "A") ? "Устройство B" : "Устройство A";
    }

    connectionStatus->setText(QString("Подключено к %1").arg(connectedDeviceName));
    sendButton->setEnabled(true);
    sendFileButton->setEnabled(true);
    scanButton->setEnabled(false);
    disconnectButton->setEnabled(true);
    statusBar->showMessage("Подключение установлено", 3000);
}

void MainWindow::onConnectionLost()
{
    connectionStatus->setText("Не подключено");
    sendButton->setEnabled(false);
    sendFileButton->setEnabled(false);
    scanButton->setEnabled(true);
    disconnectButton->setEnabled(false);
    statusBar->showMessage("Соединение разорвано", 3000);
    chatDisplay->append("> Соединение потеряно");
}

void MainWindow::on_sendFileButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл для отправки");
    if (!filePath.isEmpty()) {
        sendFileToDevice(filePath);
    }
}

void MainWindow::sendFileToDevice(const QString& filePath) {
    if (!filePath.isEmpty()) {
        deviceEmulator->sendFile(filePath);
        chatDisplay->append(QString("[Система]: Отправка файла \"%1\"...").arg(QFileInfo(filePath).fileName()));
    }
}
