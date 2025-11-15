#include "demo_v1_User.h"
#include <json/json.h>
using namespace demo::v1;

// Add definition of your processing function here

void User::getInfo(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   std::string userId) const
{
    LOG_DEBUG << "USER" << "GET HIS INFO";
    Json::Value ret;
    ret["result"] = "ok";
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
};
