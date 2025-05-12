#ifndef DEVICEEMULATOR_H
#define DEVICEEMULATOR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>
#include <QByteArray>
#include <QMap>

class DeviceEmulator : public QObject
{
    Q_OBJECT

public:
    explicit DeviceEmulator(const QString &userType, QObject *parent = nullptr);
    ~DeviceEmulator();

    bool connectToDevice(const QString &uuid);
    void sendText(const QString &text);
    void sendFile(const QString &filePath);
    void disconnect();
    bool isConnected() const;

signals:
    void textReceived(const QString &text);
    void fileReceived(const QString &fileName, const QByteArray &fileData);
    void connectionEstablished();
    void connectionLost();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QString userType;
    QUuid localUuid;
    QUuid remoteUuid;
    QMap<QUuid, quint16> uuidToPortMap;

    QByteArray receiveBuffer;
    quint32 expectedFileSize = 0;
    QString currentFileName;
    bool receivingFile = false;

    QByteArray gostEncrypt(const QByteArray &data);
    QByteArray gostDecrypt(const QByteArray &data);
};

#endif // DEVICEEMULATOR_H
