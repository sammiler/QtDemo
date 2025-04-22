#include "FileSystemWatcher.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>

FileSystemWatcher* FileSystemWatcher::m_pInstance = nullptr;

FileSystemWatcher::FileSystemWatcher(QObject* parent)
    : QObject(parent)
    , m_pSystemWatcher(new QFileSystemWatcher(this))
{
    connect(m_pSystemWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::directoryUpdated);
    connect(m_pSystemWatcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::fileUpdated);
}

FileSystemWatcher* FileSystemWatcher::instance()
{
    if (!m_pInstance) {
        m_pInstance = new FileSystemWatcher();
    }
    return m_pInstance;
}

void FileSystemWatcher::addWatchPath(const QString& path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    // 添加监控路径
    m_pSystemWatcher->addPath(path);

    // 如果是目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir()) {
        const QDir dir(path);
        m_currentContentsMap[path] = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

QMap<QString, QStringList> FileSystemWatcher::getContentsMap() const {
    return m_currentContentsMap;
}

void FileSystemWatcher::directoryUpdated(const QString& path)
{
    qDebug() << QString("Directory updated: %1").arg(path);

    // 获取当前内容列表
    QStringList currEntryList = m_currentContentsMap[path];
    const QDir dir(path);
    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

    // 添加的文件
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.toList();

    // 删除的文件
    QSet<QString> deletedFiles = currentDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.toList();

    // 更新内容列表
    m_currentContentsMap[path] = newEntryList;

    if (!newFile.isEmpty() && !deleteFile.isEmpty()) {
        // 文件/目录重命名
        if (newFile.count() == 1 && deleteFile.count() == 1) {
            qDebug() << QString("File Renamed from %1 to %2").arg(deleteFile.first(), newFile.first());
        }
    } else {
        // 新增文件/目录
        if (!newFile.isEmpty()) {
            qDebug() << "New Files/Dirs added:" << newFile;
        }
        // 删除文件/目录
        if (!deleteFile.isEmpty()) {
            qDebug() << "Files/Dirs deleted:" << deleteFile;
        }
    }
}

void FileSystemWatcher::fileUpdated(const QString& path)
{
    QFileInfo file(path);
    QString strPath = file.absolutePath();
    QString strName = file.fileName();
    qDebug() << QString("The file %1 at path %2 is updated").arg(strName, strPath);
}