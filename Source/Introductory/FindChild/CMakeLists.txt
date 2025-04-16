add_executable(FindChild
    WIN32
    main.cpp
    widget.h
    widget.cpp  
)

target_link_libraries(
    FindChild
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)