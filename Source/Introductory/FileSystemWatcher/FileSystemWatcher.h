#ifndef FILE_SYSTEM_WATCHER_H
#define FILE_SYSTEM_WATCHER_H

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    static FileSystemWatcher* instance();
    void addWatchPath(const QString& path);
    QMap<QString,QStringList> getContentsMap() const;
    public slots:
        void directoryUpdated(const QString& path);  // 目录更新时调用
    void fileUpdated(const QString& path);       // 文件修改时调用

private:
    explicit FileSystemWatcher(QObject* parent = nullptr);

private:
    static FileSystemWatcher* m_pInstance;       // 单例实例
    QFileSystemWatcher* m_pSystemWatcher;        // QFileSystemWatcher 对象
    QMap<QString, QStringList> m_currentContentsMap; // 监控路径的内容列表
};

#endif // FILE_SYSTEM_WATCHER_H