add_executable(
        FileSystemWatcherApp
        WIN32
        main.cpp
        FileSystemWatcher.cpp
        FileSystemWatcher.h
)

target_link_libraries(
        FileSystemWatcherApp
        PRIVATE
        ${QTLIBS}
)