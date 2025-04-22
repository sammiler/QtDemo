add_executable(
        CardLayout
        WIN32
        main.cpp
        QCardLayout.h
        QCardLayout.cpp
)

target_link_libraries(
        CardLayout
        PRIVATE
        ${QTLIBS}
)