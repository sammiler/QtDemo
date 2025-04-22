
# 处理 Qt 资源文件 (.qrc)
qt5_add_resources(SOURCES_RCC resources.qrc)

add_executable(FramelessHelperExample
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h             # 包含 Q_OBJECT，需要 moc 处理
        frameless_helper.cpp
        frameless_helper.h       # 包含 Q_OBJECT，需要 moc 处理
        widgetdata.cpp
        widgetdata.h
        CursorPosCalculator.h
        CursorPosCalculator.cpp
        FramelessHelperPrivate.h
        ${SOURCES_RCC}           # 包含资源文件编译结果
)

# 链接所需的 Qt 模块库
target_link_libraries(FramelessHelperExample
        PRIVATE
        Qt5::Core    # QObject, QHash, QList, QPoint, QRect, QRubberBand (需要 Core, Gui, Widgets)
        Qt5::Gui     # QMouseEvent, QHoverEvent, QCursor, Qt::CursorShape, QWindowFlags, frameGeometry(), mapToGlobal() 等需要 Gui
        Qt5::Widgets # QWidget, QApplication, QRubberBand, childAt() 等需要 Widgets
)

