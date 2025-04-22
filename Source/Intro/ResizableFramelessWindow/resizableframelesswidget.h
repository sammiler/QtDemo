#ifndef RESIZABLEFRAMELESSWIDGET_H
#define RESIZABLEFRAMELESSWIDGET_H

#include <QWidget> // 继承自 QWidget

// 仅在 Windows 平台包含 Windows 特定头文件
#ifdef Q_OS_WIN
#include <qt_windows.h> // 包含 Windows.h
// 需要 Windowsx.h 包含 GET_X_LPARAM, GET_Y_LPARAM 宏
// 有些环境中 qt_windows.h 可能包含了，但为了明确和兼容性，可以显式包含
#include <Windowsx.h>
#endif

class ResizableFramelessWidget : public QWidget
{
    // Q_OBJECT 可选，如果不需要自定义信号槽
    // Q_OBJECT

public:
    explicit ResizableFramelessWidget(QWidget *parent = nullptr);
    ~ResizableFramelessWidget();

protected:
    // 重写 nativeEvent 方法来处理原生窗口事件 (如 Windows 消息)
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override; // 使用 override 关键字

private:
    int m_nBorder = 5; // 鼠标位于边框缩放范围的宽度 (像素)
};

#endif // RESIZABLEFRAMELESSWIDGET_H