add_executable(CustomButtonTableView
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
        TableModel.cpp
        TableModel.h
        TableViewDelegate.cpp
        TableViewDelegate.h
        Images/resources.qrc

)

target_link_libraries(CustomButtonTableView
        PRIVATE
        Qt5::Core    # QObject, QList, QString, QVariant, QAbstractItemModel, QAbstractTableModel, QModelIndex, QEvent 等
        Qt5::Gui     # QColor, Qt::, QIcon, QPixmap, QPainter, QStyleOptionViewItem, QMouseEvent, QStyle, QStyleOptionButton 等
        Qt5::Widgets # QWidget, QApplication, QTableView, QHeaderView, QAbstractItemView, QFrame, QLayouts, QCheckBox 等
)