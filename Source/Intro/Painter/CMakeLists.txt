add_executable(Painter
        WIN32
        main.cpp
        MainWindow.cpp
        MainWindow.h
        PaintWidget.cpp
        PaintWidget.h
        resources.qrc
)

# 链接 Qt 库
target_link_libraries(Painter
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)