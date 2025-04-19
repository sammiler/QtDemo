


add_executable(PasswordLineEdit
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h          # 包含 Q_OBJECT，需要 moc 处理
        password_event_filter.cpp
        password_event_filter.h # 包含 Q_OBJECT，需要 moc 处理
        password_line_edit.cpp
        password_line_edit.h  # 包含 Q_OBJECT，需要 moc 处理
)

# 链接所需的 Qt 模块库
target_link_libraries( PasswordLineEdit
        PRIVATE
        Qt5::Core    # QObject, QEvent, QByteArray 等
        Qt5::Gui     # QKeyEvent, QMouseEvent, QKeySequence, qobject_cast 等
        Qt5::Widgets # QWidget, QLineEdit, QApplication, QMessageBox, QLayouts, QLabel 等
)

