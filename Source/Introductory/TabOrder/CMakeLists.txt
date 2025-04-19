

qt5_add_resources(SOURCES_RCC resources.qrc)

add_executable(TabOrderExample
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h          # 包含 Q_OBJECT，需要 moc 处理
        ${SOURCES_RCC}        # 包含资源文件编译结果
)

# 链接所需的 Qt 模块库
target_link_libraries(TabOrderExample
        PRIVATE
        Qt5::Core    # QObject, QString 等
        Qt5::Gui     # 基本 GUI 功能
        Qt5::Widgets # QWidget, QPushButton, QLineEdit, QLayouts, QApplication 等
)

