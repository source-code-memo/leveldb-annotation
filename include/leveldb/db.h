
#ifndef STORAGE_LEVELDB_INCLUDE_DB_H_
#define STORAGE_LEVELDB_INCLUDE_DB_H_

#include <stdint.h>
#include <stdio.h>

#include "slice.h"
#include "status.h"

namespace leveldb {
// leveldb version 1.20
static const int kMajorVersion = 1;
static const int kMinorVersion = 20;

// 前置声明的类
struct Options;
struct ReadOptions;
struct WriteOptions;
struct WriteBatch;

// DB某个特定状态的抽象操作
// Snapshot 是一个不可改变的对象,因此可以很安全的在多线程之间操作而不需要外部的同步
class Snapshot {
protected:
    virtual ~Snapshot();
};

// Range 是描述的key的范围
struct Range {
    Slice start;
    Slice limit;

    Range() { }
    Range(const Slice& s, const Slice& l) : start(s), limit(l) { }
};

// DB 是一个持久化的有序的k-v的map
// DB 是多线程安全的
class DB {
public:
    // 打开name为名的datebase
    // 把heap-allocated上分配的指针存到 *dptr中,并在成功的时候返回OK
    // 如果失败则*dptr=NULL,并返回相应的错误
    // 调用者必须在*dptr不再使用的时候delete掉
    static Status Open(const Options& options,
                       const std::string& name,
                       DB** dbprt);
    DB() { }
    virtual ~DB();

private:
};

}

#endif // STORAGE_LEVELDB_INCLUDE_DB_H_

