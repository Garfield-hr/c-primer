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
- 隐式类型转换：依靠只接受一个实参的构造函数；类型转换只允许一步
