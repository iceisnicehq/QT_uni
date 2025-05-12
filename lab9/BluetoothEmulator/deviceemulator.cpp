#include "deviceemulator.h"
#include <QMessageBox>
#include <QDebug>

DeviceEmulator::DeviceEmulator(const QString &userType, QObject *parent)
    : QObject(parent), userType(userType), server(new QTcpServer(this)), socket(nullptr)
{
    uuidToPortMap[QUuid("550e8400-e29b-41d4-a716-446655440000")] = 12345;
    uuidToPortMap[QUuid("550e8400-e29b-41d4-a716-446655440001")] = 12346;

    localUuid = (userType == "A")
        ? QUuid("550e8400-e29b-41d4-a716-446655440000")
        : QUuid("550e8400-e29b-41d4-a716-446655440001");

    if (!server->listen(QHostAddress::LocalHost, uuidToPortMap[localUuid])) {
        qCritical() << "Не удалось запустить сервер:" << server->errorString();
    } else {
        qDebug() << "Сервер запущен на порту" << uuidToPortMap[localUuid];
    }

    connect(server, &QTcpServer::newConnection, this, &DeviceEmulator::onNewConnection);
}

DeviceEmulator::~DeviceEmulator() {
    disconnect();
    server->close();
}

bool DeviceEmulator::connectToDevice(const QString &uuid) {
    QUuid targetUuid(uuid);
    if (!uuidToPortMap.contains(targetUuid) || targetUuid == localUuid) {
        return false;
    }

    if (socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
    }

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &DeviceEmulator::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &DeviceEmulator::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &DeviceEmulator::onSocketError);

    socket->connectToHost(QHostAddress::LocalHost, uuidToPortMap[targetUuid]);

    if (!socket->waitForConnected(3000)) {
        qWarning() << "Не удалось подключиться:" << socket->errorString();
        return false;
    }

    remoteUuid = targetUuid;
    emit connectionEstablished();
    return true;
}

void DeviceEmulator::sendData(const QString &data) {
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data.toUtf8());
        socket->flush();
    }
}

void DeviceEmulator::disconnect() {
    if (socket) {
        socket->disconnectFromHost();
    }
}

bool DeviceEmulator::isConnected() const {
    return socket && socket->state() == QAbstractSocket::ConnectedState;
}

void DeviceEmulator::onNewConnection() {
    if (socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
    }

    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &DeviceEmulator::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &DeviceEmulator::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &DeviceEmulator::onSocketError);

    quint16 peerPort = socket->peerPort();
    remoteUuid = (peerPort == 12345)
        ? QUuid("550e8400-e29b-41d4-a716-446655440000")
        : QUuid("550e8400-e29b-41d4-a716-446655440001");

    emit connectionEstablished();
}

void DeviceEmulator::onReadyRead() {
    if (socket) {
        QByteArray data = socket->readAll();
        emit dataReceived(QString::fromUtf8(data));
    }
}

void DeviceEmulator::onDisconnected() {
    emit connectionLost();
}

void DeviceEmulator::onSocketError(QAbstractSocket::SocketError error) {
    qWarning() << "Ошибка сокета:" << error;
    emit connectionLost();
}

