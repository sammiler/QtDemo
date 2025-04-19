add_executable(PathPainter
        WIN32
        main.cpp
        MainWindow.cpp
        MainWindow.h
        PathWidget.cpp
        PathWidget.h
)

# 链接 Qt 库
target_link_libraries(PathPainter
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)