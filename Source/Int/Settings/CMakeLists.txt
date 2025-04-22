

add_executable(
        SettingsExample
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

target_link_libraries(
        SettingsExample
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)