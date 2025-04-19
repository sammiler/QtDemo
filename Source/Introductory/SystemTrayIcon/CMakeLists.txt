add_executable(
        SystemTrayIcon
        WIN32
        main.cpp
        Resource/resources.qrc
)

target_link_libraries(
        SystemTrayIcon
        PRIVATE
        ${QTLIBS}
)