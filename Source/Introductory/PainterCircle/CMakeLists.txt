add_executable(PathCircle
        WIN32
        main.cpp
        MainWindow.cpp
        MainWindow.h
        PathWidget.cpp
        PathWidget.h
)

target_link_libraries(PathCircle
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)