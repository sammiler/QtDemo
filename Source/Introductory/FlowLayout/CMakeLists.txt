add_executable(
        FlowLayout
        WIN32
        main.cpp
        QFlowLayout.h
        QFlowLayout.cpp
)
target_link_libraries(
        FlowLayout
        PRIVATE
        ${QTLIBS}
)