add_executable(
        LineEdit
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

target_link_libraries(
        LineEdit
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)