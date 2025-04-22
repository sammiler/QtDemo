#ifndef IPC_DEFS_H
#define IPC_DEFS_H

#include <QString>

// 仅在 Windows 平台编译以下代码
#ifdef Q_OS_WIN
// #pragma comment 告诉编译器链接 user32.lib 库，其中包含 FindWindowW, SendMessage 等函数
#pragma comment(lib, "user32.lib")
// 包含 Qt 提供的 Windows 特定头文件包装器
#include <qt_windows.h>
#endif

// 用户自定义的消息类型，用于 WM_COPYDATA 结构体中的 dwData 字段
// 发送方和接收方必须一致，用于过滤消息
const ULONG_PTR CUSTOM_TYPE = 10000;

// 接收窗口的窗口标题，发送方使用 FindWindowW 来查找这个窗口
// 发送方和接收方必须一致
const QString RECEIVER_WINDOW_TITLE = "ReceiveMessage";

#endif // IPC_DEFS_H