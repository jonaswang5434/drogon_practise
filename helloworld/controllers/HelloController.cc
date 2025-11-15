#include "HelloController.h"
#include <drogon/drogon.h>

void HelloController::hello(const HttpRequestPtr &,
                            std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("Hello from HelloController!");
    callback(resp);
}
