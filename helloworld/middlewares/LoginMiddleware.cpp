
#include "LoginMiddleware.h"
#include <drogon/HttpResponse.h>

using namespace drogon;

void LoginMiddleware::invoke(const drogon::HttpRequestPtr &req,
                             drogon::MiddlewareNextCallback &&nextCb,
                             drogon::MiddlewareCallback &&mcb)
{
    std::string origin = req->getHeader("origin");

    if (origin.find("www.some-evil-place.com") != std::string::npos)
    {
        // intercept directly
        mcb(HttpResponse::newNotFoundResponse(req));
        return;
    }

    nextCb([mcb = std::move(mcb), origin](const HttpResponsePtr &resp)
           {
            // Do something after the next middleware returns
            resp->addHeader("Access-Control-Allow-Origin", origin);
            resp->addHeader("Access-Control-Allow-Credentials","true");
            mcb(resp); });
}
