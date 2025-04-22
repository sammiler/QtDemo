add_executable(
        StackedWidget
        WIN32
        main.cpp
)

target_link_libraries(
        StackedWidget
        PRIVATE
        ${QTLIBS}
)