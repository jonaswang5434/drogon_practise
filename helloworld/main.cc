#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#endif

#include <drogon/drogon.h>
#include <controllers/HelloController.h>
#include <middlewares/LoginMiddleware.h>
using namespace drogon;

int main()

{
    drogon::app().registerMiddleware<LoginMiddleware>();
    drogon::app().loadConfigFile("../config.yaml");
    app().registerHandler(
        "/",
        [](const HttpRequestPtr &request,
           std::function<void(const HttpResponsePtr &)> &&callback)
        {
            LOG_INFO << "connected:"
                     << (request->connected() ? "true" : "false");
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Hello world");
            callback(resp);
        },
        {Get});

    app().registerHandler(
        "/user/{user-name}",
        [](const HttpRequestPtr &,
           std::function<void(const HttpResponsePtr &)> &&callback,
           const std::string &name)
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("hello, " + name + "!");
            callback(resp);
        },
        {Get}

    );

    app().registerHandler(
        "/hello_user",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback)
        {
            auto resp = HttpResponse::newHttpResponse();
            auto name = req->getOptionalParameter<std::string>("User");
            if (!name)
                resp->setBody("Please tell me you name");
            else
                resp->setBody("Hello," + name.value() + "~");
            callback(resp);
        },
        {Get});

    app().setBeforeListenSockOptCallback([](int fd)
                                         {
                                             LOG_INFO << "SetBeforeListenSockOPtCallback:" << fd;
#ifdef _WIN32
#elif __linux__
#ifdef TCP_FASTOPEN
                                             int enable = 1;
                                             if (setsockopt(
                                                     fd, IPPROTO_TCP, TCP_FASTOPEN, &enable, sizeof(enable)) == -1)
                                             {
                                                 LOG_INFO << "setsockopt TCP_FASTOPEN failed";
                                             }
#endif
#else
#endif
                                         })
        .setAfterAcceptSockOptCallback([](int) {});
    // Set HTTP listener address and port
    // app().addListener("0.0.0.0", 8081);

    app().run();
}
