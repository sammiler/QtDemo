

# 定义可执行文件目标
# WIN32 标志用于在 Windows 上创建 GUI 子系统应用
# 列出所有需要编译的 .cpp 文件和 moc 生成的文件
add_executable(CustomProgressTableView
        WIN32
        main.cpp
        mainwindow.h
        mainwindow.cpp
        TableModel.h
        TableModel.cpp
        ProgressBarDelegate.h
        ProgressBarDelegate.cpp
        FileDownloadThread.cpp
        FileDownloadThread.h
)

# 链接所需的 Qt 库到可执行文件
target_link_libraries(CustomProgressTableView
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# 可选: 安装可执行文件
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)