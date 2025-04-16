add_executable(LCD 
    WIN32
    main.cpp 
)

target_link_libraries(
    LCD
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)