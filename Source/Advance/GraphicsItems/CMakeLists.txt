

# Add the executable
add_executable(GraphicsItem
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h # Use WIN32 for a standard Windows GUI application
        resources/resources.qrc
        SmileItem.cpp
        SmileItem.h
)

# Link Qt libraries to the executable
target_link_libraries(GraphicsItem
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)