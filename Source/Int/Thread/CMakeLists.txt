add_executable( ThreadExample WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
        worker.cpp
        worker.h)

target_link_libraries( ThreadExample PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets )