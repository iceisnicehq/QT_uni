#include "deviceemulator.h"
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QDir>
#include <QDebug>
#include <cstring>

static const quint8 GOST_KEY[32] = {
    0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
    0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF
};

QByteArray DeviceEmulator::gostEncrypt(const QByteArray &data) {
    QByteArray padded = data;
    int padding = 8 - (padded.size() % 8);
    padded.append(QByteArray(padding, static_cast<char>(padding))); // PKCS#5/7 padding

    QByteArray result;
    for (int i = 0; i < padded.size(); i += 8) {
        QByteArray block = padded.mid(i, 8);
        for (int j = 0; j < 8; ++j)
            block[j] = block[j] ^ GOST_KEY[j];
        result.append(block);
    }
    return result;
}


QByteArray DeviceEmulator::gostDecrypt(const QByteArray &data) {
    QByteArray decrypted;
    for (int i = 0; i < data.size(); i += 8) {
        QByteArray block = data.mid(i, 8);
        for (int j = 0; j < 8; ++j)
            block[j] = block[j] ^ GOST_KEY[j];
        decrypted.append(block);
    }

    // Удаление PKCS#5/7 padding
    if (!decrypted.isEmpty()) {
        int padding = static_cast<unsigned char>(decrypted.back());
        if (padding > 0 && padding <= 8 && decrypted.endsWith(QByteArray(padding, static_cast<char>(padding)))) {
            decrypted.chop(padding);
        }
    }

    return decrypted;
}

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
    if (!uuidToPortMap.contains(targetUuid) || targetUuid == localUuid) return false;

    if (socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
    }

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &DeviceEmulator::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &DeviceEmulator::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &DeviceEmulator::onSocketError);

    socket->connectToHost(QHostAddress::LocalHost, uuidToPortMap[targetUuid]);
    if (!socket->waitForConnected(3000)) return false;

    remoteUuid = targetUuid;
    emit connectionEstablished();
    return true;
}

void DeviceEmulator::sendText(const QString &text) {
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray encrypted = gostEncrypt(text.toUtf8());
        socket->write("TEXT" + encrypted);
        socket->flush();
    }
}

void DeviceEmulator::sendFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "[sendFile] Не удалось открыть файл:" << filePath;
        return;
    }

    QByteArray fileData = gostEncrypt(file.readAll());
    file.close();

    QString fileName = QFileInfo(filePath).fileName();
    QByteArray nameData = fileName.toUtf8();

    QByteArray payload;
    QDataStream stream(&payload, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream.writeRawData("FILE", 4);
    stream << quint16(nameData.size());
    stream.writeRawData(nameData.constData(), nameData.size());
    stream << quint32(fileData.size());
    stream.writeRawData(fileData.constData(), fileData.size());

    socket->write(payload);
    socket->flush();
    qDebug() << "[sendFile] Отправлен файл:" << fileName << ", размер:" << fileData.size();
}

void DeviceEmulator::disconnect() {
    if (socket) socket->disconnectFromHost();
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
    if (!socket) return;

    receiveBuffer.append(socket->readAll());

    while (receiveBuffer.size() >= 4) {
        QByteArray magic = receiveBuffer.left(4);
        if (magic == "TEXT") {
            QByteArray encrypted = receiveBuffer.mid(4);
            QByteArray decrypted = gostDecrypt(encrypted);
            emit textReceived(QString::fromUtf8(decrypted));
            receiveBuffer.clear();
            break;
        }
        else if (magic == "FILE") {
            if (receiveBuffer.size() < 6) return;

            QDataStream stream(receiveBuffer);
            stream.setByteOrder(QDataStream::BigEndian);

            stream.skipRawData(4); // skip "FILE"
            quint16 nameLen;
            stream >> nameLen;
            if (receiveBuffer.size() < 6 + nameLen + 4) return;

            QByteArray nameData = receiveBuffer.mid(6, nameLen);
            QString fileName = QString::fromUtf8(nameData);

            quint32 fileSize;
            stream.skipRawData(nameLen);
            stream >> fileSize;

            int totalSize = 6 + nameLen + 4 + fileSize;
            if (receiveBuffer.size() < totalSize) return;

            QByteArray fileData = receiveBuffer.mid(6 + nameLen + 4, fileSize);
            QByteArray decrypted = gostDecrypt(fileData);
            emit fileReceived(fileName, decrypted);
            receiveBuffer.remove(0, totalSize);
        } else {
            qWarning() << "Неизвестный тип сообщения";
            receiveBuffer.clear();
            break;
        }
    }
}

void DeviceEmulator::onDisconnected() {
    emit connectionLost();
}

void DeviceEmulator::onSocketError(QAbstractSocket::SocketError error) {
    qWarning() << "Ошибка сокета:" << error;
    emit connectionLost();
}
