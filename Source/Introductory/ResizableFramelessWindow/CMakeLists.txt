add_executable(ResizableFramelessWindow
        WIN32
        main.cpp
        resizableframelesswidget.cpp
        resizableframelesswidget.h # 包含 Q_OBJECT (如果添加了), 需要 moc 处理
)

# 链接所需的 Qt 模块库
target_link_libraries(ResizableFramelessWindow
        PRIVATE
        Qt5::Core    # QObject, geometry() 需要 Core
        Qt5::Gui     # QWindow, nativeEvent(), QMouseEvent (如果用), Q_OS_WIN, etc. 需要 Gui
        Qt5::Widgets # QWidget, QApplication, childAt() 需要 Widgets
)

