#ifndef MongoDB_H
#define MongoDB_H

#include <cstdint>
#include <iostream>
#include <vector>
#include "bsoncxx/stdx/make_unique.hpp"
#include "bsoncxx/stdx/optional.hpp"
#include "bsoncxx/stdx/string_view.hpp"
#include "bsoncxx/json.hpp"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/view_or_value.hpp>

#include "mongocxx/instance.hpp"
#include "mongocxx/logger.hpp"
#include "mongocxx/pool.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/stdx.hpp"
#include "mongocxx/pipeline.hpp"
#include "mongocxx/uri.hpp"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

/**
* mongodb 操作类
**/
class MongoDB{
public:
    MongoDB();
    ~MongoDB();
    bool Initialize(std::unique_ptr<mongocxx::instance> instance,
        std::unique_ptr<mongocxx::pool> pool);
    mongocxx::pool::entry GetConn();
    mongocxx::stdx::optional<mongocxx::pool::entry> TryGetConnection();//尝试获取可用连接，多线程或协程环境必须用这个方法；
    bsoncxx::types::value& insert_one(bsoncxx::document::view_or_value doc);
    std::int32_t insert_many(std::vector<bsoncxx::document::value> docs);
    time_t convert_string_to_time_t(const std::string & time_string);
private:
    std::unique_ptr<mongocxx::instance> _instance = nullptr;
    std::unique_ptr<mongocxx::pool> _pool = nullptr;
};
extern MongoDB MongoDatabase;                                 ///mongodb

#endif
