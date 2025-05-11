#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <QObject>
#include <QDir>
#include <QStringList>

class FileSearcher : public QObject
{
    Q_OBJECT

public:
    explicit FileSearcher(QObject *parent = nullptr);
    void search(const QString &rootDir, const QString &extension,
                const QString &content, qint64 minSize, qint64 maxSize);
    int countFiles(const QDir &dir) const;

signals:
    void resultFound(const QString &filePath);
    void progressUpdated(int value);
    void finished();

public slots:

private:
    bool m_cancelRequested = false;
    QAtomicInt m_progress = 0;

    void processDirectory(const QDir &dir, const QString &extension,
                          const QString &content, qint64 minSize, qint64 maxSize);
    bool matchesCriteria(const QFileInfo &file, const QString &extension,
                         const QString &content, qint64 minSize, qint64 maxSize) const;


};

#endif // FILESEARCHER_H
