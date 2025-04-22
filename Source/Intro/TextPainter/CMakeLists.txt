# 添加源文件
add_executable(TextPainter
        WIN32
        main.cpp
        MainWindow.cpp
        MainWindow.h
        TextWidget.cpp
        TextWidget.h
)

# 链接 Qt 库
target_link_libraries(TextPainter
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)