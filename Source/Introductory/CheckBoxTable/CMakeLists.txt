

# 处理 Qt 资源文件 (.qrc)
qt5_add_resources(SOURCES_RCC resources.qrc)

# 定义可执行文件
# WIN32 标志在 Windows 上创建 GUI 子系统应用
# 列出所有需要编译的源文件 (.cpp) 和包含 Q_OBJECT 宏的头文件 (.h)
# 包含资源文件编译生成的源文件 (${SOURCES_RCC})
add_executable(MasterCheckboxTableExample
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h          # 包含 Q_OBJECT，需要 moc 处理
        TableModel.cpp
        TableModel.h          # 包含 Q_OBJECT，需要 moc 处理
        CheckBoxDelegate.cpp
        CheckBoxDelegate.h    # 包含 Q_OBJECT，需要 moc 处理
        TableHeaderView.cpp
        TableHeaderView.h     # 包含 Q_OBJECT，需要 moc 处理
        ${SOURCES_RCC}        # 包含资源文件编译结果
)

# 链接所需的 Qt 模块库
target_link_libraries(MasterCheckboxTableExample
        PRIVATE
        Qt5::Core    # QObject, QList, QString, QVariant, QAbstractItemModel, QAbstractTableModel, QModelIndex, QEvent 等
        Qt5::Gui     # QColor, Qt::, QIcon, QPixmap, QPainter, QStyleOptionViewItem, QMouseEvent, QStyle, QStyleOptionButton, QHeaderView 等
        Qt5::Widgets # QWidget, QApplication, QTableView, QHeaderView, QAbstractItemView, QFrame, QLayouts, QCheckBox 等
)
