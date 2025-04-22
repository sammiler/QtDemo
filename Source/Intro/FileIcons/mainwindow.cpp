#include "mainwindow.h"
#include <QStringList> // 需要 QStringList
#include <QSize>       // 需要 QSize
#include <QColor>      // 可选，用于背景色等
#include <QPalette>    // 可选，用于背景色等

// 构造函数
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建 QListWidget 控件，以当前窗口为父对象
    m_listWidget = new QListWidget(this);

    // 设置 QListWidget 的属性，使其以图标模式显示
    m_listWidget->setIconSize(QSize(48, 48));         // 设置单元项中的图标大小
    m_listWidget->setResizeMode(QListView::Adjust);   // 设置大小模式为可调节
    m_listWidget->setViewMode(QListView::IconMode);   // 设置显示模式为图标模式
    m_listWidget->setMovement(QListView::Static);     // 设置单元项不可被拖动移动
    m_listWidget->setSpacing(10);                     // 设置单元项之间的间距

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this); // 垂直布局
    layout->addWidget(m_listWidget);              // 将 QListWidget 添加到布局
    setLayout(layout);                            // 将布局设置到窗口上

    // --- 定义需要查询的扩展名列表 ---
    QStringList extensions;
    // 使用 QStringLiteral 更好，或者直接使用英文扩展名避免转码问题
    extensions << QStringLiteral("exe") << QStringLiteral("zip")
               << QStringLiteral("har") << QStringLiteral("hwl") // 示例中有的扩展名
               << QStringLiteral("accdb") << QStringLiteral("xlsx")
               << QStringLiteral("pptx") << QStringLiteral("docx")
               << QStringLiteral("jnt") << QStringLiteral("txt")
               << QStringLiteral("pdf") << QStringLiteral("png") // 添加一些常见的
               << QStringLiteral("mp3") << QStringLiteral("mp4")
               << QStringLiteral("cpp") << QStringLiteral("h");


    // --- 遍历扩展名列表，获取图标和类型，并添加到 QListWidget ---
    for (const QString &extension : extensions) // 使用范围-based for 循环
    {
        // 获取图标和类型
        QIcon icon = getFileIcon(extension);
        QString type = getFileType(extension);

        // 如果获取类型失败，使用扩展名代替
        if (type.isEmpty()) {
            type = "." + extension;
        }

        // 创建 QListWidgetItem 单元项
        QListWidgetItem *item = new QListWidgetItem(m_listWidget); // 以 QListWidget 为父对象创建
        item->setIcon(icon); // 设置图标
        item->setText(type); // 设置文本 (文件类型描述)

        // 将单元项添加到 QListWidget 中
        // m_listWidget->addItem(item); // 在构造时指定父对象即可自动添加
    }

    qDebug() << "MainWindow created and populated with file icons.";
}

// 析构函数
MainWindow::~MainWindow()
{
    // m_listWidget 的父对象是 this，会自动销毁
}

// --- Helper 方法实现 ---

// 根据扩展名获取对应的文件图标
QIcon MainWindow::getFileIcon(const QString &extension) const
{
    QFileIconProvider provider; // 文件图标提供者对象
    QIcon icon;

    // --- 使用 QTemporaryFile 创建一个临时文件，以便 QFileIconProvider 查询 ---
    // 使用文件名模板，确保有唯一名称和正确的扩展名
    // QTemporaryFile 的文件名模板格式通常是 path/to/temp/prefix_XXXXXX.suffix
    // XXXXXX 会被替换为唯一的字符串
    QString templateName = QDir::tempPath() + QDir::separator() +
                           QCoreApplication::applicationName() + "_XXXXXX." + extension;

    QTemporaryFile tmpFile(templateName);
    // 设置 AutoRemove 为 true，这样当 QTemporaryFile 对象被销毁时，临时文件会自动删除
    tmpFile.setAutoRemove(true);

    // 尝试打开临时文件，这会在磁盘上创建它
    if (tmpFile.open())
    {
        // 文件创建成功，立即关闭它。必须关闭文件，QFileInfo 才能正确访问它。
        tmpFile.close();

        // !!! 关键修正 !!!
        // 使用 tmpFile.fileName() 获取临时文件实际创建时的完整路径和名称
        // 而不是使用文件名模板 strTemplateName (原始代码中的 strFileName 可能是笔误)
        QFileInfo fileInfo(tmpFile.fileName());

        // 使用 QFileIconProvider 获取该文件的图标
        icon = provider.icon(fileInfo);

        // tmpFile 对象在函数结束时会自动销毁，自动删除文件 (因为 autoRemove 是 true)
         qDebug() << "Got icon for extension ." << extension << " using temporary file:" << tmpFile.fileName();

    }
    else
    {
        // 临时文件创建失败
        qCritical() << QString("failed to create temporary file with extension .%1: %2").arg(extension).arg(tmpFile.errorString());
        // icon 会是默认的无效图标
    }

    return icon; // 返回获取到的图标 (成功时是系统图标，失败时可能是默认图标)
}

// 根据扩展名获取对应的文件类型描述
QString MainWindow::getFileType(const QString &extension) const
{
    QFileIconProvider provider; // 文件图标提供者对象
    QString type;

    // --- 使用 QTemporaryFile 创建一个临时文件，以便 QFileIconProvider 查询 ---
    QString templateName = QDir::tempPath() + QDir::separator() +
                           QCoreApplication::applicationName() + "_XXXXXX." + extension;

    QTemporaryFile tmpFile(templateName);
    // 设置 AutoRemove 为 true，当 QTemporaryFile 对象被销毁时，临时文件会自动删除
    tmpFile.setAutoRemove(true);

    // 尝试打开临时文件
    if (tmpFile.open())
    {
        // 文件创建成功，立即关闭它
        tmpFile.close();

        // 使用 tmpFile.fileName() 获取临时文件实际路径
        QFileInfo fileInfo(tmpFile.fileName());

        // 使用 QFileIconProvider 获取该文件的类型描述字符串
        type = provider.type(fileInfo);

        // tmpFile 对象在函数结束时会自动销毁，自动删除文件 (因为 autoRemove 是 true)
         qDebug() << "Got type for extension ." << extension << " using temporary file:" << tmpFile.fileName() << " -> Type:" << type;
    }
    else
    {
        // 临时文件创建失败
        qCritical() << QString("failed to create temporary file with extension .%1: %2").arg(extension).arg(tmpFile.errorString());
        // type 会是空的
    }

    return type; // 返回获取到的文件类型描述字符串
}