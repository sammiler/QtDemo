# 定义可执行文件
# WIN32 标志在 Windows 上创建 GUI 子系统应用
# 列出所有需要编译的源文件 (.cpp) 和包含 Q_OBJECT 宏的头文件 (.h)
add_executable(SwitchControl
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h          # 包含 Q_OBJECT，需要 moc 处理
        SwitchControl.cpp
        SwitchControl.h       # 包含 Q_OBJECT，需要 moc 处理
)

# 链接所需的 Qt 模块库
target_link_libraries(SwitchControl
        PRIVATE
        Qt5::Core    # QObject, QTimer, QColor, qreal, qint16, etc.
        Qt5::Gui     # QPainter, QMouseEvent, QPaintEvent, QResizeEvent, QColor, QPainterPath, Qt::, QSize, QPoint, QWidget::event, QCursor etc.
        Qt5::Widgets # QWidget, QApplication, QSize, QLayouts
)

