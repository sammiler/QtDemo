add_executable(
        GridLayout
        WIN32
        main.cpp
)

target_link_libraries(
        GridLayout
        PRIVATE
        ${QTLIBS}
)