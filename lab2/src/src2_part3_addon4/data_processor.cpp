#include "data_processor.h"

DataProcessor::DataProcessor(QObject *parent) : QObject(parent) {}

void DataProcessor::processData(const QString &input) {
    QString processedData = "Обработано: " + input;
    emit dataProcessed(processedData);
}
