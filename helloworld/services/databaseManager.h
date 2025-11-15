#pragma once
#include <drogon/orm/Mapper.h>
#include <drogon/orm/DbClient.h>
#include <drogon/drogon.h>
class DatabaseManager
{
public:
    static drogon::orm::DbClientPtr getClient(const std::string &name = "postgre_db")
    {
        return drogon::app().getDbClient(name);
    }
};