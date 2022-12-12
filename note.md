# Index

## Chapter 2
### 类型转换
- 算数值转布尔，为零则转为False,否则为True。
- 浮点数转整形，截断——向零取整。
- 给无符号数赋超过范围的值：取模。  
    eg: unsigned a = -1 // a = 2^32 - 1
- 给有符号数赋值超过范围，结果是未定义的。
- 算术表达式既含有无符号数有含有int时，int会被转换成无符号数。
### 初始化
- 初始化的三种方式
    - int a = 0;
    - int a = {0};
    - int a{0};
    - int a(0); // 在结构体初始化中不能使用
- 默认初始化
    - 定义在函数外部：初始化为零。
    - 定义在函数内部：不被初始化；建议声明时显示初始化。
### const
- 顶层const与底层const
    - 顶层const指对象本身是不可变的，因此必须初始化，引用也不存在顶层const.
    - 底层const表示指针指向的对象是常量
- 区分顶层const和底层const从右往左读
- typedef char *newType是新建了一种type，const newType 是顶层const
- 常量引用可以引用字面值，表达式
- constexpr:常量表达式，值不会改变，在编译时就可以确定。
- auto忽略顶层const但保留底层const
- 对常量的引用或是取地址得到底层const
- decltype 保留顶层和底层const
### decltype
- 左值经过decltype返回引用，如*p
- 变量加上括号会被判断为左值从而返回引用

## Chapter 3
### String
- string.size()的类型是string::size_type,无符号数。
- string可以和string或字符串字面值相加，字符串字面值不能相加。两个仅由空格隔开的字符串字面值是一个整体。
- string可以用大小运算符比较大小。结果为字典顺序。
- is >> s，从流中读取字符串，以空格分隔
- 从流中读取一行getline(is, s)
### Vector
- 初始化
    - vector<T> a;
    - vector<T> a = b;
    - vector<T> a(10);
    - vector<T> a(10, b);
    - vector<T> a{b, c, d};
- 不能使用for改变vector等容器的大小
### Iterator
- 只读: auto it = v.cbegin();
- 二分：mid = begin + (end - begin)/2
### 多维数组
- for range访问时除了最内层循环都要使用引用。因为无法对指针for range。
## chapter 4
### 强制类型转换
- dynamic_cast
- static_cast: 用来改变变量类型，不能改变const性质。
- const_cast: 改变const性质。
- reinterpret_cast: 位模式重新解释，可以改变指针类型。
## chapter 6 function
- 形参类型全部相同但数量未知，可以用initializer_list<T>
- 尾置返回：auto f() -> int (*)[10]; // 返回数组指针
- 函数指针
    - 形参函数类型自动转换为函数指针(作为一个值使用时)，返回值则不会
    - 用decltype作用于函数时类型时函数，需要指针结果需要显示加上*
## chapter 7 class
- 返回*this可以支持类似a.add().add()的连续操作
- 隐式类型转换：依靠只接受一个实参的构造函数；类型转换只允许一步，explicit 关键字可以让构造函数不能用于隐式转换
- const 成员函数，const紧跟参数列表，表示this是底层const，不可以对非常量对象调用普通的成员函数
## chapter 8 IO
- 输出流需要刷新缓冲区才会实际输出，可以通过endl, ends, flush显示刷新，程序返回，缓存区满或者关联的输入流被调用时也会刷新缓冲区
- IO 迭代器的一个例子
```cpp
istream_iterator<int> in(cin), eof;
cout<<accumulate(in, eof, 0)<<endl;
```
## chapter 9 顺序容器
### 赋值和swap
- array可以用初始化列表初始化但不支持用初始化列表赋值
- swap交换地址, swap array 是值交换；C++11建议统一使用非成员函数的swap
- assign允许使用相容但不相同的类型赋值
- forward_list不支持size
### 顺序容器操作
- emplace 构造而不是拷贝，可以传递几个参数构造新的对象
- []访问不检查越界，at()检查
- push_back(), emplace_back()返回void
- insert返回指向添加的第一个元素的迭代器
- erase返回指向被删除元素后的第一个元素的迭代器
## chapter 10 泛型算法
### algorithm
- find
- sort
### numeric
- accumulate
### lambda
[] () -> type {}
- 必须有
- 如果函数体内容超过一行，默认返回void
### bind
- 定义在functional中
- bind(func, a, b, c)等同于调用func(a, b, c)
- g = bind(func, a, _1)，调用 g(b) 等同于调用func(a, b)
- 需要绑定引用参数时使用ref函数， bind(print, ref(os), _1)

## chapter 11 关联容器
无序关联容器unordered_map, unorderd_set

## chapter 12 智能指针
### 定义和改变shared_otr
- shared_ptr<T> p = make_shared<T>(args) 推荐使用这种方式而非new创建智能指针
- shared_ptr<T> p(q)，q指向new分配的内存。智能指针的构造函数时explicit，不能隐式地用普通指针转换
- shared_ptr<T> p(u), 从unique_ptr u接管对象所有权
- shared_ptr<T> p(q,d), 从内置指针q接管所有权，将用d()代替delete
- shared_ptr<T> p(p2, d), 同上
- p.reset(), p.reset(q), p.reset(q, d)， 若p是唯一指向其对象的shared_ptr，reset会释放此对象。q为p释放后指向的地址；若传递了d，将调用d()而非delete
#### 注意事项
- 不要混用内置指针和智能指针
- 不要用get()初始化另一个智能指针

### unique_ptr
只有一个unique_ptr指向一个给定对象，不可拷贝。
- unique_ptr<T> u1
- unique_ptr<T, D> u2
- unique_ptr<T, D> u(d)
- u = nullptr
- u.release() 放弃控制权并将u置空，返回指针
- u.reset(), u.reset(q), u.reset(nullptr) 如果提供了内置指针q，令u指向该对象，否则置空
- unique_ptr默认支持动态数组，shared_ptr需要定义删除器

### allocator
- allocator<T> a
- a.allocate(n)
- a.deallocate(p, n)
- a.construct(p, args) 用args在p指向的内存中构造一个对象
- a.destroy(p) 对p指向的对象执行析构函数
- uninitialized_copy(b, e, b2), uninitialized_copy_n(b, n, b2)拷贝b到b2
- uninitialized_fill(b, e, t), uninitialized_fill_n(b, n, t)

## chapter 13
- 有const成员，则不会定义合成拷贝构造函数， 不能使用合成拷贝赋值运算符
- 有引用成员，合成拷贝赋值运算符被定义为删除的
- 阻止拷贝构造或赋值应该用=delete而不是将其定义为private
- 拷贝并交换：先用拷贝构造函数构造副本，再将副本与左侧对象交换（处理了自赋值并且是异常安全的）
- 拷贝赋值函数：一般需要实现拷贝构造+析构的
### 13.5提供了一个动态内存管理的样本，需细看
### move
- move将左值转换为右值，用户需要确保之后除了赋值和销毁不再使用它。
- 使用move时应该使用std::move
- 使用make_move_iterator将一个普通迭代器转换为一个移动迭代器
### 右值引用和成员函数
- 在参数列表后加一个&可以使操作对象必须为可修改的左值
- 有const时&必须跟在const之后
- 重载时或者同名函数都没有引用控制符或者都有，不可省略

## chapter 14 运算符重载
- 如果类同时定义了算术运算符和相关的复合赋值运算符，通常应该使用复合赋值来实现算数运算符
- 后置自增自减运算符接受一个额外的int形参（不被使用）以区分
- 重载的箭头运算符必须返回类的指针或者定义了箭头运算符的某个对象
### 标准库定义的函数对象 没看懂

## chapter 15 OOP
- override表示重写，跟在const或&后面
- 类名后接final防止继承
- 派生类向基类的转换只对指针有效
- 基类向派生类不存在隐式类型转换
- 派生类向基类的转换可能因为访问受限而不可行
- 纯虚函数,在最后加上=0
- 派生访问说明符控制的是派生类对基类的访问权限
- 用户使用D->B转换需要公有继承，成员和友元不受影响，D的派生类最少需要受保护的继承
- 仅需覆盖重载函数的少数实例时，可以using声明这些函数
- using可以让编译器基于基类自动生成构造函数，不会改变其访问特性
- 派生类的构造函数需要显示地调用基类的构造函数，析构函数则不需要

## chapter 16 模板与泛型编程
- 模板中定义类型参数 template<typename T>, 非类型参数 template<unsigned N>,类 template<typename T> class A
- 在类模板的作用域内，我们可以直接使用模板名而不必指定模板实参
- 声明一个模板类的所有实例都为友元 template<typename T> friend class A
- 成员模板不能是虚函数
- extern实例化声明 extern template class Blob<string>;和普通类模板的实例化不同，显式声明实例化会实例化所有成员函数
### 类型转换与模板类型参数
- 顶层const在模板参数匹配会被忽略；数组或函数指针转换也是可行的
- 可以显示指定模板函数类型，在返回值是模板时常用
- 用尾置返回加decltype可以解决返回值位置的问题
- 类型转换模板remove_reference<int&>::type是int  
    std::move 的实现
    ```cpp
    template<typename T>
    typename remove_reference<T>::type&& move(T&& t)
    {
        return static_cast<typename remove_reference<T>::type &&>(t);
    }
    ```
- 引用折叠，在模板函数中，对于一个右值引用模板，编译器可推断左值实参为引用，并将两个引用折叠为一个左值引用
- 特例化： 不太懂
## chapter 17 标准库特殊设施
- tuple
- bitset
- regular expression
- 随机数
- IO格式化
## chapter 18 用于大型程序的工具
- 异常处理: catch(...) throw; 捕获所有异常，继续抛出异常
- 名字空间: include位于名字空间之外
- 虚继承: 不论虚基类在继承体系中出现多少次，派生类仅包含一个贡献的虚基类子对象

## 刷题笔记
### 内存分配
#### 有效对齐值
- 结构体第一个成员的偏移量为零
- 之后每个成员偏移量是min(size, 对齐量)的整数倍
- 结构体总大小为默认有效对齐值和结构体中最大数据成员长度的整数倍
```cpp
//32位系统
#include<stdio.h>
struct
{
    int i;    
    char c1;  
    char c2;  
}x1;

struct{
    char c1;  
    int i;    
    char c2;  
}x2;

struct{
    char c1;  
    char c2; 
    int i;    
}x3;

int main()
{
    printf("%d\n",sizeof(x1));  // 输出8
    printf("%d\n",sizeof(x2));  // 输出12
    printf("%d\n",sizeof(x3));  // 输出8
    return 0;
}
```
#### 类的内存分布
- 有虚函数无继承:虚函数表（4字节），按声明顺序排列的各个成员变量
- 有虚函数有继承，虚函数表，基类成员，派生类成员
- 多继承，各个基类都含有自己的虚函数表
- 虚继承，先是各个固定的派生类，随后才是虚继承共用的派生类
#### 位域
告诉编译器只使用部分字节，int x: 3表示只使用三个字节
### STL
#### 迭代器失效
- 序列式容器 vector, string
    - erase导致删除处的迭代器和之后所有的迭代器，引用和指针失效; erase会返回下一个有效的迭代器
    - insert导致插入处和之后所有的迭代器，引用和指针失效
    - push_back 如果重新分配内存，导致所有迭代器，引用和指针失效
- 序列式容器 deque
    - 插入，删除首尾之外的任何位置导致所有迭代器，引用和指针失效
    - 插入首尾会导致迭代器失效，但不影响指向存在的元素的引用和指针失效
    - 删除首尾不会导致其他位置的迭代器，引用和指针失效
- 链表式容器 list, forward_list
    - 插入无任何影响
    - 删除仅影响当前迭代器
- 关联容器 map, key
    - 插入和删除仅影响当前迭代器，递增迭代器即可解决

### 小知识点
- 构造函数不能是虚函数
- 逗号表达式的值是最后一个表达式的值
- memmove, memcopy都是二进制拷贝，memmove在源和目的有重叠的时候依然可以成功
- 重载函数不能以返回值为判断依据
- 类成员在初始化列表被初始化时，成员的构造函数先于类的构造函数被执行
- char 用单引号，双引号时字符串常量
- 函数传递数组时退化为指针
- 静态成员函数仅能访问静态成员
- 栈可以动态分配内存，用alloca
- 列表初始化按照变量声明顺序初始化
- 编译器会自动为空类生成构造函数，拷贝构造函数，拷贝赋值函数，析构函数
- 空结构体在C中大小为零，在C++中大小为1
