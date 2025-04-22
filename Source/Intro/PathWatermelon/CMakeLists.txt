add_executable(PathWatermelon
        WIN32
        main.cpp
        MainWindow.cpp
        MainWindow.h
)

target_link_libraries(PathWatermelon
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)