#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "deviceemulator.h"
#include "deviceselectiondialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &userType, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_scanButton_clicked();
    void on_sendButton_clicked();
    void on_disconnectButton_clicked();
    void on_sendFileButton_clicked();
    void onDeviceSelected(const QString &uuid);
    void onTextReceived(const QString &text);
    void onFileReceived(const QString &fileName, const QByteArray &fileData);
    void onConnectionEstablished();
    void onConnectionLost();
    void sendFileToDevice(const QString& filePath);

private:
    QTextEdit *chatDisplay;
    QLineEdit *messageEdit;
    QPushButton *sendButton;
    QPushButton *scanButton;
    QPushButton *disconnectButton;
    QLabel *userLabel;
    QLabel *connectionStatus;
    QStatusBar *statusBar;
    bool lastReceivedWasFile = false;

    DeviceEmulator *deviceEmulator;
    QString currentUser;
    QString connectedDeviceName;
    QPushButton* sendFileButton;
};

#endif // MAINWINDOW_H
