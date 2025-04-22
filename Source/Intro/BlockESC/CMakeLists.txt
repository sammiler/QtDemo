
add_executable(EscapeBehaviorExample
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h                  # 包含 Q_OBJECT，需要 moc 处理
        escape_filter.cpp
        escape_filter.h               # 包含 Q_OBJECT，需要 moc 处理
        default_escape_dialog.cpp
        default_escape_dialog.h       # 包含 Q_OBJECT，需要 moc 处理
        event_filter_escape_dialog.cpp
        event_filter_escape_dialog.h  # 包含 Q_OBJECT，需要 moc 处理
        key_press_override_dialog.cpp
        key_press_override_dialog.h   # 包含 Q_OBJECT，需要 moc 处理
        reject_override_dialog.cpp
        reject_override_dialog.h      # 包含 Q_OBJECT，需要 moc 处理
)

# 链接所需的 Qt 模块库
target_link_libraries(EscapeBehaviorExample
        PRIVATE
        Qt5::Core    # QObject, QEvent, QKeyEvent, QByteArray 等
        Qt5::Gui     # QKeyEvent, QKeySequence, qobject_cast 等
        Qt5::Widgets # QWidget, QDialog, QPushButton, QDialogButtonBox, QMessageBox, QLayouts, QLabel, QApplication 等
)

