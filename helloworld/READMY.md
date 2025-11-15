### static function vs function

静态函数：只能访问 静态成员变量 或其他静态函数,没有 this<br>

普通函数：可以访问 普通成员变量、普通函数、静态成员变量、静态函数

```
class MyClass {
    static int staticVar;
    int normalVar;
public:
    static void staticFunc() {
        staticVar = 1;   // ✅ 可以访问静态变量
        // normalVar = 2; // ❌ 错误，不能访问非静态成员
    }

    void normalFunc() {
        normalVar = 2;   // ✅ 可以访问普通变量
        staticVar = 1;   // ✅ 可以访问静态变量
    }
};


MyClass::staticFunc();  // ✅ 静态函数
staticFunc();           // ❌ 不能直接调用（除非 using namespace 或全局作用域）


```

- 使用场景

静态函数常用于：

工具函数（不依赖对象状态）

单例模式的访问接口

回调函数或全局方法封装到类里

- 普通函数常用于：

操作对象状态

访问或修改成员变量

###

orm::DbClientPtr getDbClient(const std::string &name = "postgre_prod"); <br>

> name is the value of the name configuration option in the configuration file to distinguish multiple different DbClient objects of the same application.

### Filter vs middleware

Filter 是“拦截器”，Middleware 是“管道工具”。

Filter：用于 控制访问（鉴权、限制访问、检查参数）。

Middleware：用于 处理请求生命周期（日志、统计、统一前后处理）。

⭐ 核心区别（一句话看懂）

Filter 是专门用来 决定请求能不能进入 Controller 的。

典型用途：
> JWT 鉴权<br>
> 检查 Headers<br>
> 检查参数是否合法<br>
> 限流<br>
> 黑名单拦截<br>

⭐ Middleware：贯穿整个请求链的处理器

Middleware 是对 request 和 response 的“包裹”。

进入 → 前置处理 → controller → 后置处理 → 返回

典型用途：
> 请求日志<br>
> 响应日志<br>
> 统计请求耗时<br>
> 注入全局变量<br>
> 统一错误处理<br>

⭐ 谁更早执行？

顺序如下：

Middleware（前）<br>
↓<br>
Filter<br>
↓<br>
Controller<br>
↓<br>
Middleware（后）
