# Callback:

`  virtual void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                        std::function<void (const HttpResponsePtr &)> &&callback)override;`

> callback 是每次请求都会右drogon自动生成,callback的类型是`std::function<void (const HttpResponsePtr &)> && ` , callback接收参数的类型为`const HttpRequestPtr &`,其来自std::function<void(const HttpResponsePtr &)> 里.<br>
外层 std::function<...> 表示这是一个可调用对象；<br>
里面的 void(const HttpResponsePtr &) 表示这个函数对象：<br>
* 接收一个参数：const HttpResponsePtr &
* 返回类型是 void


# 模板继承
`class User : public drogon::HttpController<User>` <br>
> User 是继承drogon::HttpCOntroller的,但是可以把User 作为模板参数传递给基类,让基类在编译时知道派生类的类型,好处:<br>
* 减少虚函数开销,
* 框架注册路由时可以用User的派生类生成控制器对象.
