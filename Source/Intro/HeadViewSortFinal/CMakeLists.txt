# Minimum required CMake version


# Find the Qt5 package with necessary modules

# Define the executable target
# WIN32 flag creates a GUI application on Windows
# List ALL source files (.cpp) AND the moc-generated sources (${SOURCES_MOC})
add_executable(HeadViewSortFinal
        WIN32 # Create a Windows GUI application
        main.cpp
        mainwindow.cpp
        mainwindow.h
        TableModel.cpp
        TableModel.h
        SortFilterProxyModel.cpp
        SortFilterProxyModel.h
        SortDelegate.h
        SortDelegate.cpp
)

# Link the necessary Qt libraries to your executable
# Use the simplified form requested
target_link_libraries(HeadViewSortFinal
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# Optional: Install the executable
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)