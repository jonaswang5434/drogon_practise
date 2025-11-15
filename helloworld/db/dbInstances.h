#pragma once
#include <drogon/orm/DbClient.h>
#include <drogon/drogon.h>
class DbInstance
{
public:
    static drogon::orm::DbClientPtr getDbClient()
    {
        static drogon::orm::DbClientPtr client = drogon::app().getDbClient("postgre_db");
        return client;
    }
};

// static std::once_flag flag;
// static drogon::orm::DbClientPtr client;
// std::call_once(flag, []()
//                { client = drogon::app().getDbClient(name); }

// );