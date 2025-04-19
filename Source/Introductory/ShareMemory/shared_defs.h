#ifndef SHARED_DEFS_H
#define SHARED_DEFS_H

#include <QString>

// 共享内存段的唯一键
// 两个进程必须使用相同的键来访问同一个共享内存段
const QString SHARED_MEMORY_KEY = "QtSharedMemoryImageExampleKey";

#endif // SHARED_DEFS_H