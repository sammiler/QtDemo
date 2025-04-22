//
// Created by sammiler on 2025/4/21.
//
#include <QList>
#include <QMap>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QStack>
#include <QTime>
#include <QApplication>
#include <QDebug>
#include <qtconcurrentmap.h>

using namespace QtConcurrent;

// 递归搜索文件
QStringList findFiles(const QString &startDir, const QStringList &filters)
{
    QStringList names;
    QStack<QString> stack;
    stack.push(startDir);

    while (!stack.isEmpty()) {
        const QString currentDirPath = stack.pop();
        const QDir dir(currentDirPath);
        if (!dir.exists()) {
            continue;
        }

        for (const QString &file : dir.entryList(filters, QDir::Files)) {
            names += currentDirPath + '/' + file;
        }

        for (const QString &subdir : dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
            stack.push(currentDirPath + '/' + subdir);
        }
    }
    return names;
}

using WordCount = QMap<QString, int>;

// 单线程单词计数器函数
WordCount singleThreadedWordCount(const QStringList &files)
{
    WordCount wordCount;
    for (const QString &file : files) {
        QFile f(file);
        f.open(QIODevice::ReadOnly);
        QTextStream textStream(&f);
        while (!textStream.atEnd()) {
            for (const QString &word : textStream.readLine().split(' ')) {
                wordCount[word] += 1;
            }
        }
    }
    return wordCount;
}

// countWords 计算单个文件的单词数，该函数由多个线程并行调用，线程安全
WordCount countWords(const QString &file)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    QTextStream textStream(&f);
    WordCount wordCount;

    while (!textStream.atEnd()) {
        for (const QString &word : textStream.readLine().split(' ')) {
            wordCount[word] += 1;
        }
    }
    return wordCount;
}

// reduce 将 map 的结果添加到最终结果，单线程调用
void reduce(WordCount &result, const WordCount &w)
{
    QMapIterator<QString, int> i(w);
    while (i.hasNext()) {
        i.next();
        result[i.key()] += i.value();
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "finding files...";
    const QStringList files = findFiles("C:/Users/sammiler/MyFile/QtDemo/Source", QStringList() << "*.cpp" << "*.h");
    qDebug() << files.count() << "files";

    qint64 singleThreadTime = 0;
    {
        QElapsedTimer time;
        time.start();
        singleThreadedWordCount(files);
        singleThreadTime = time.elapsed();
        qDebug() << "single thread" << singleThreadTime;
    }

    qint64 mapReduceTime = 0;
    {
        QElapsedTimer time;
        time.start();
        mappedReduced(files, countWords, reduce);
        mapReduceTime = time.elapsed();
        qDebug() << "MapReduce" << mapReduceTime;
    }

    qDebug() << "MapReduce speedup x" << (static_cast<double>(singleThreadTime) - static_cast<double>(mapReduceTime)) / static_cast<double>(mapReduceTime) + 1;
    return QApplication::exec();
}