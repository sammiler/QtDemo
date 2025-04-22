# Create executable
add_executable(
        DataSave
        WIN32
        main.cpp
        MainWindow.cpp
        PushButton.cpp
        MainWindow.h
        PushButton.h
        User.h
)

# Link Qt libraries
target_link_libraries(
        DataSave
        PRIVATE
        ${QTLIBS}
)