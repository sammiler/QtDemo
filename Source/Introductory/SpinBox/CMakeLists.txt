add_executable(
        SpinBox
        WIN32
        main.cpp
)

target_link_libraries(
        SpinBox
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)