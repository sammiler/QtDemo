# 最小CMake版本要求
cmake_minimum_required(VERSION 3.5)

# 项目名称和支持的语言
project(CustomFramelessWindow LANGUAGES CXX)

# 查找 Qt5 库及其所需的模块
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# 处理 Qt 资源文件 (.qrc)
# 这会将资源文件编译成 C++ 代码，供应用程序使用
qt5_add_resources(SOURCES_RCC resources.qrc)

# 定义可执行文件
# WIN32 标志在 Windows 上创建 GUI 子系统应用，不显示控制台窗口
# 列出所有需要编译的源文件 (.cpp)
# 列出包含 Q_OBJECT 宏的头文件 (.h)，以便 Qt 的 find_package 配置的逻辑进行 moc 处理
# 包含资源文件编译生成的源文件 (${SOURCES_RCC})
add_executable(CustomFramelessWindow
        WIN32
        main.cpp
        customwindow.cpp
        customwindow.h      # 包含 Q_OBJECT (如果 CustomWindow 有信号槽)
        title_bar.cpp
        title_bar.h         # 包含 Q_OBJECT，需要 moc 处理
        ${SOURCES_RCC}      # 包含资源文件编译生成的源文件
)

# 链接所需的 Qt 模块库
target_link_libraries(CustomFramelessWindow
        PRIVATE
        Qt5::Core
        Qt5::Gui     # QMouseEvent, QIcon, QPixmap 需要 Gui
        Qt5::Widgets # QWidget, QLabel, QPushButton, QVBoxLayout, QHBoxLayout, QApplication, QStyle 需要 Widgets
)



