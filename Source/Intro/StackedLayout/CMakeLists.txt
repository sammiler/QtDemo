add_executable(
        StackedLayout
        WIN32
        main.cpp
)

target_link_libraries(
        StackedLayout
        PRIVATE
        ${QTLIBS}
)