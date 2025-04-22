add_executable(
        CheckBox
        WIN32
        main.cpp
        mainwindow.h
        mainwindow.cpp
)

target_link_libraries(
        CheckBox
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)