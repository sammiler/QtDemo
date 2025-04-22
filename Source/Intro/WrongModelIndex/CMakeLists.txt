




# Define the executable target
# Use WIN32 flag for Windows GUI application
# List ALL source files (.cpp) AND the moc-generated sources (${SOURCES_MOC})
add_executable(MapToSourceDemo # Changed target name
        WIN32
        main.cpp
        correctmainwindow.h
        correctmainwindow.cpp
        incorrectmainwindow.h
        incorrectmainwindow.cpp
        tablemodel.h
        TableModel.cpp
        SortFilterProxyModel.h
        SortFilterProxyModel.cpp
        SortDelegate.cpp
        SortDelegate.h
)

# Link the necessary Qt libraries to your executable
target_link_libraries(MapToSourceDemo
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# Optional: Install the executable
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)