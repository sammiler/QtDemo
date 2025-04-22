add_executable(
        ProcessBar
        WIN32
        main.cpp
)

target_link_libraries(
        ProcessBar
        PRIVATE
        ${QTLIBS}
)
