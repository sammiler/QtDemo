

# 查找 Qt5 库及其所需的模块
find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED) # QLocalServer/Socket 需要 Network 模块

# 定义共享的包含目录，以便两个子项目都能找到 ipc_defs.h
include_directories(${CMAKE_SOURCE_DIR})

# --- 配置服务器应用程序 ---
add_executable(FortuneServer
        WIN32 # Windows GUI 子系统应用
        server/server_main.cpp
        server/serverwindow.cpp
        server/serverwindow.h # 包含 Q_OBJECT，需要 moc 处理
        ipc_defs.h            # 共享头文件，列在这里以便 CMake/IDE 识别项目文件
)

# 链接服务器应用程序所需的库
target_link_libraries(FortuneServer
        PRIVATE
        Qt5::Core    # 基本模块
        Qt5::Gui     # QMessageBox 需要 Gui
        Qt5::Widgets # QWidget, QPushButton 需要 Widgets
        Qt5::Network # QLocalServer, QLocalSocket 需要 Network
)




# --- 配置客户端应用程序 ---
add_executable(FortuneClient
        WIN32 # Windows GUI 子系统应用
        client/client_main.cpp
        client/clientwindow.cpp
        client/clientwindow.h # 包含 Q_OBJECT，需要 moc 处理
        ipc_defs.h            # 共享头文件
)

# 链接客户端应用程序所需的库
target_link_libraries(FortuneClient
        PRIVATE
        Qt5::Core    # 基本模块
        Qt5::Gui     # QMessageBox 需要 Gui
        Qt5::Widgets # QWidget, QLabel, QLineEdit, QPushButton 需要 Widgets
        Qt5::Network # QLocalSocket 需要 Network
)

