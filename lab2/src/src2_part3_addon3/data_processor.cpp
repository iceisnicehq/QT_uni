#include "data_processor.h"

void DataProcessor::processData(const QString &input)
{
    QString processedData = "Обработано: " + input;
    emit dataProcessed(processedData);
}

// Если проект на старом qmake без нормального автоматического moc
// можно раскомментировать эту строку
//#include "data_processor.moc"
