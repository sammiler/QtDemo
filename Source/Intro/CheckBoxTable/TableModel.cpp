#include "TableModel.h"
#include <QDebug>       // 需要 qDebug
#include <QStringList>  // 需要 QStringList

// 构造函数
TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    qDebug() << "TableModel created.";
}

// 析构函数
TableModel::~TableModel()
{
    qDebug() << "TableModel destroyed.";
}

// 更新表格数据，并通知视图进行完全刷新
void TableModel::updateData(QList<FileRecord> recordList)
{
    // 通知视图数据即将完全重置
    beginResetModel();
    // 更新内部数据列表
    m_recordList = recordList;
    // 通知视图数据重置完毕，可以重新获取数据并刷新显示
    endResetModel();

    qDebug() << "TableModel updated with" << m_recordList.count() << "records.";

    // 数据更新后，更新表头状态
    updateHeaderState();
}

// 返回模型中的行数
int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_recordList.count();
}

// 返回模型中的列数
int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2; // 复选框列 + 文件路径列
}

// 为指定的索引和角色提供数据
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_recordList.count() || index.column() >= 2)
        return QVariant();

    // 获取指定行的数据记录
    const FileRecord &record = m_recordList.at(index.row()); // 使用 const 引用

    // 根据请求的角色返回对应的数据
    switch (role)
    {
    case Qt::TextColorRole: // 文本颜色角色
        return QColor(Qt::white); // 示例，配合深色背景 QSS
    case Qt::TextAlignmentRole: // 文本对齐角色
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter); // 左对齐并垂直居中
    case Qt::DisplayRole: // 显示角色 (用于显示文本)
    {
        if (index.column() == File_PATH_COLUMN)
            return record.strFilePath;
        return QVariant(); // 复选框列的 DisplayRole 通常不显示文本
    }
    case Qt::UserRole: // 用户角色 (用于存储和获取复选框的布尔状态)
    {
        if (index.column() == CHECK_BOX_COLUMN)
            // 返回复选框的布尔状态作为用户数据
            return record.bChecked;
    }
    // 注意：不在这里处理 Qt::CheckStateRole，因为委托会自己绘制和管理状态，通过 Qt::UserRole 与模型交互
    default:
        return QVariant(); // 其他未处理的角色返回无效 QVariant
    }
}

// 设置指定索引和角色的数据
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (index.row() >= m_recordList.count() || index.column() >= 2)
        return false;

    // 获取指定行的数据记录 (非 const 引用，因为要修改)
    FileRecord &record = m_recordList[index.row()];

    bool dataWasChanged = false; // 标志数据是否真的改变了
    int changedRole = role; // 记录实际改变的角色

    switch (role)
    {
    case Qt::DisplayRole: // 通常不用于设置数据，除非 ItemIsEditable 标志被设置
    {
        if (index.column() == File_PATH_COLUMN)
        {
            if (record.strFilePath != value.toString()) {
                 record.strFilePath = value.toString();
                 dataWasChanged = true;
                 qDebug() << "TableModel: File path changed at row" << index.row() << "to" << record.strFilePath;
            }
        }
        break;
    }
    case Qt::UserRole: // 用户角色 (用于通过委托更新复选框的布尔状态)
    {
        if (index.column() == CHECK_BOX_COLUMN)
        {
            // 委托传递过来的是布尔值 (或者可以 toInt 判断 Qt::Checked/Unchecked，取决于委托如何调用 setData)
            // 根据 CheckBoxDelegate 的代码 (model->setData(index, !data, Qt::UserRole);)
            // 委托在这里传递的是直接的布尔值 !data
            bool newCheckedState = value.toBool();
            if (record.bChecked != newCheckedState) {
                 record.bChecked = newCheckedState; // 更新复选框状态
                 dataWasChanged = true;
                 changedRole = Qt::UserRole; // 记录实际改变的是 UserRole
                 qDebug() << "TableModel: Check state changed at row" << index.row() << "to" << record.bChecked;
            }
        }
        break;
    }
    // 注意：不处理 Qt::CheckStateRole，因为委托通过 Qt::UserRole 来更新模型数据
    default:
        return false;
    }

    if (dataWasChanged) {
        // 发射 dataChanged 信号，通知视图指定索引的数据已改变
        // dataChanged 信号的 roles 参数需要一个 QVector<int>
        QVector<int> changedRoles;
        changedRoles << changedRole; // 将实际改变的角色添加到 QVector 中

        emit dataChanged(index, index, changedRoles); // 发射信号，传递 QVector

        // !!! 数据改变后，更新表头状态 !!!
        updateHeaderState();

        return true;
    }

    return false;
}

// 提供表头数据
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section < 0 || (orientation == Qt::Horizontal && section >= 2) || (orientation == Qt::Vertical && section >= m_recordList.count()))
         return QVariant();

    switch (role)
    {
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::DisplayRole:
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == CHECK_BOX_COLUMN)
                return QStringLiteral("状态");

            if (section == File_PATH_COLUMN)
                return QStringLiteral("文件路径");
        }
        return QVariant();
    }
    // 注意：不在这里处理 Qt::CheckStateRole 或 Qt::UserRole，表头状态由 HeaderView 自己的变量管理
    default:
        return QVariant();
    }
}

// 返回指定索引的单元项标志
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    // 设置基础标志：可用和可选中
    Qt::ItemFlags baseFlags = QAbstractItemModel::flags(index);
    Qt::ItemFlags flags = baseFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    // !!! 注意：不在这里为复选框列添加 ItemIsUserCheckable 标志 !!!
    // 因为复选框的交互和绘制完全由委托负责

    // 如果文件路径列需要可编辑，可以在这里添加 Qt::ItemIsEditable
    // if (index.column() == File_PATH_COLUMN)
    //     flags |= Qt::ItemIsEditable;

    return flags;
}

// 获取选中状态的文件路径列表 (可选实现)
QStringList TableModel::getCheckedFilePaths() const
{
    QStringList checkedList;
    for (const FileRecord &record : m_recordList) {
        if (record.bChecked) {
            checkedList.append(record.strFilePath);
        }
    }
    return checkedList;
}

// 接收来自表头的信号，更新所有行项的复选状态
// state 使用 Qt::CheckState 枚举值 (会被转换为 int)
void TableModel::onStateChanged(int state)
{
    qDebug() << "TableModel::onStateChanged received state:" << state;

    // 根据表头传来的状态，确定行项的新状态
    bool newRowCheckedState = (state == Qt::Checked); // 如果表头是完全选中，则所有行项设为选中

    QModelIndex index;
    int rowCount = m_recordList.count();
    if (rowCount == 0) return; // 没有数据则无需更新

    // 批量更新模型数据 (性能优化)
    // beginResetModel() 和 endResetModel() 会导致整个视图刷新，适用于大规模数据变化
    // beginInsertRows/endInsertRows, beginRemoveRows/endRemoveRows, beginMoveRows/endMoveRows 适用于增删移动
    // dataChanged 适用于局部数据变化
    // 这里可以遍历修改数据，然后发射 dataChanged 信号通知视图刷新
    // 或者如果变化范围大，可以考虑 begin/endResetModel

    // 遍历所有行，更新复选状态
    bool dataChangedInLoop = false;
    for (int i = 0; i < rowCount; ++i)
    {
        // 只在状态需要改变时进行修改
        if (m_recordList[i].bChecked != newRowCheckedState) {
            m_recordList[i].bChecked = newRowCheckedState; // 更新模型数据
            dataChangedInLoop = true;
            // 可以发射 dataChanged 信号通知视图刷新单个或部分项
            // emit dataChanged(this->index(i, CHECK_BOX_COLUMN), this->index(i, CHECK_BOX_COLUMN), QVector<int>() << Qt::UserRole);
        }
    }

    // 如果有数据改变，通知视图刷新
    if (dataChangedInLoop) {
        // 发射信号通知视图整个第一列的数据可能都改变了
        emit dataChanged(this->index(0, CHECK_BOX_COLUMN), this->index(rowCount - 1, CHECK_BOX_COLUMN), QVector<int>() << Qt::UserRole);
        qDebug() << "TableModel: All rows updated to checked =" << newRowCheckedState;
    }
    // 注意：这里更新行项状态不会反过来调用 updateHeaderState()，避免死循环

}

// 内部方法，计算当前所有行项的总复选状态 (Checked, Unchecked, PartiallyChecked)
// 并在需要时发射 stateChanged 信号通知表头
void TableModel::updateHeaderState()
{
    int rowCount = m_recordList.count();
    if (rowCount == 0) {
        // 如果没有数据，表头应该显示未选中状态
        emit stateChanged(Qt::Unchecked);
        qDebug() << "TableModel: Updating header state to Unchecked (no data).";
        return;
    }

    int checkedCount = 0;
    for (const FileRecord &record : m_recordList) {
        if (record.bChecked) {
            checkedCount++;
        }
    }

    Qt::CheckState currentState;
    if (checkedCount == 0) {
        currentState = Qt::Unchecked;
    } else if (checkedCount == rowCount) {
        currentState = Qt::Checked;
    } else {
        currentState = Qt::PartiallyChecked;
    }

    // 发射信号通知表头更新状态
    emit stateChanged(currentState);
    qDebug() << "TableModel: Updating header state to" << currentState;
}