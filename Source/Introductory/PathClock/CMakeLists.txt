add_executable(PathClock
        WIN32
        main.cpp
        ClockWidget.cpp
        ClockWidget.h
)

target_link_libraries(PathClock
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)