
#include "db_impl.h"

namespace leveldb {

DB::~DB() { }

Status DB::Open(const Options& options, const std::string& dbname,
                DB** dptr) {
    *dptr = NULL;

    DBImpl* impl = new DBImpl(options, dbname);
    impl->mutex_.Lock();
    VersionEdit edit;
}

} // namespace leveldb
