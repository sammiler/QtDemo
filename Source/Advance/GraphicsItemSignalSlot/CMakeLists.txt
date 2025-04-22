# Add the executable
# Include custom_signaling_item.cpp in the executable source list
add_executable(GraphicsItemSignalSlot
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
        custom_signaling_item.cpp
        custom_signaling_item.h # Use WIN32 for a standard Windows GUI application
)

# Link Qt libraries to the executable
target_link_libraries(GraphicsItemSignalSlot
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
