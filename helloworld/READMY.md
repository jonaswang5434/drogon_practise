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
