add_executable(
        TreeTableLayout
        WIN32
        main.cpp
)

target_link_libraries(
        TreeTableLayout
        PRIVATE
        ${QTLIBS}
)