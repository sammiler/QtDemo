find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

add_executable(
        NetworkInfo
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

target_link_libraries(
        NetworkInfo
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)