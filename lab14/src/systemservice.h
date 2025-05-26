#pragma once

#include <QObject>
#include <QVariantMap>

class SystemService : public QObject
{
    Q_OBJECT
public:
    explicit SystemService(QObject *parent = nullptr);

    Q_PROPERTY(bool authenticated READ isAuthenticated NOTIFY authenticatedChanged)
    Q_PROPERTY(QVariantMap deviceParameters READ getDeviceParameters NOTIFY deviceParametersChanged)

    bool isAuthenticated() const { return m_authenticated; }
    Q_INVOKABLE bool checkPassword(const QString &password);
    Q_INVOKABLE QVariantMap getSystemInfo();
    Q_INVOKABLE QVariantMap getDeviceParameters();
    Q_INVOKABLE void setDeviceParameter(const QString &name, const QVariant &value);

    // D-Bus методы системных настроек
    Q_INVOKABLE void setBrightness(int value);
    Q_INVOKABLE void setVolume(int value);
    Q_INVOKABLE void setRingerMode(const QString &mode);

    Q_INVOKABLE void sendNotification(const QString &message);

signals:
    void notificationSent(const QString &message);
    void authenticatedChanged(bool);
    void deviceParametersChanged();

private:
    bool m_authenticated = false;
    QVariantMap m_deviceParams;
};
