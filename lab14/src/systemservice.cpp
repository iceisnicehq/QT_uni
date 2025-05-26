#include "systemservice.h"
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QProcess>
#include <QDebug>
#include <QFile>

const QString PASSWORD = "1234";

SystemService::SystemService(QObject *parent)
    : QObject(parent)
{
    m_deviceParams["brightness"] = 50;
    m_deviceParams["sound"] = 50;
    m_deviceParams["mode"] = "normal";
}

bool SystemService::checkPassword(const QString &password)
{
    bool ok = (password == PASSWORD);
    if (ok != m_authenticated) {
        m_authenticated = ok;
        emit authenticatedChanged(ok);
    }
    return ok;
}

QVariantMap SystemService::getSystemInfo()
{
    QVariantMap info;
    QFile file("/proc/stat");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString line = in.readLine();
        info["cpu_stat"] = line;
    }
    QFile memFile("/proc/meminfo");
    if (memFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&memFile);
        info["meminfo"] = in.readAll();
    }
    return info;
}

QVariantMap SystemService::getDeviceParameters()
{
    return m_deviceParams;
}

void SystemService::setDeviceParameter(const QString &name, const QVariant &value)
{
    if (!m_authenticated) return;
    m_deviceParams[name] = value;
    emit deviceParametersChanged();

    // Управление через D-Bus
    if (name == "brightness")
        setBrightness(value.toInt());
    else if (name == "sound")
        setVolume(value.toInt());
    else if (name == "mode")
        setRingerMode(value.toString());
}

void SystemService::setBrightness(int value)
{
    // value: 0-100, приводим к 0-255
    int dbusValue = qBound(0, (value * 255) / 100, 255);
    QDBusInterface mceIface("com.nokia.mce",
                            "/com/nokia/mce/request",
                            "com.nokia.mce.request",
                            QDBusConnection::systemBus());
    QDBusReply<void> reply = mceIface.call("set_display_brightness", dbusValue);
    qDebug() << "Set brightness to" << dbusValue << "reply:" << reply.isValid();
}

void SystemService::setVolume(int value)
{
    // value: 0-100
    int paValue = qBound(0, value, 100);
    QString cmd = QString("pactl set-sink-volume @DEFAULT_SINK@ %1%").arg(paValue);
    QProcess::execute("/bin/sh", QStringList() << "-c" << cmd);
    qDebug() << "Set volume to" << paValue << "%";
}

void SystemService::setRingerMode(const QString &mode)
{
    QDBusInterface mceIface("com.nokia.mce",
                            "/com/nokia/mce/request",
                            "com.nokia.mce.request",
                            QDBusConnection::systemBus());
    if (mode == "silent") {
        mceIface.call("req_audio_profile", "silent");
    } else if (mode == "vibrate") {
        mceIface.call("req_audio_profile", "vibrate");
    } else {
        mceIface.call("req_audio_profile", "general");
    }
    qDebug() << "Set ringer mode to" << mode;
}

void SystemService::sendNotification(const QString &message)
{
    if (!m_authenticated) return;
    emit notificationSent(message);
}
