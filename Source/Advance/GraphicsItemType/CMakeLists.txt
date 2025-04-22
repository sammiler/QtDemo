

# Add the executable
add_executable(GraphicsItemType
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
        custom_rect_item.cpp
        custom_rect_item.h # Use WIN32 for a standard Windows GUI application # Add source files
)

# Link Qt libraries to the executable
target_link_libraries(GraphicsItemType
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

