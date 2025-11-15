#include "demo_v1_User.h"
#include <json/json.h>
#include "db/dbInstances.h"

using namespace demo::v1;

// Add definition of your processing function here
void User::login(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback,
                 std::string &&userId,
                 const std::string &password)
{
    LOG_DEBUG << "uSER" << userId << "login";
    Json::Value ret;
    ret["result"] = "ok";
    ret["token"] = drogon::utils::getUuid();
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void User::getInfo(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   std::string userId,
                   const std::string &token) const
{
    LOG_DEBUG << "User" << userId << " get his information";
    auto clientPtr = DbInstance::getDbClient();
    clientPtr->execSqlAsync("select * from users where user_name=$1", [callback](const drogon::orm::Result &result)

                            {
                                Json::Value ret;
                                if(!result.empty())
                                {
                                    ret["user_name"]=result[0]["user_name"].as<std::string>();
                                    ret["email"]=result[0]["email"].as<std::string>();
                                    ret["gender"]=result[0]["gender"].as<int>();
                                }

                                auto resp=HttpResponse::newHttpJsonResponse(ret);
                                callback(resp); }, [callback](const drogon::orm::DrogonDbException &e)
                            {
                                    Json::Value ret;
                                    ret["result"]="error";
                                    ret["msg"]=e.base().what();
                                    auto resp=HttpResponse::newHttpJsonResponse(ret);
                                    callback(resp); }, userId);
}
