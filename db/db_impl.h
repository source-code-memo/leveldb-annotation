
#ifndef STORAGE_LEVELDB_DB_DB_IMPL_H_
#define STORAGE_LEVELDB_DB_DB_IMPL_H_

#include "leveldb/db.h"

namespace leveldb {

class VersionEdit;
class VersionSet;

class DBImpl : public DB {
public:
    DBImpl(const Options& options, const std::string& name);
    virtual ~DBImpl();

    // DB 接口
    virtual Status Put(const WriteOptions&, const Slice& key, const Slice& value);
    virtual Status Delete(const WriteOptions&, const Slice& key);
    virtual Status Write(const WriteOptions&, WriteBatch* updates);
    virtual Status Get(const ReadOptions&, const Slice& key, std::string* value);

private:
    friend class DB;
    struct CompactionState;
    struct Writer;

    // 以下的成员变量由mutex_保护
    port::Mutex mutex_;
};

} // namespace leveldb

#endif // STORAGE_LEVELDB_DB_DB_IMPL_H_
