add_executable(
        ToolButton
        WIN32
        main.cpp
)

target_link_libraries(
        ToolButton
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)