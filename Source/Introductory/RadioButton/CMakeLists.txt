add_executable(
        RadioButton
        WIN32
        main.cpp
        mainwindow.h
        mainwindow.cpp
)

target_link_libraries(
        RadioButton
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)