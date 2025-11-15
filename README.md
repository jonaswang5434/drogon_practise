# c++ 右值 &&
“右值引用”并不等于“必须是右值”。<br>
> C++ 有一个机制叫 引用折叠（reference collapsing）： <br>
* 当模板参数是右值引用时，如果传入的实参是左值，编译器会自动“折叠”为普通引用。<br>
* 如果传入的是右值或lambda函数时,因为二者都是在"="右边,所以此时模板函数就自动折叠为右值引用.<br>
例如:
```
template<typename T>
void f(T &&x);

int a = 5;
f(a);        // a在=左边,传左值 → T = int& → 参数类型 = int& && → 折叠为普通引用 int&
f(5);        // 5为变量的值,是放在=右边的,传右值 → T = int → 参数类型 = int&&
```
例2:
```
template <typename FUNCTION1,
        typename FUNCTION2,
        typename... Arguments>
void execSqlAsync(const std::string &sql,
                FUNCTION1 &&rCallback,
                FUNCTION2 &&exceptCallback,
                Arguments &&... args) noexcept;
```
函数定义rCallback 和 exceptCallback 都是右值引用.而下面的函数都是用lambda函数作为右值参数传入,以形成右值引用,从而避免了复制操作
```
auto clientPtr = drogon::app().getDbClient();
clientPtr->execSqlAsync("select * from users where org_name=$1",
                            [](const drogon::orm::Result &result) {
                                std::cout << result.size() << " rows selected!" << std::endl;
                                int i = 0;
                                for (auto row : result)
                                {
                                    std::cout << i++ << ": user name is " << row["user_name"].as<std::string>() << std::endl;
                                }
                            },
                            [](const DrogonDbException &e) {
                                std::cerr << "error:" << e.base().what() << std::endl;
                            },
                            "default");
```

### Lvalue Reference vs Rvalue Reference
```
LValue reference:
int a = 10;
int& r = a;

RValue reference:
int&& r = 10;
```
* 右值引用能触发移动语义（move semantics）

std::vector<int> v; <br>
v.push_back(std::vector<int>{1,2,3}); //{1,2,3} 是右值，可以触发移动，不会复制 <br>
* 可以用 std::move 把左值变右值引用
std::string a = "hello";
std::string b = std::move(a);  // 移动

* 普通引用不能绑定右值 <br>
> int& r = 5;   // ❌ 错误 <br>
* 右值引用不能绑定左值  <br>
> int a = 5; <br>
> int&& r = a;  // ❌ 错误

### 总结
普通引用是“借用”

借现成的对象

不改变所有权

不负责销毁


右值引用是“接管”

绑定临时对象

可以拿走资源（移动）

一般与 std::move 一起用