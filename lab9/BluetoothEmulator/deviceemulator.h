#ifndef DEVICEEMULATOR_H
#define DEVICEEMULATOR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>

class DeviceEmulator : public QObject
{
    Q_OBJECT

public:
    explicit DeviceEmulator(const QString &userType, QObject *parent = nullptr);
    ~DeviceEmulator();

    bool connectToDevice(const QString &uuid);
    void sendData(const QString &data);
    void disconnect();
    bool isConnected() const;

signals:
    void dataReceived(const QString &data);
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
};

#endif // DEVICEEMULATOR_H

