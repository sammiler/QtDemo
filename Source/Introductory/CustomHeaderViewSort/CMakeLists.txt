




# Define the executable target
add_executable(
        CustomHeaderViewSort
        WIN32
        main.cpp
        mainwindow.h
        mainwindow.cpp
        TableModel.h
        TableModel.cpp
        SortFilterProxyModel.h
        SortFilterProxyModel.cpp
)

# Link the necessary Qt libraries to your executable
target_link_libraries(
        CustomHeaderViewSort
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# Optional: Install the executable (useful for deployment)
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)