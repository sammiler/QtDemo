#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QLocalServer> // 需要 QLocalServer
#include <QStringList>  // 需要 QStringList
#include <QMessageBox>  // 需要 QMessageBox
#include <QVBoxLayout>  // 需要布局
#include <QLabel>       // 需要 QLabel (可选, 显示状态)

class ServerWindow final : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow() override;

    private slots:
        void sendFortune(); // 当有新连接时发送数据

private:
    QLocalServer *server;     // 本地服务器对象
    QStringList fortunes;     // 存储财富语录的列表
    QLabel *statusLabel;      // 显示服务器状态 (可选)
};

#endif // SERVERWINDOW_H