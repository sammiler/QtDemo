//
// Created by sammiler on 2025/4/18.
//

#include "CursorPosCalculator.h"


// 初始化 CursorPosCalculator 的静态成员
int CursorPosCalculator::m_nBorderWidth = 5;
int CursorPosCalculator::m_nTitleHeight = 30;

/***** CursorPosCalculator 实现 *****/
CursorPosCalculator::CursorPosCalculator()
{
    reset(); // 构造时重置所有标志
}

void CursorPosCalculator::reset()
{
    m_bOnEdges = false;
    m_bOnLeftEdge = false;
    m_bOnRightEdge = false;
    m_bOnTopEdge = false;
    m_bOnBottomEdge = false;
    m_bOnTopLeftEdge = false;
    m_bOnBottomLeftEdge = false;
    m_bOnTopRightEdge  = false;
    m_bOnBottomRightEdge = false;
}

void CursorPosCalculator::recalculate(const QPoint &gMousePos, const QRect &frameRect)
{
    // 获取全局鼠标坐标
    int globalMouseX = gMousePos.x();
    int globalMouseY = gMousePos.y();

    // 获取窗口 frameGeometry 的坐标和尺寸
    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth = frameRect.width();
    int frameHeight = frameRect.height();

    // 计算鼠标是否在各个边框区域内
    m_bOnLeftEdge = (globalMouseX >= frameX &&
                     globalMouseX <= frameX + m_nBorderWidth );


    m_bOnRightEdge = (globalMouseX >= frameX + frameWidth - m_nBorderWidth &&
                      globalMouseX <= frameX + frameWidth);

    m_bOnTopEdge = (globalMouseY >= frameY &&
                    globalMouseY <= frameY + m_nBorderWidth );

    m_bOnBottomEdge = (globalMouseY >= frameY + frameHeight - m_nBorderWidth &&
                     globalMouseY <= frameY + frameHeight);

    // 计算鼠标是否在各个角落区域内 (同时满足两个边的条件)
    m_bOnTopLeftEdge = m_bOnTopEdge && m_bOnLeftEdge;
    m_bOnBottomLeftEdge = m_bOnBottomEdge && m_bOnLeftEdge;
    m_bOnTopRightEdge = m_bOnTopEdge && m_bOnRightEdge;
    m_bOnBottomRightEdge = m_bOnBottomEdge && m_bOnRightEdge;

    // 计算鼠标是否在任何边或角上
    m_bOnEdges = m_bOnLeftEdge || m_bOnRightEdge || m_bOnTopEdge || m_bOnBottomEdge;
}