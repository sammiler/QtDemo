add_executable(PushButton 
    WIN32
    main.cpp
    tri_state_button.h
    tri_state_button.cpp  
)

target_link_libraries(
    PushButton 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)