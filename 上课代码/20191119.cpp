#include <iostream>
using namespace std;


#if 0
// C 语言中类型转换：隐式类型转化 & 显式类型转化
int main()
{
	double d = 12.34;
	int a = d;

	int* pa = &a;
	pa = (int*)&d; // 编译阶段：直接报错

	cout << pa << endl;
	cout << &d << endl;

	const int c = 10;
	int* pc = (int*)&c;
	return 0;
}
#endif


#if 0
typedef void(*FUNC)();

int DoSomething(int i)
{
	cout << "DoSomething" << endl;
	return 0;
}


void Test()
{
	//
	// reinterpret_cast可以编译器以FUNC的定义方式去看待DoSomething函数
	// 所以非常的BUG，下面转换函数指针的代码是不可移植的，所以不建议这样用
	// C++不保证所有的函数指针都被一样的使用，所以这样用有时会产生不确定的结果
	//
	FUNC f = reinterpret_cast<FUNC>(DoSomething);
	f();
}

int main()
{
	double d = 12.34;
	int a = static_cast<int>(d);

	int* pa = &a;
	pa = reinterpret_cast<int*>(&d);

	const int c = 10;
	int* pc = const_cast<int*>(&c); // const int*
	return 0;
}
#endif

#if 0
class Base
{
public:
	virtual void func()
	{
		cout << "Base::func()" << endl;
	}

protected:
	int _b;
};

class Derived : public Base
{
public:
	void funcD()
	{
		cout << "Derived::funcD()" << endl;
	}

protected:
	int _d;
};


// pa--->基类对象  pa---->将其转化为派生类指针--->有风险  向下转型--dynamic_cast
// pa--->子类对象         将子类指针转化为基类指针-->安全 向上转型  支持
void fun(Base* pa)
{
	// dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回
	pa->func();  // 实现多态

	Derived* pb1 = static_cast<Derived*>(pa);
	Derived* pb2 = dynamic_cast<Derived*>(pa);

	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;

	// 如果pa指向的是子类对象，可能需要借助子类的成员函数做一些其他事情
	
	// 原因：在编译期间，编译器识别出pa是一个基类的指针
	// 因此pa只能调用基类的成员函数
	//pa->funcD();  // 编译失败

	// 如果想要调用派生类的函数，只能将pa转化为子类的指针
	// 如果pa真正指向的是一个子类对象，代码是安全的
	// 如果pa真正指向的是一个基类对象，代码不安全
	
	if (pb1)
		pb1->funcD();

	if (pb2)
		pb2->funcD();
}

int main()
{
	Base b;
	Derived d;

	// 赋值兼容规则
	b = d;
	Base* pb = &d;
	Base& rb = d;

	Derived* pd = dynamic_cast<Derived*>(&b);


	fun(&b);
	fun(&d);

	return 0;
}
#endif

#if 0
// 单参构造函数，或者除过第一个参数外其他参数都带有默认值的构造函数
class Date
{
public:
	explicit Date(int year, int month=1, int day=1)
		: _year(year)
		, _month(1)
		, _day(1)
	{
		cout << "Date::Date(int):" << this << endl;
	}


	Date& operator=(const Date& d)
	{
		cout << this << "=" << &d << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	~Date()
	{
		cout << "Date::~Date()" << this << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};


int main()
{
	Date d1(2019);

	// 1. 调用单参构造函数，用2020构造一个临时对象
	// 2. 用构造好的临时对象给d1赋值
	// 3. 赋值结束后，临时对象将被销毁
	d1 = 2020;

	return 0;
}
#endif

#if 0
#include <vector>
#include <map>


class Date
{
public:
	explicit Date(int year, int month = 1, int day = 1)
		: _year(year)
		, _month(1)
		, _day(1)
	{
		cout << "Date::Date(int):" << this << endl;
	}


	Date& operator=(const Date& d)
	{
		cout << this << "=" << &d << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	~Date()
	{
		cout << "Date::~Date()" << this << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	int a1 = 0;
	int a2(0);
	int a3{ 0 };

	int array[] = { 1, 2, 3, 4 };
	vector<int> v0(array, array+sizeof(array)/sizeof(array[0]));

	vector<int> v1{ 1, 2, 3, 4 };

	int array1[5]{1, 2, 3, 4, 5};
	int array2[]{1, 2, 3, 4, 5};


	map<string, string> m{ { "one", "1" }, {"tow", "2"} };

	int* pa = new int[10]{1,2,3,4,5,6,7,8,9,0};

	Date d1(2019);
	Date d2{ 2019, 11, 21 };

	return 0;
}
#endif

#if 0
#include <initializer_list>
namespace bite
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;

	public:
		vector()
		{
			_start = _finish = _end_of_storage = nullptr;
		}

		vector(const initializer_list<T>& il)
			: _start(new T[il.size()])
		{
			auto it = il.begin();
			_finish = _start;
			while (it != il.end())
			{
				*_finish++ = *it;
				++it;
			}

			_end_of_storage = _finish;
		}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
}

int main()
{
	bite::vector<int> v1;
	bite::vector<int> v2{ 1, 2, 3, 4 };
	
	// 范围for可以让用户写代码方便
	// 但是编译器最终会将范围for转化为迭代器方式打印：begin()/end()
	for (auto e : v2)
		cout << e << " ";
	cout << endl;
	
	return 0;
}
#endif

// Add(1, 2.0);
// Add(1.0, 2);

#if 0
// auto在返回值类型位置不能用
template<class T1, class T2>
auto Add(const T1& left, const T2& right)
{
	return left + right;
}
#endif


#if 0
template<class T1, class T2, class T3>
void Add(const T1& left, const T2& right, T3& ret)
{
	ret = left + right;
}

int main()
{
	//cout << Add(1, 3) << endl;

	int ret = 0;
	Add(1, 3, ret);
	cout << ret << endl;
	return 0;
}
#endif

#if 0
void TestFunc(int)
{}

typedef decltype(TestFunc) PF;

void(*set_malloc_handler(void(*f)()))()
{
	return nullptr;
}

typedef decltype(set_malloc_handler) SH;

int main()
{
	short a = 32760;
	short b = 32760;

	decltype(a+b) c = a + b;
	cout << typeid(c).name() << endl;

	cout << typeid(SH).name() << endl;

	cout << typeid(decltype(set_malloc_handler(nullptr))).name() << endl;
	return 0;
}
#endif

#if 0
// 返回值类型追踪
template<class T1, class T2>
auto Add(const T1& left, const T2& right)->decltype(left + right)
{
	return left + right;
}

int main()
{
	Add(1, 2.0);
	return 0;
}
#endif

/*
如果一个类什么都没有定义，编译器会自动生成六个默认的成员函数：
1. 构造函数
2. 拷贝构造函数
3. 析构函数
4. 赋值运算符的重载
5.6 两个&
*/

// 编译器生成的默认构造函数
// 1. 编译器到底是否会生成默认的构造函数？
// 答案：不一定,像单独的Date的日期类一定不会生成

// 2. 什么情况下编译器一定会生成默认的构造函数
//  答案：如果编译器需要，它自己就会生成
// 4个场景
// 1: 

#if 0
class Time
{
public:
	Time()
		: _hour(0)
		, _minute(0)
		, _second(0)
	{}

private:
	int _hour;
	int _minute;
	int _second;
};
class Date
{
public:
// 	Date()
// 	{}

private:
	int _year;
	int _month;
	int _day;
	Time _t;
};


int main()
{
	Date d;   // call Date::Date()

	return 0;
}
#endif

#if 0
// 2. 在继承体系中，如果基类定义了无参的构造函数，派生类没有显式定义任何构造函数
// 编译器将会给派生类生成一个默认的无参构造函数
// 作用：要在生成的无参构造函数初始化列表位置调用基类的构造函数

class A
{
public:
	A()
	{}

};

class B : public A
{};


int main()
{
	B b;
	return 0;
}
#endif


#if 0
// 带有虚函数的类，如果没有显式定义任何构造函数，编译器也会生成
class A
{
public:
	virtual void Test()
	{}
};


int main()
{
	A a;
	return 0;
}
#endif


class A
{};

class B : virtual public A
{};


int main()
{
	B b;
	return 0;
}