#include<iostream>
using namespace std;

#if 0
int a1 = 10;
int a = 20;//��C++�п��Զ��������ͬ���Ƶı���

int main()
{
	int a = 10;
	cout << a << endl;//��ӡ�����Ǿֲ�����a
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

//�����ռ����Ƕ��
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
//ֱ���ڳ�Աǰ�������ռ�����::
int main()
{
	int a = 70;
	printf("%d\n", a);//�����������е�a��70
	printf("%d\n", ::a);//����ȫ�ֱ����е�a��1
	printf("%d\n", N1::a);//����N1�����ռ��е�a��10
	printf("%d\n",N2::N3::a);//����N2�����ռ���Ƕ�׵������ռ���N3��a��50
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

using N1::a;//����ֱ��дa���������鷳��дN1::a;

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

using namespace N1;//����ֱ����N1�����ռ��еı����ͺ���
int main()
{
	printf("%d\n", Add(a,b));
	system("pause");
	return 0;
}
#endif

#if 0
//���һ�������д��ڶ����ͬ���������ռ�ʱ���������Ὣ��ϲ���һ��
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
//ȫȱʡ���������Բ���������Ĭ��ֵ
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
//��ȱʡ���������ֲ�������Ĭ��ֵ  Ҫ��ֻ�ܴ����������
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
	Testfunc();//��������֪��Ӧ�õ����ĸ�����
	return 0;
}
#endif

#if 0
//�������أ���������ͬ����������ͬ���ֵĺ�������������б�ͬ�����������͡����ʹ���
//�뷵��ֵ�����Ƿ���ͬ�޹�
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
	//�������ڱ���׶Σ������ʵ�ε����ͽ������ݣ��������ݵ�ʵ�����͵Ľ��ѡ����ú��ʵĺ���
	Add(1, 2);
	Add(1.0, 2.0);
	return 0;
}
#endif

#if 0
//1
void Testfunc()
{}
//2��1�ǲ���������ͬ
//2
void Testfunc(int a)
{}
//3
void Testfunc(int a,double b)
{}
//3��4��ͬ���������ʹ���
//4
void Testfunc(double a,int b)
{}
//2��5����������
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
//c���Ժ����������ι��򣺱�����ֻ���ں�������ǰ����_
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
//��C++������
//extern "C"���ã�����������C�ķ����б���
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
//��ֵ
//�ŵ㣺�Ժ����βεĸı䲻��Ӱ���ⲿ��ʵ��
//ȱ�㣺����ͨ���βθı��ⲿ��ʵ�Σ��˷ѿռ䣬���ʹ��������Ч��
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

//����ַ
//�ŵ㣺����ͨ���βθı��ⲿ��ʵ�Σ����ε�Ч��
//ȱ�㣺�����ĸ����û�Ӱ���ⲿ��ʵ�Σ�ָ�벻��ȫ�����ʹ���Ŀɶ���
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
//���õĸ���
int main()
{
	int a = 10;
	//һ��ʵ������ж������
	int& ra1 = a;
	int& ra2 = a;
	int& ra3 = ra2;

	ra1 = 100;
	ra2 = 200;
	ra3 = 200;

	cout << &a << " " << &ra1 << endl;
	//һ���������͵ı���һ����һ��ʵ���Ϻ󣬾Ͳ��ܹ���������ʵ����
	int b = 10;
	if (true)
	{
		int& rb = b;
	}
	return 0;
}
#endif
#if 0
//������Ϊ�������βΣ������ͨ���βθı��ⲿʵ��----������ͨ��������
//                    �������ͨ���βθı��ⲿʵ��---����const��������

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
