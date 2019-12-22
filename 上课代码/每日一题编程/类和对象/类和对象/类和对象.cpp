#include<iostream>
using namespace std;

#if 0
int a1 = 10;
int a = 20;//在C++中可以定义另个相同名称的变量

int main()
{
	int a = 10;
	cout << a << endl;//打印的是是局部变量a
	system("pause");
	return 0;
}
#endif


#if 0
int a = 1;

namespace N1
{
	int a = 10;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}
}

//命名空间可以嵌套
namespace N2
{
	int a = 30;
	int b = 40;
	int Sub(int left, int right)
	{
		return left - right;
	}

	namespace N3
	{
		int a = 50;
		int b = 60;
		int Mul(int left, int right)
		{
			return left * right;
		}
	}
}
//直接在成员前加命名空间名字::
int main()
{
	int a = 70;
	printf("%d\n", a);//访问主函数中的a；70
	printf("%d\n", ::a);//访问全局变量中的a，1
	printf("%d\n", N1::a);//访问N1命名空间中的a，10
	printf("%d\n",N2::N3::a);//访问N2命名空间中嵌套的命名空间中N3的a，50
	system("pause");
	return 0;
}
#endif
#if 0
namespace N1
{
	int a = 10;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}
}

using N1::a;//可以直接写a，不用再麻烦得写N1::a;

//int a = 30;
int main()
{
	printf("%d\n", a);
	system("pause");
	return 0;
}
#endif
#if 0
namespace N1
{
	int a = 10;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}
}

using namespace N1;//可以直接用N1命名空间中的变量和函数
int main()
{
	printf("%d\n", Add(a,b));
	system("pause");
	return 0;
}
#endif

#if 0
//如果一个工程中存在多个相同名称命名空间时，编译器会将其合并成一个
namespace N1
{
	int a = 10;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}
}

namespace N2
{
	int c = 10;
	int d = 20;
	int Sub(int left, int right)
	{
		return left -right;
	}
}
#endif

#if 0
int main()
{
	int a;
	double b;
	cin >> a;
	cin >> b;
	cout << a << " " <<b << endl;

	cin >> a >> b;
	cout << a << " " << b << endl;

	cout << 10;
	cout << 12.34 << " " << 'A' << "\n";
	cout << "Hello world" << endl;

	system("pause");
	return 0;
}
#endif
#if 0
//全缺省参数：所以参数都带有默认值
void TestFunc(int a = 1, int b = 2, int c = 3)
{
	cout << a << " " << b << " " << c << endl;
}

int main()
{
	TestFunc();//1,2,3
	TestFunc(10);//10,2,3
	TestFunc(10, 20);//10,20,3
	TestFunc(10, 20, 30);//10,20,30
	system("pause");
	return 0;
}
#endif

#if 0
//半缺省参数：部分参数带有默认值  要求：只能从右往左给出
void TestFunc(int a , int b = 2, int c = 3)
{
	cout << a << " " << b << " " << c << endl;
}

int main()
{
	TestFunc(10);
	TestFunc(10, 20);
	TestFunc(10, 20, 30);
	system("pause");
	return 0;
}
#endif
#if 0
void Testfunc(int a = 10);//
void Testfunc(int a = 20)
{
	cout << a << endl;
}
int main()
{
	Testfunc();//编译器不知道应该调用哪个函数
	return 0;
}
#endif

#if 0
//函数重载：必须在相同的作用域，相同名字的函数，如果参数列表不同（个数、类型、类型次序）
//与返回值类型是否相同无关
int Add(int left, int right)
{
	return left + right;
}
double Add(double left, double right)
{
	return left + right;
}
namespace N
{
	char Add(char left, char right)
	{
		return left + right;
	}
}
int main()
{
	//编译器在编译阶段，必须对实参的类型进行推演，根据推演的实参类型的结果选择调用合适的函数
	Add(1, 2);
	Add(1.0, 2.0);
	return 0;
}
#endif

#if 0
//1
void Testfunc()
{}
//2和1是参数个数不同
//2
void Testfunc(int a)
{}
//3
void Testfunc(int a,double b)
{}
//3和4不同：参数类型次序
//4
void Testfunc(double a,int b)
{}
//2和5参数的类型
//5
int Testfunc(char a)
{
	return 0;
}
//6
char Testfunc(char a)
{
	return 0;
}
int main()
{
	int ret1 = Testfunc('a');
	char ret2 = Testfunc('b');

	Testfunc('c');
	return 0;
}
#endif
#if 0
//c语言函数名字修饰规则：编译器只是在函数名字前增加_
int Add(int left, int right)
{
	return left + right;
}

int main()
{
	Add(1, 2);//call _Add
	return 0;
}
#endif
#if 0
//在C++工程中
//extern "C"作用：将函数按照C的风格进行编译
extern "C" int Add(int left, int right);
//{
//	return left + right;
//}
int main()
{
	Add(1, 2); //? Add@@YAHHH@Z
	return 0;
}
#endif
#if 0
void Testfunc(int a=10)
{}
void Testfunc()
{}

int main()
{
	Testfunc();
	return 0;
}
#endif
#if 0
//传值
//优点：对函数形参的改变不会影响外部的实参
//缺点：不能通过形参改变外部的实参，浪费空间，减低代码的运行效率
struct SeqList
{
	int array[1000000];
	int _size;
};
void Swap(int left, int right)
{
	int temp = left;
	left = right;
	right = temp;
}

//传地址
//优点：可以通过形参改变外部的实参，传参的效率
//缺点：函数的副作用会影响外部的实参，指针不安全，降低代码的可读性
void Swap(int *left, int *right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}
int main()
{
	int a = 10;
	int b = 20;
	Swap(a, b);
	Swap(&a, &b);
	Swap(NULL, NULL);

	return 0;
}
#endif
#if 0
//引用的概念
int main()
{
	int a = 10;
	//一个实体可以有多个别名
	int& ra1 = a;
	int& ra2 = a;
	int& ra3 = ra2;

	ra1 = 100;
	ra2 = 200;
	ra3 = 200;

	cout << &a << " " << &ra1 << endl;
	//一个引用类型的变量一旦与一个实体结合后，就不能够在与其他实体结合
	int b = 10;
	if (true)
	{
		int& rb = b;
	}
	return 0;
}
#endif
#if 0
//引用作为函数的形参：如果想通过形参改变外部实参----传递普通类型引用
//                    如果不想通过形参改变外部实参---传递const类型引用

void Swap(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}
void Testfunc(const int& ra)
{}

int main()
{
	int a = 10; 
	int b = 20;
	Swap(a, b);
	cout << a << " " << b << endl;
	Testfunc(a);
	return 0;
}
#endif
