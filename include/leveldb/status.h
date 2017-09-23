// Status 涵盖了一个操作的结果.有可能是成功
// 或者是带有错误信息的错误结果
// Status 在调用const方法的时候是多线程安全的
// 但如果有其中一个线程调用了非const方法
// 则访问同样Status对象的进程需要同步

#ifndef STORAGE_LEVELDB_INCLUDE_STATUS_H_
#define STORAGE_LEVELDB_INCLUDE_STATUS_H_

#include <cstdio>

namespace leveldb {
class Status {
public:
    Status() : state_(NULL) { }
    ~Status() { delete[] state_; }

private:
    char *state_;

    enum Code {
        kOk = 0,
        kNotFound = 1,
        kCorruption = 2,
        kNotSupported = 3,
        kInvalidArgument = 4,
        kIOError = 5,
    };
};

} // namespace leveldb
#endif /* ifndef STORAGE_LEVELDB_INCLUDE_STATUS_H_ */
