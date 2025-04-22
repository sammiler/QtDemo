add_executable(GradientPainter
        WIN32
        main.cpp
        MainWindow.cpp
        MainWindow.h
        GradientWidget.cpp
        GradientWidget.h
)

# 链接 Qt 库
target_link_libraries(GradientPainter
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)