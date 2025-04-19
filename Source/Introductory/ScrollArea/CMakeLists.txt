add_executable(
        ScrollArea
        WIN32
        main.cpp
        resources.qrc
)

target_link_libraries(
        ScrollArea
        PRIVATE
        ${QTLIBS}
)