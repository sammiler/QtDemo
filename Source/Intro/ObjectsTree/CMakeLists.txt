add_executable(ObjectsTree
    WIN32
    main.cpp
)

target_link_libraries(
    ObjectsTree
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)