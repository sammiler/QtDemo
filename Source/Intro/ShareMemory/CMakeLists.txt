
# 定义共享的包含目录，以便两个子项目都能找到 shared_defs.h
include_directories(${CMAKE_SOURCE_DIR})

# --- 配置写入者应用程序 ---
add_executable(SharedMemoryWrite
        WIN32 # Windows GUI 子系统应用
        writer/writer_main.cpp
        writer/writerwindow.cpp
        writer/writerwindow.h # 包含 Q_OBJECT，需要 moc 处理
        shared_defs.h         # 共享头文件，列在这里以便 CMake/IDE 识别项目文件
)

# 链接写入者应用程序所需的库
target_link_libraries(SharedMemoryWrite
        PRIVATE
        Qt5::Core
        Qt5::Gui # QFileDialog, QImage 需要 Gui 模块
        Qt5::Widgets # QWidget, QPushButton, QFileDialog 需要 Widgets 模块
)




# --- 配置读取者应用程序 ---
add_executable(ShareMemoryRead
        WIN32 # Windows GUI 子系统应用
        reader/reader_main.cpp
        reader/readerwindow.cpp
        reader/readerwindow.h # 包含 Q_OBJECT，需要 moc 处理
        shared_defs.h         # 共享头文件
)

# 链接读取者应用程序所需的库
target_link_libraries(ShareMemoryRead
        PRIVATE
        Qt5::Core    # QSharedMemory, QBuffer, QDataStream 需要 Core 模块
        Qt5::Gui     # QImage, QPixmap 需要 Gui 模块
        Qt5::Widgets # QWidget, QLabel, QPushButton 需要 Widgets 模块
)



