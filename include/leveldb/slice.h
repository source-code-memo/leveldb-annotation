// Slice 是一个简单的结构包含了所指的字符buffer和其大小
// 如果所指向的buffer已经被释放了,则Slice不能再使用
// 
// Slice 的const方法是线程安全的,但如果有任何一个线程调用了非const方法
// 其他的访问同一个Slice的线程需要使用同步方法
 
#ifndef STORAGE_LEVELDB_INCLUDE_SLICE_H_
#define STORAGE_LEVELDB_INCLUDE_SLICE_H_

#include <assert.h>
#include <string>

namespace leveldb {

class Slice
{
public:
    // 创建一个空的Slice
    Slice(): data_(""), size_(0) { }

    // Slice指向d[0:n-1]
    Slice(const char *d, size_t n) : data_(d), size_(n) { }

    // Slice代表string的内容
    Slice(const std::string &s) :data_(s.data()), size_(s.size()) { }

    // Slice指向s[0:strlen(s)-1]
    Slice(const char *s) : data_(s), size_(strlen(s)) { }

    const char* data() const { return data_; }

    size_t size() const { return size_; }

    bool empty() { return size_ == 0; }
    
    char operator[](size_t n) const {
        assert(n < size_);
        return data_[n];
    }

    // 清空slice的内容
    void clear() { data_ = ""; size_ = 0; }

    // 丢弃掉slice的前n个字节
    void remove_prefix(size_t n) {
        assert(n < size_);
        size_ -= n;
        data_ += n;
    }

    // 返回一个包含slice所指内容的string
    std::string ToString() const { return std::string(data_, size_); }

    // 定义slice的比较函数
    // < 0 表示 *this < b
    // = 0 表示 *this = b
    // > 0 表示 *this > b
    int compare(const Slice& b) const;

    // 返回是否是以slice x开始的
    bool start_with(const Slice& x) const {
        return ((x.size_ <= size_) && 
            (memcmp(data_, x.data_, x.size_) == 0));
    }

    virtual ~Slice();
private:
    const char *data_;
    size_t size_;
};

// 重载判断操作符
inline bool operator==(const Slice& a, const Slice& b) {
    return ((a.size() == b.size()) && 
            memcmp(a.data(), b.data(), a.size()));
}

inline bool operator!=(const Slice& a, const Slice& b) {
    return !(a == b);
}

inline int Slice::compare(const Slice& x) const {
    const size_t min_size = (size_ < x.size_) ? size_ : x.size_;
    int r = memcmp(data_, x.data_, min_size);
    if (r == 0) {
        if (size_ < x.size_) r = -1;
        else if (size_ > x.size_) r = 1;
    }
    return r;
}

} // namespace leveldb

#endif // STORAGE_LEVELDB_INCLUDE_SLICE_H_
