#include <QApplication>
#include <QVBoxLayout>
#include <QDateTimeEdit>
#include <QDebug>
#include <QLabel>
#include <QTimer>

class DateTimeWidget : public QWidget
{
    Q_OBJECT

public:
    DateTimeWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        auto *layout = new QVBoxLayout(this);

        // 日期时间编辑器
        QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
        dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
        dateTimeEdit->setCalendarPopup(true);

        // 日期编辑器
        QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate(), this);
        dateEdit->setDisplayFormat("yyyy/MM/dd");
        dateEdit->setCalendarPopup(true);
        dateEdit->setMinimumDate(QDate::currentDate().addDays(-365));
        dateEdit->setMaximumDate(QDate::currentDate().addDays(365));

        // 时间编辑器
        QDateTimeEdit *timeEdit = new QDateTimeEdit(QTime::currentTime(), this);
        timeEdit->setDisplayFormat("HH:mm:ss");

        // 展示当前字段信息
        QLabel *label = new QLabel(this);

        layout->addWidget(new QLabel("DateTime:", this));
        layout->addWidget(dateTimeEdit);
        layout->addWidget(new QLabel("Date:", this));
        layout->addWidget(dateEdit);
        layout->addWidget(new QLabel("Time:", this));
        layout->addWidget(timeEdit);
        layout->addWidget(new QLabel("Selected Section Info:", this));
        layout->addWidget(label);

        // 信号槽连接
        connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](const QDateTime &dt) {
            qDebug() << "[DateTime Changed]:" << dt;
        });

        connect(dateEdit, &QDateTimeEdit::dateChanged, this, [=](const QDate &d) {
            qDebug() << "[Date Changed]:" << d;
        });

        connect(timeEdit, &QDateTimeEdit::timeChanged, this, [=](const QTime &t) {
            qDebug() << "[Time Changed]:" << t;
        });

        // 获取具体字段值
        QTimer::singleShot(1000, this, [=]() {
            dateTimeEdit->setSelectedSection(QDateTimeEdit::DaySection);  // 设置选中部分
            int count = dateTimeEdit->sectionCount();
            auto section = dateTimeEdit->currentSection();
            int index = dateTimeEdit->currentSectionIndex();

            QString year = dateTimeEdit->sectionText(QDateTimeEdit::YearSection);
            QString month = dateTimeEdit->sectionText(QDateTimeEdit::MonthSection);
            QString day = dateTimeEdit->sectionText(QDateTimeEdit::DaySection);
            QString hour = dateTimeEdit->sectionText(QDateTimeEdit::HourSection);
            QString minute = dateTimeEdit->sectionText(QDateTimeEdit::MinuteSection);
            QString second = dateTimeEdit->sectionText(QDateTimeEdit::SecondSection);

            QString info = QString("SectionCount: %1\nCurrentSectionIndex: %2\n"
                                   "Year: %3\nMonth: %4\nDay: %5\nHour: %6\nMinute: %7\nSecond: %8")
                               .arg(count)
                               .arg(index)
                               .arg(year)
                               .arg(month)
                               .arg(day)
                               .arg(hour)
                               .arg(minute)
                               .arg(second);

            label->setText(info);
        });

        setLayout(layout);
        setWindowTitle("QDateTimeEdit 全功能演示");
        resize(400, 300);
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DateTimeWidget widget;
    widget.show();
    return app.exec();
}
