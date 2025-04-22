add_executable(
        ToolBox
        WIN32
        main.cpp
        Resource/resources.qrc
)

target_link_libraries(
        ToolBox
        PRIVATE
        ${QTLIBS}
)