#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class HelloController : public HttpController<HelloController>
{
public:
  METHOD_LIST_BEGIN
  METHOD_ADD(HelloController::hello, "/hello", Get);
  // list path definitions here;
  // PATH_ADD("/path", "filter1", "filter2", HttpMethod1, HttpMethod2...);
  METHOD_LIST_END
  void hello(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
