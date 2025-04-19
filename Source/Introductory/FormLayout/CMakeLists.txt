add_executable(
        FormLayout
        WIN32
        main.cpp
)

target_link_libraries(
        FormLayout
        PRIVATE
        ${QTLIBS}
)