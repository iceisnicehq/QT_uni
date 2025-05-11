#include "filesearcher.h"
#include <QDirIterator>
#include <QFile>
#include <QTextStream>

FileSearcher::FileSearcher(QObject *parent) : QObject(parent) {}

void FileSearcher::search(const QString &rootDir, const QString &extension,
                         const QString &content, qint64 minSize, qint64 maxSize)
{
    m_cancelRequested = false;
    QDir dir(rootDir);
    processDirectory(dir, extension, content, minSize, maxSize);
    emit finished();
}

void FileSearcher::processDirectory(const QDir &dir, const QString &extension,
                                   const QString &content, qint64 minSize, qint64 maxSize)
{
    if (m_cancelRequested) return;

    // Поиск в текущей директории
    for (const auto &fileInfo : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
        if (matchesCriteria(fileInfo, extension, content, minSize, maxSize)) {
            emit resultFound(fileInfo.absoluteFilePath());
        }
        m_progress.fetchAndAddRelaxed(1);
        emit progressUpdated(m_progress);
    }

    // Рекурсивный поиск в поддиректориях
    for (const auto &subDir : dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        processDirectory(QDir(dir.filePath(subDir)), extension, content, minSize, maxSize);
    }
}

bool FileSearcher::matchesCriteria(const QFileInfo &file, const QString &extension,
                                  const QString &content, qint64 minSize, qint64 maxSize) const
{
    // Проверка размера
    if (file.size() < minSize || (maxSize > 0 && file.size() > maxSize))
        return false;

    if (!extension.isEmpty()) {
        QString normalizedExtension = extension.startsWith('.') ? extension.mid(1) : extension;
        if (file.suffix().compare(normalizedExtension, Qt::CaseInsensitive) != 0)
            return false;
    }

    // Поиск содержимого (только для текстовых файлов)
    if (!content.isEmpty()) {
        QFile f(file.absoluteFilePath());
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&f);
            while (!stream.atEnd()) {
                if (stream.readLine().contains(content))
                    return true;
            }
        }
        return false;
    }

    return true;
}

int FileSearcher::countFiles(const QDir &dir) const
{
    int count = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot).size();
    for (const auto &subDir : dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        count += countFiles(QDir(dir.filePath(subDir)));
    }
    return count;
}
