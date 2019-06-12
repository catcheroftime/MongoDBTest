#include <mongocxx/logger.hpp>
#include "mongodb.h"
MongoDB MongoDatabase;
MongoDB::MongoDB(){
}
MongoDB::~MongoDB(){
}

class noop_logger : public mongocxx::logger {
public:
    virtual void operator()(mongocxx::log_level,
        mongocxx::stdx::string_view,
        mongocxx::stdx::string_view) noexcept {}
};


/**
* 初始化
**/
bool MongoDB::Initialize(std::unique_ptr<mongocxx::instance> instance,
    std::unique_ptr<mongocxx::pool> pool)
{
    _instance = std::move(instance);
    _pool = std::move(pool);

    return true;
}

mongocxx::pool::entry MongoDB::GetConn() {
    return _pool->acquire();
}

mongocxx::stdx::optional<mongocxx::pool::entry> MongoDB::TryGetConnection() {
    return _pool->try_acquire();
}
