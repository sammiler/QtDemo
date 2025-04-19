add_executable(
        Coordinate
        WIN32
        main.cpp
)

target_link_libraries(
        Coordinate
        PRIVATE
        ${QTLIBS}
)