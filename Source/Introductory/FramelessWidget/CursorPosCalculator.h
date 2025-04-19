

#pragma once

#include <QRect>

class CursorPosCalculator
{
public:
    explicit CursorPosCalculator();
    void reset();
    // 根据全局鼠标位置和窗口的 frameGeometry 计算鼠标命中的区域
    void recalculate(const QPoint &globalMousePos, const QRect &frameRect);

public:
    // 标志位，指示鼠标命中了哪个区域
    bool m_bOnEdges              : true; // 是否在任何边或角上
    bool m_bOnLeftEdge           : true; // 左边
    bool m_bOnRightEdge          : true; // 右边
    bool m_bOnTopEdge            : true; // 上边
    bool m_bOnBottomEdge         : true; // 下边
    bool m_bOnTopLeftEdge        : true; // 左上角
    bool m_bOnBottomLeftEdge     : true; // 左下角
    bool m_bOnTopRightEdge       : true; // 右上角
    bool m_bOnBottomRightEdge    : true; // 右下角

    // 静态成员，存储边框宽度和标题栏高度阈值，所有 FramelessHelper 实例共享
    static int m_nBorderWidth; // 边框宽度，用于缩放区域判断
    static int m_nTitleHeight; // 标题栏高度，用于拖动区域判断
};
