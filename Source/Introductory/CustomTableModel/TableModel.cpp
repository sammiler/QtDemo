#include "TableModel.h"
#include <QDebug> // 需要 qDebug

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
}

// 返回模型中的行数
int TableModel::rowCount(const QModelIndex &parent) const
{
    // 对于表格模型，非法的父模型索引 (默认值) 表示顶层，行数就是数据列表的大小
    if (parent.isValid())
        return 0; // 如果父模型索引有效，表示是树状结构的子节点，这里不支持，所以返回 0

    return m_recordList.count();
}

// 返回模型中的列数
int TableModel::columnCount(const QModelIndex &parent) const
{
    // 对于表格模型，非法的父模型索引 (默认值) 表示顶层，列数固定为 2
    if (parent.isValid())
        return 0; // 如果父模型索引有效，表示是树状结构的子节点，这里不支持，所以返回 0

    return 2; // 复选框列 + 文件路径列
}

// 为指定的索引和角色提供数据
QVariant TableModel::data(const QModelIndex &index, const int role) const
{
    // 检查索引是否有效 (行和列是否在范围内)
    if (!index.isValid())
        return QVariant(); // 无效索引返回无效 QVariant

    // 检查行号是否超出数据范围
    if (index.row() >= m_recordList.count() || index.column() >= 2)
        return QVariant();

    // 获取指定行的数据记录
    const FileRecord &record = m_recordList.at(index.row()); // 使用 const 引用更高效和安全

    // 根据请求的角色返回对应的数据
    switch (role)
    {
    case Qt::TextColorRole: // 文本颜色角色
        return QColor(Qt::white); // 设置文本颜色为白色 (示例，配合深色背景 QSS)
    case Qt::TextAlignmentRole: // 文本对齐角色
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter); // 左对齐并垂直居中
    case Qt::DisplayRole: // 显示角色 (用于显示文本)
    {
        if (index.column() == File_PATH_COLUMN) // 如果是文件路径列
            return record.strFilePath; // 返回文件路径字符串
        // 如果是复选框列的 DisplayRole，不显示文本，只显示复选框，所以返回空字符串或 QVariant()
        return QVariant();
    }
    case Qt::CheckStateRole: // 复选框状态角色
    {
        if (index.column() == CHECK_BOX_COLUMN) // 如果是复选框列
            // 根据 bChecked 的布尔值返回对应的 Qt::CheckState 枚举值
            return record.bChecked ? Qt::Checked : Qt::Unchecked;
    }
    // 可以添加其他角色，如 Qt::DecorationRole (图标), Qt::ToolTipRole (工具提示) 等
    default:
        return QVariant(); // 其他未处理的角色返回无效 QVariant
    }
}

// 设置指定索引和角色的数据
bool TableModel::setData(const QModelIndex &index, const QVariant &value, const int role)
{
    // 检查索引是否有效
    if (!index.isValid())
        return false; // 无效索引返回 false

    // 检查行号是否超出数据范围
    if (index.row() >= m_recordList.count() || index.column() >= 2)
        return false;

    // 获取指定行的数据记录 (非 const 引用，因为要修改)
    FileRecord &record = m_recordList[index.row()]; // 使用 [] 非 const 访问更高效

    bool dataWasChanged = false; // 标志数据是否真的改变了

    // 根据请求的角色设置数据
    switch (role)
    {
    case Qt::DisplayRole: // 显示角色 (如果该列允许编辑文本，会收到此角色)
    {
        if (index.column() == File_PATH_COLUMN) // 如果是文件路径列
        {
            // 检查新值是否与当前值不同
            if (record.strFilePath != value.toString()) {
                 record.strFilePath = value.toString(); // 更新文件路径
                 dataWasChanged = true;
                 qDebug() << "TableModel: File path changed at row" << index.row() << "to" << record.strFilePath;
            }
        }
        break; // 跳出 switch
    }
    case Qt::CheckStateRole: // 复选框状态角色
    {
        if (index.column() == CHECK_BOX_COLUMN) // 如果是复选框列
        {
            // 将 QVariant 的值转换为整数，并判断是否等于 Qt::Checked
            const bool newCheckedState = (value.toInt() == Qt::Checked);
            // 检查新状态是否与当前状态不同
            if (record.bChecked != newCheckedState) {
                 record.bChecked = newCheckedState; // 更新复选框状态
                 dataWasChanged = true;
                 qDebug() << "TableModel: Check state changed at row" << index.row() << "to" << record.bChecked;
            }
        }
        break; // 跳出 switch
    }
    // 可以处理 Qt::EditRole 等其他角色
    default:
        return false; // 其他未处理的角色返回 false
    }

    // 如果数据确实发生了改变
    if (dataWasChanged) {
        // 发射 dataChanged 信号，通知视图指定索引的数据已改变，视图会根据需要重新获取数据并刷新
        emit dataChanged(index, index, QVector<int>() << role); // 也可以只传递改变的角色列表
        return true; // 数据设置成功
    }

    return false; // 数据未改变或设置失败
}

// 提供表头数据
QVariant TableModel::headerData(const int section, const Qt::Orientation orientation, const int role) const
{
    // 检查区域 (列/行索引) 是否有效
    if (section < 0 || (orientation == Qt::Horizontal && section >= 2) || (orientation == Qt::Vertical && section >= m_recordList.count()))
         return QVariant(); // 无效区域返回无效 QVariant

    // 根据请求的角色返回表头数据
    switch (role)
    {
    case Qt::TextAlignmentRole: // 文本对齐角色
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter); // 左对齐并垂直居中
    case Qt::DisplayRole: // 显示角色 (用于显示表头文本)
    {
        if (orientation == Qt::Horizontal) // 如果是水平表头
        {
            if (section == CHECK_BOX_COLUMN) // 如果是复选框列的表头
                return QStringLiteral("状态"); // 显示“状态”
            if (section == File_PATH_COLUMN) // 如果是文件路径列的表头
                return QStringLiteral("文件路径"); // 显示“文件路径”
        }
        // 如果是垂直表头，通常显示行号，QAbstractTableModel 默认处理，这里可以不写
        // 或者如果需要自定义行号文本，可以在这里实现
        return QVariant(); // 其他情况返回无效 QVariant
    }
    // 可以添加 Qt::DecorationRole (图标), Qt::ToolTipRole (工具提示) 等角色
    default:
        return QVariant(); // 其他未处理的角色返回无效 QVariant
    }
}

// 返回指定索引的单元项标志
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    // 如果索引无效，返回默认标志
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    // 获取基类的默认标志 (通常包含 ItemIsEnabled | ItemIsSelectable)
    const Qt::ItemFlags baseFlags = QAbstractItemModel::flags(index);

    // 如果是复选框列
    if (index.column() == CHECK_BOX_COLUMN)
        // 在默认标志的基础上，添加 ItemIsUserCheckable 标志
        // 这个标志告诉视图该单元项可以由用户交互式地切换复选框状态
        return baseFlags | Qt::ItemIsUserCheckable;

    // 如果是文件路径列，通常不添加 ItemIsUserCheckable 或 ItemIsEditable
    // 如果想让文件路径可编辑，需要在这里加上 ItemIsEditable
    // if (index.column() == File_PATH_COLUMN)
    //     return baseFlags | Qt::ItemIsEditable;

    // 其他列或复选框列以外的，返回基类的默认标志
    return baseFlags;
}