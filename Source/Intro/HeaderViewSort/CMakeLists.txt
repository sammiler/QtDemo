add_executable(HeaderViewSort
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
        TableModel.h
        TableModel.cpp

)

# 链接所需的 Qt 模块库
target_link_libraries(HeaderViewSort
        PRIVATE
        Qt5::Core
        Qt5::Gui     # QMouseEvent, QIcon, QPixmap 需要 Gui
        Qt5::Widgets # QWidget, QLabel, QPushButton, QVBoxLayout, QHBoxLayout, QApplication, QStyle 需要 Widgets
)
