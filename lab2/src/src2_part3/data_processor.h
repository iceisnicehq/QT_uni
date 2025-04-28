#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QObject>

class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void processData(const QString &input);

signals:
    void dataProcessed(const QString &result);
};

#endif // DATA_PROCESSOR_H
