#include "mywindow.h"
#include <QDebug>

MyWindow::MyWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("自定义事件示例");
    setGeometry(500, 500, 400, 200);

    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    label = new QLabel("等待自定义事件...");
    layout->addWidget(label);

    button = new QPushButton("发送自定义事件");
    connect(button, &QPushButton::clicked, this, &MyWindow::sendCustomEvent);
    layout->addWidget(button);

    eventFilter = new MyEventFilter(this); // 将事件过滤器设置为窗口的子对象，方便管理生命周期
    installEventFilter(eventFilter); // 在窗口上安装事件过滤器

    connect(eventFilter, &MyEventFilter::customEventReceived, this, &MyWindow::handleCustomEventData);
}


MyWindow::~MyWindow()
= default;

void MyWindow::sendCustomEvent()
{
    QVariant eventData;
    QString a = "aadsasad";
    eventData.setValue(QString("Hello from custom event!"));
    MyCustomEvent *customEvent = new MyCustomEvent(eventData);
    QCoreApplication::postEvent(this, customEvent); // 将自定义事件投递到窗口的事件队列
}

void MyWindow::handleCustomEventData(const QVariant& data)
{
    label->setText(QString("事件过滤器接收到数据: %1").arg(data.toString()));
}

bool MyWindow::event(QEvent *event)
{
    qDebug() << event->type();

    if (event->type() == MyCustomEvent::Type) {
        MyCustomEvent *customEvent = static_cast<MyCustomEvent*>(event);
        QVariant data = customEvent->getData();
        qDebug() << "窗口自身处理自定义事件，数据:" << data;
        // 在这里可以对自定义事件进行进一步的处理
        return true; // 返回 true 表示该事件已被处理，不再传递给其他处理器
    }
    return QMainWindow::event(event); // 调用父类的 event 方法，处理其他事件
}