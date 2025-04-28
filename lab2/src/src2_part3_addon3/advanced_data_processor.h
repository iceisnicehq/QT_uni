#ifndef ADVANCED_DATA_PROCESSOR_H
#define ADVANCED_DATA_PROCESSOR_H

#include <QObject>
#include <QString>

class AdvancedDataProcessor : public QObject {
    Q_OBJECT
public:
    explicit AdvancedDataProcessor(QObject *parent = nullptr);

public slots:
    void toUpperCase(const QString &input);
    void formatText(const QString &input);
    void logResult(const QString &input);

signals:
    void upperCaseDone(const QString &result);
    void formatDone(const QString &result);
    void logDone(const QString &result);
};

#endif // ADVANCED_DATA_PROCESSOR_H
