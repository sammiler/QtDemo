# 最小CMake版本要求
cmake_minimum_required(VERSION 3.5)



# 定义可执行文件
# WIN32 标志在 Windows 上创建 GUI 子系统应用，不显示控制台窗口
# 列出所有需要编译的源文件 (.cpp)
# 同时列出包含 Q_OBJECT 宏的头文件 (.h)，以便 Qt 的 find_package 配置的逻辑进行 moc 处理
add_executable(FramelessWindow
        WIN32
        main.cpp
        framelesswidget.cpp
        framelesswidget.h # 包含 Q_OBJECT，需要 moc 处理
)

# 链接所需的 Qt 模块库
target_link_libraries(FramelessWindow
        PRIVATE
        Qt5::Core
        Qt5::Gui     # QMouseEvent 需要 Gui
        Qt5::Widgets # QWidget 需要 Widgets
)

# 自动添加 Qt 的包含目录
