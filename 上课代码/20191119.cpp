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

// 构造函数作用：初始化对象，不负责为对象开辟空间
// Date* pd = new Date;
class Date
{
public:
// 	Date()
// 	{}

	Date(int year){}

private:
	int _year;
	int _month;
	int _day;
	//Time _t;
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

struct Goods
{
	string _name;
	double _price;
};

#if 0
#include <algorithm>


// 1. 函数指针: 实现一个比较功能
bool isLess(const Goods& g1, const Goods& g2)
{
	return g1._price < g2._price;
}


// 2. 通过仿函数
struct IsGreater
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1._price > g2._price;
	}
};


// Date

// Time
int main()
{


	Goods gds[] = { { "苹果", 2.1 }, { "相交", 3 }, { "橙子", 2.2 }, { "菠萝", 1.5 } };
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), isLess);

	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), IsGreater());
	return 0;
}
#endif

#if 0
#include <algorithm>

int main()
{
	Goods gds[] = { { "苹果", 2.1 }, { "相交", 3 }, { "橙子", 2.2 }, { "菠萝", 1.5 } };
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& l, const Goods& r)
		->bool
	{
		return l._price < r._price;
	});
	return 0;
}
#endif

#if 0
int Add(int left, int right)
{
	return left + right;
}

void TestFunc()
{
	int a = 10, b = 20;
	Add(a, b);
}

int main()
{
	int a = 10, b = 20;

	// [捕获列表](参数列表)->returnType{实现体};

	auto Add = [](int a, int b)->int{
		cout << "[](int a, int b)->int{}" << endl;
		return a + b; 
	};

	int c = 30, d = 40;
	Add(c, d);


	[]{};
	return 0;
}
#endif

#if 0
int main()
{
	int a = 10, b = 20;
	int c = 0;

	cout << &c << endl;

	// c 按照值的方式进行捕获
	auto Add = [c](int left, int right)mutable->int
	{
		cout << &c << endl;
		c = left + right;
		return c;
	};

	Add(a, b);

	return 0;
}
#endif

#if 0
int main()
{
	int a = 10, b = 20;
	int c = 0;

	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;

	// c 按照值的方式进行捕获
	auto Add = [=](int left, int right)mutable->int
	{
		cout << &a << endl;
		cout << &b << endl;
		cout << &c << endl;

		c = left + right;
		return c;
	};

	Add(a, b);

	return 0;
}
#endif

#if 0
int main()
{
	int a = 10, b = 20;
	int c = 0;

	cout << &c << endl;

	// c 按照值的方式进行捕获
	auto Add = [&c](int left, int right)mutable->int
	{
		cout << &c << endl;
		c = left + right;
		return c;
	};

	Add(a, b);

	return 0;
}
#endif

#if 0
int main()
{
	int a = 10, b = 20;
	int c = 0;

	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;

	// c 按照值的方式进行捕获
	auto Add = [&](int left, int right)mutable->int
	{
		cout << &a << endl;
		cout << &b << endl;
		cout << &c << endl;

		c = left + right;
		return c;
	};

	Add(a, b);
	return 0;
}
#endif

#if 0
int main()
{
	int a = 10, b = 20;
	int c = 0;

	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;

	// =: 以值的方式捕获所有变量
	// a：以值的方式捕获a
	// a重复捕获  代码编译时报错
	auto Add = [=, a](int left, int right)mutable->int
	{
		cout << &a << endl;
		cout << &b << endl;
		cout << &c << endl;

		c = left + right;
		return c;
	};

	Add(a, b);
	return 0;
}
#endif



#if 0
int main()
{
	int a = 10, b = 20;
	int c = 0;

	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;

	if (1)
	{
		// =: 以值的方式捕获所有变量
		// &a：以引用的方式捕获a
		//auto Add = [=, &a](int left, int right)mutable->int
		auto Add = [&, a](int left, int right)mutable->int
		{
			cout << &a << endl;
			cout << &b << endl;
			cout << &c << endl;

			c = left + right;

			return c;
		};

		Add(a, b);
	}
	
	return 0;
}
#endif

#if 0
//auto Add = [](int a, int b)->int{ return a + b; };

int main()
{
	Add(10, 20);

	return 0;
}
#endif

//

#if 0
int g_a = 10;
int main()
{
	int a = 10;
	int b = 20;

	auto Add = [a, b](int left, int right)->int{ return left + right; };
	Add(10, 20);

	return 0;
}
#endif

#if 0
// 定义一个没有参数，没有返回值类型的函数指针变量
void(*PF)();


//main::<lambda_70cf8d9e75d81d4fee39ed2f2f0febe9>& main::<lambda_70cf8d9e75d81d4fee39ed2f2f0febe9>::operator=(const main::<lambda_70cf8d9e75d81d4fee39ed2f2f0febe9> &);
// main::<A>& operator=(const main::<A>);

int main()
{
	auto f1 = []{cout << "hello world" << endl; };
	auto f2 = []{cout << "hello world!" << endl; };
	// 此处先不解释原因，等lambda表达式底层实现原理看完后，大家就清楚了
	//f1 = f2; // 编译失败--->提示找不到operator=()
	// 允许使用一个lambda表达式拷贝构造一个新的副本
	
 	auto f3(f2);
 	f3();
 	// 可以将lambda表达式赋值给相同类型的函数指针
 	PF = f2;
 	PF();
	return 0;
}
#endif

#if 0
class Rate
{
public:
	Rate(double rate) : _rate(rate)
	{}

	double operator()(double money, int year)
	{
		return money * _rate * year;
	}
private:
	double _rate;
};


int main()
{
	// 函数对象
	double rate = 0.49;
	Rate r1(rate);
	r1(10000, 2);

	// lamber
	auto r2 = [rate](double monty, int year)->double
	{
		return monty*rate*year; 
	};

	r2(10000, 2);
	return 0;
}
#endif

#if 0
int main()
{
	const int& cra = 10;
	return 0;
}
#endif


#if 0
// C++98: 引用概念
// C++11: 右值引用: 也是一个别名，只能引用右值
int Test()
{
	int a = 10;
	return a;
}

int main()
{
	int a = 10;
	int& ra = a;

	a = 10;
	cout << &a << endl;

	// int&& rra = a;  // 编译失败：因为a是左值
	int&& rra = 10;


	const int c = 20;
	// cout << &c << endl;
	//const int&& rrc = c;

	int b1 = 1, b2 = 2;
	// b1 + b2 = 10;
	// &(b1 + b2);

	// b1+b2的表达式结果是右值
	int&& rrb = b1 + b2;
	
	// ++b1表达式结果是左值
	//++b1 = 20;

	//Test() = 10;
	//(&Test());
	int&& rt = Test();

	int t = Test();
	return 0;
}
#endif

#if 0
/*
右值： 1.不能放在赋值运算符的左侧
      2.不能取&
	  3.有些表达式的结果可能是左值：a+b
	  4.有些函数的返回值结果：
	  int  Test()
	  {
	      int a = 10;
		  return a;
	  }

	  只能将其作为判断是否为右值的参考
*/


int& Test(int& a)
{
	a = 10;
	return a;
}

int main()
{
	int b = 0;
	Test(b) = 100;
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test()
	{
		cout << "Test():" << this << endl;
	}

	Test(const Test& t)
	{
		cout << "Test(const Test&):" << this << endl;
	}

	Test& operator=(const Test& t)
	{
		cout << this << "=" << &t << endl;
		return *this;
	}

	~Test()
	{
		cout << "~Test():"<<this << endl;
	}
};

Test func(Test t)
{
	Test temp;
	temp = t;
	return temp;
}

void TestFunc()
{
	Test t1;
	Test t2(t1);
	t2 = func(t1);
}

int main()
{
	TestFunc();
	return 0;
}
#endif

#if 0
int main()
{
	int&& ra = 10;

	int b = 10;
	// int&& rb = b; 
	int&& rb = move(b);  // 将一个左值转化为右值

	return 0;
}
#endif

class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}


	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	// 移动构造：将s中的资源转移给当前对象
	String(String&& s)
		: _str(s._str)
	{
		s._str = nullptr;
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* str = new char[strlen(s._str) + 1];
			strcpy(str, s._str);
			delete[] _str;
			_str = str;
		}

		return *this;
	}

	// 移动赋值
	String& operator=(String&& s)
	{
		if (this != &s)
		{
			delete[] _str;
			_str = s._str;
			s._str = nullptr;
		}

		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}

	String operator+(const String& s)
	{
		char* str = new char[strlen(_str) + strlen(s._str) + 1];
		strcpy(str, _str);
		strcat(str, s._str);

		String strRet(str);
		return strRet;
	}

	char& operator[](size_t index)
	{
		return _str[index];
	}
private:
	char* _str;
};

#if 0
void TestString()
{
	String s1("hello ");
	String s2("world");
	String s3;
	s3 = s1 + s2;
}

int main()
{
	//TestString();

	String s1("hello");

	// move的误用
	String s2(move(s1));
	s1[0] = 'H';
	return 0;
}
#endif

class Person
{
public:
	Person(char* name, char* sex, int age)
		: _name(name)
		, _sex(sex)
		, _age(age)
	{}

	Person(const Person& p)
		: _name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{}

#if 0
	Person(Person&& p)
		: _name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{}
#else
		Person(Person&& p)
		: _name(move(p._name))
		, _sex(move(p._sex))
		, _age(p._age)
	{}
#endif
private:
	String _name;
	String _sex;
	int _age;
};

Person GetTempPerson()
{
	Person p("prety", "male", 18);
	return p;
}

int main()
{
	Person p(GetTempPerson());
	return 0;
}


