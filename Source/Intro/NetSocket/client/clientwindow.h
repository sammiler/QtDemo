#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QLocalSocket> // 需要 QLocalSocket
#include <QDataStream>  // 需要 QDataStream
#include <QLineEdit>    // 需要 QLineEdit
#include <QPushButton>  // 需要 QPushButton
#include <QLabel>       // 需要 QLabel
#include <QMessageBox>  // 需要 QMessageBox
#include <QVBoxLayout>  // 需要布局

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

    private slots:
        void requestNewFortune(); // 请求新的财富语录
    void readFortune();       // 读取服务器发送的数据
    void displayError(QLocalSocket::LocalSocketError socketError); // 处理 socket 错误

private:
    QLocalSocket *socket;        // 本地 socket 对象
    quint16 blockSize;           // 存储接收到的数据块大小
    QLineEdit *hostLineEdit;     // 输入服务器名称的行编辑
    QLabel *statusLabel;         // 显示接收到的财富语录或状态信息
    QPushButton *getFortuneButton; // 请求按钮
    QString currentFortune;      // 存储当前显示的财富语录 (用于避免重复请求)
};

#endif // CLIENTWINDOW_H