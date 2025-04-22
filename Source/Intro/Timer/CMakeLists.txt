add_executable(
    Timer
    main.cpp
    mytimerwindow.h
    mytimerwindow.cpp   
)

target_link_libraries(
    Timer
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)