#pragma once
#include <drogon/HttpMiddleware.h>

class LoginMiddleware : public drogon::HttpMiddleware<LoginMiddleware>
{
public:
    void invoke1(const drogon::HttpRequestPtr &req,
                 drogon::MiddlewareNextCallback &&nextCb,
                 drogon::MiddlewareCallback &&mcb) override;
};
#pragma once
