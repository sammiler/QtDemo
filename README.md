# QtDemo

一个面向初学者的 Qt 示例项目集合，涵盖了 Qt 框架的多种核心功能和常用模块。本项目使用 CMake 进行构建。

## 项目概述

本项目旨在通过一系列简单独立的示例，帮助初学者快速了解和掌握 Qt 开发。示例按照功能领域被组织在不同的子目录中，方便学习和查阅。

项目主要分为以下几个类别：

*   **Intro**: Qt 基础概念、常用控件、布局、事件处理、绘图基础、IPC 基础、表格视图基础等。
*   **Int**: 中级主题，如网络、多线程、并发、应用设置等。
*   **Advance**: 高级主题，如图形视图框架 (Graphics View Framework) 的深入应用等。

## 构建项目

本项目使用 CMake 进行构建。请确保你已经安装了 Qt 5 或更高版本，以及相应的 C++ 编译器和 CMake。

1.  **获取代码**:
    ```bash
    git clone <你的仓库地址> # 如果代码托管在 Git 仓库
    # 或者直接下载源代码压缩包并解压
    ```

2.  **创建构建目录**:
    在项目根目录下创建一个 `build` 目录：
    ```bash
    mkdir build
    cd build
    ```

3.  **配置项目**:
    运行 CMake 来配置项目。CMake 会检测你的系统和 Qt 安装。
    ```bash
    cmake ..
    ```
    *   如果 CMake 找不到 Qt，你可能需要设置 `CMAKE_PREFIX_PATH` 环境变量指向你的 Qt 安装目录（例如 `export CMAKE_PREFIX_PATH=/path/to/your/Qt/5.x.y/gcc_64`）或在运行 cmake 时指定 (`cmake -DCMAKE_PREFIX_PATH=/path/to/your/Qt/5.x.y/gcc_64 ..`)。
    *   你可以指定不同的生成器，例如在 Windows 上使用 Visual Studio: `cmake .. -G "Visual Studio 16 2019"`

4.  **构建项目**:
    运行构建命令。
    ```bash
    cmake --build .
    ```

5.  **运行示例**:
    构建成功后，可执行文件通常会在 `build` 目录下的 `Debug` 或 `Release` 子目录中（取决于你的构建配置）。运行 `QtDemo` 可执行文件即可打开主界面，通过界面选择并运行不同的示例。

## 示例说明

本项目中的示例按功能进行分组，并通过主程序统一启动。以下是各类别包含的示例简要说明：

### Intro (入门)

本部分涵盖 Qt 基础知识、常用控件、布局、绘图等入门级示例。

*   **Property**: 演示 Qt 的属性系统。
*   **Event**: 解释 Qt 的事件处理机制。
*   **Timer**: 学习如何使用 `QTimer` 实现定时操作。
*   **ObjectsTree**: 展示 `QObject` 的父子对象树关系。
*   **FindChild**: 演示如何查找子对象。
*   **Dialog**: 各种类型的对话框示例。
*   **Label**: `QLabel` 部件的使用。
*   **LCD**: `QLCDNumber` 部件的使用。
*   **PushButton**: `QPushButton` 部件的使用。
*   **ToolButton**: `QToolButton` 部件的使用。
*   **CheckBox**: `QCheckBox` 部件的使用。
*   **RadioButton**: `QRadioButton` 部件的使用。
*   **LineEdit**: `QLineEdit` 部件的使用。
*   **SpinBox**: `QSpinBox` 和 `QDoubleSpinBox` 部件的使用。
*   **Slider**: `QSlider` 部件的使用。
*   **ProcessBar**: `QProgressBar` 部件的使用。
*   **DateTimeEdit**: `QDateTimeEdit` 部件的使用。
*   **ScrollArea**: 使用 `QScrollArea` 实现滚动区域。
*   **ToolBox**: `QToolBox` 部件的使用。
*   **SystemTrayIcon**: 在系统托盘中显示图标和菜单。
*   **CardLayout**: (假定) 演示一个自定义的卡片式布局。
*   **FlowLayout**: (假定) 演示一个自定义的流式布局。
*   **BorderLayout**: (假定) 演示一个自定义的边界布局。
*   **GridLayout**: `QGridLayout` 网格布局的使用。
*   **FormLayout**: `QFormLayout` 表单布局的使用。
*   **StackedLayout**: `QStackedLayout` 的使用。
*   **StackedWidget**: `QStackedWidget` 部件的使用。
*   **SpacerItem**: 在布局中使用弹簧 (`QSpacerItem`)。
*   **SizePolicy**: 控制部件的尺寸策略。
*   **FileSystemWatcher**: 监控文件系统变化。
*   **DataSave**: (假定) 演示基本的数据保存方法。
*   **Coordinate**: (假定) 解释 Qt 中的坐标系统概念 (如部件坐标)。
*   **Painter**: 使用 `QPainter` 进行基本 2D 绘图。
*   **GradientPainter**: 演示梯度填充效果。
*   **TextPainter**: 使用 `QPainter` 绘制文本。
*   **PainterPath**: 使用 `QPainterPath` 绘制复杂形状。
*   **PainterCircle**: (假定) 使用 `QPainter` 绘制圆形。
*   **PathWatermelon**: (假定) 使用 `QPainterPath` 绘制西瓜形状。
*   **PathAnt**: (假定) 使用 `QPainterPath` 或动画绘制蚂蚁行进路径。
*   **PathClock**: (假定) 使用 `QPainter` 和 `QPainterPath` 绘制时钟。
*   **PathBanner**: (假定) 使用 `QPainterPath` 绘制旗帜形状。
*   **IPCWindows**: (假定) 演示 Windows 平台下的进程间通信 (IPC)。
*   **ShareMemory**: 演示共享内存实现的进程间通信 (IPC)。
*   **NetSocket**: 演示基于 `QTcpSocket` 和 `QUdpSocket` 的基本网络通信。
*   **FramelessWindow**: 创建无边框窗口。
*   **CustomFramelessWindow**: 定制无边框窗口的行为和外观。
*   **ResizableFramelessWindow**: 实现可调整大小的无边框窗口。
*   **FramelessWidget**: (假定) 演示无边框部件的应用。
*   **SwitchControl**: (假定) 演示一个自定义的开关控件。
*   **TabOrder**: 设置部件的 Tab 键导航顺序。
*   **PasswordLineEdit**: (假定) 定制 `QLineEdit` 实现密码输入框的特性。
*   **BlockESC**: (假定) 阻止按下 ESC 键关闭对话框。
*   **FileIcons**: 获取系统文件图标。
*   **CustomTableModel**: 实现自定义的模型 (`QAbstractTableModel`)。
*   **CustomDelegate**: 实现自定义的委托 (`QAbstractItemDelegate`)。
*   **CheckBoxTable**: 在 `QTableView` 中集成复选框。
*   **HeaderViewSort**: 在表格头部启用排序功能。
*   **CustomHeaderViewSort**: 定制表格头部排序的行为。
*   **HeadViewSortFinal**: (假定) 头部排序功能的最终示例。
*   **WrongModelIndex**: (假定) 演示错误使用模型索引可能导致的问题。
*   **RichTextFormatTableView**: 在 `QTableView` 中显示富文本。
*   **CustomProgressTableView**: 在 `QTableView` 中使用委托显示进度条。
*   **CustomButtonTableView**: 在 `QTableView` 中使用委托显示按钮。

### Int (中级)

本部分包含网络、多线程、并发、应用设置等中级主题。

*   **HostInfo**: 获取网络主机信息。
*   **NetworkInterface**: 获取系统网络接口信息。
*   **Thread**: 使用 `QThread` 进行多线程编程。
*   **Concurrent**: 使用 Qt Concurrent 模块实现并发编程。
*   **Settings**: 使用 `QSettings` 保存和加载应用程序设置。

### Advance (高级)

本部分深入 Graphics View Framework (图形视图框架) 等高级主题。

*   **GraphicsItems**: 演示图形视图框架中的基本图元 (`QGraphicsItem` 子类)。
*   **GraphicsProxyWidget**: 演示如何在图形场景中嵌入标准 Qt 部件 (`QWidget`)。
*   **GraphicsItemSignalSlot**: 演示如何为自定义图元添加信号槽功能 (通常通过继承 `QGraphicsObject`)。

## 贡献

欢迎对本项目的改进建议和代码贡献。请遵循标准的 Fork -> Clone -> Branch -> Commit -> Push -> Pull Request 流程。



