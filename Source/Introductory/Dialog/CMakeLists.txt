add_executable(Dialog
    WIN32
    main.cpp
    mainwindow.h
    mainwindow.cpp
    customdialog.h
    customdialog.cpp 
)

target_link_libraries(
    Dialog
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)