#include "advanced_data_processor.h"
#include <QDebug>

AdvancedDataProcessor::AdvancedDataProcessor(QObject *parent) : QObject(parent) {}

void AdvancedDataProcessor::toUpperCase(const QString &input) {
    QString result = input.toUpper();
    emit upperCaseDone(result);
}

void AdvancedDataProcessor::formatText(const QString &input) {
    QString result = "Обработано: " + input;
    emit formatDone(result);
}

void AdvancedDataProcessor::logResult(const QString &input) {
    qDebug() << "Log:" << input;
    emit logDone(input);
}
