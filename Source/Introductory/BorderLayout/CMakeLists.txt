add_executable(
        BorderLayout
        WIN32
        main.cpp
        QBorderLayout.h
        QBorderLayout.cpp
)

target_link_libraries(
        BorderLayout
        PRIVATE
        ${QTLIBS}
)