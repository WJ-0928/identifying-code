#include <iostream>
using namespace std;

// new/delete 申请和释放单个元素的空间
// new[]/delete[] 申请和释放一段连续的空间


#if 0
int main()
{
	int array[10];
	// C++：提供的new和delete操作符申请空间
	int* p1 = new int;
	int* p2 = new int(10);
	int* p3 = new int[10];
	int* p4 = new int[10]{1,2,3,4,5,6,7,8,9,0};

	delete p1;
	delete p2;
	delete[] p3;
	delete[] p4;

	return 0;
}
#endif

#if 0
// malloc/free  new/delete new[]/delete[]
// 一定要匹配：否则可能会造成内存泄漏或者代码崩溃
// 对内置类型不会出错

#if 0
void TestNew()
{
	int* p1 = (int*)malloc(sizeof(int));
	delete p1;

	int* p2 = (int*)malloc(sizeof(int));
	delete[] p2;

	int* p3 = new int;
	free(p3);

	int* p4 = new int;
	delete[] p4;

	int* p5 = new int[10];
	free(p5);

	int* p6 = new int[10];
	delete p6;
}


int main()
{
	TestNew();
	_CrtDumpMemoryLeaks();
	return 0;
}
#endif

class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void TestNew()
{
	Test* p1 = (Test*)malloc(sizeof(Test));
	delete p1;

	Test* p2 = (Test*)malloc(sizeof(Test));
	delete[] p2;

	Test* p3 = new Test;
	free(p3);

	Test* p4 = new Test;
	delete[] p4;

	Test* p5 = new Test[10];
	free(p5);

	Test* p6 = new Test[10];
	delete p6;
}

int main()
{
	TestNew();
	return 0;
}
#endif

#if 0
// new 和 delete
class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void TestNew()
{
	// malloc：不会调用构造函数---malloc的不能将其称为对象-->与对象大小的一块内存空间
	Test* p1 = (Test*)malloc(sizeof(Test));


	// new其实会调用构造函数--->new出的结果才是一个真正的对象
	Test* p2 = new Test;

	// free: 在释放空间期间不会调用析构函数
	free(p1);

	// delete:在释放空间期间会调用析构函数将对象中的资源清理掉
	delete p2;

	// new[]: 会申请空间 + 调用N次构造函数
	Test* p3 = new Test[10];

	// delete[]： 会释放空间 + 调用N次析构
	delete[] p3;
}

int main()
{
	TestNew();
	_CrtDumpMemoryLeaks();
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};


int main()
{
	_CrtMemBlockHeader
	Test* p = new Test[10];
	delete[] p;

	return 0;
}
#endif


#if 0
struct ListNode
{
	ListNode* _next;
	ListNode* _prev;
	int _data;

	void* operator new(size_t n)
	{
		void* p = nullptr;
		p = allocator<ListNode>().allocate(1);
		cout << "memory pool allocate" << endl;
		return p;
	}

	void operator delete(void* p)
	{
		allocator<ListNode>().deallocate((ListNode*)p, 1);
		cout << "memory pool deallocate" << endl;
	}
};



class List
{
public:
	List()
	{
		_head = new ListNode;
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		ListNode* cur = _head->_next;
		while (cur != _head)
		{
			ListNode* next = cur->_next;
			delete cur;
			cur = next;
		}
		delete _head;
		_head = nullptr;
	}
private:
	ListNode* _head;
};

int main()
{
	List l;
	return 0;
}
#endif

#if 0
void* operator new(size_t size, char* fileName, char* funcName, size_t lineNo)
{
	cout << fileName << "-" << funcName << "-" << lineNo << "-" << size << endl;
	return malloc(size);
}


#define  new new(__FILE__, __FUNCDNAME__, __LINE__) 
int main()
{
	int* p = new int;
	delete p;

	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void TestFunc()
{
	int* p = new int[10];
	FILE* pf = fopen("1.txt", "rb");
	if (nullptr == pf)
	{
		return;
	}

	// 文件操作
	fclose(pf);
}

int main()
{
	Test* pt = (Test*)malloc(sizeof(Test));
	new(pt) Test(10);

	pt->~Test();
	free(pt);
	//delete pt;
	_CrtDumpMemoryLeaks();
	return 0;
}
#endif

#if 0
int main()
{
	void* p = new char[0xfffffffful];
	cout << "new:" << p << endl;
	return 0;
}
#endif

#if 0
typedef int DataType;

struct SeqList
{
	DataType* _array;
	size_t _capacity;
	size_t _size;
};
#endif

#if 0
// 通用的加法函数：与类型无关
int Add(int left, int right)
{
	return left + right;
}

double Add(double left, double right)
{
	return left + right;
}

char Add(char left, char right)
{
	return left + right;
}



int main()
{
	return 0;
}
#endif

#if 0
// class 或者typename T
// 如果模板参数列表中有多个类型，多个类型之间用逗号隔开
// 每个类型前必须加class或者typename的关键字

// 加法函数模板
template<class T>
T Add(T left, T right)
{
	cout << typeid(T).name() << endl;
	return left + right;
}

// watch: 函数模板不是真正的函数，是编译器生成代码的规则

int main()
{
	// 对函数模板进行实例化
	// 在编译期间，根据实例化参数的实际类型，推演模板函数中T的实际类型，
	// 根据推演的实际类型生成处理具体类型的代码
	Add(1, 2);  // Add<int>
	Add(1.0, 2.0); // Add<double>
	Add('1', '2'); // Add<char>

	return 0;
}
#endif

// template<class T1, class T2>
// T1 Add(const T1& left, const T2& right)
// {
// 	return left + right;
// }

#if 0
class Complex
{
public:
	Complex(double real, double image)
		: _real(real)
		, _image(image)
	{}

// 	Complex operator+(const Complex& c)const
// 	{
// 		Complex ret(_real+c._real, _image+c._image);
// 		return ret;
// 	}

	Complex operator+(const Complex& c)const
	{
		// 无名对象
		return Complex(_real + c._real, _image + c._image);
	}

private:
	double _real;
	double _image;
};

template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}


int main()
{
	// 隐式实例化：没有直接指明T的实际类型，T的类型需要进行参数推演才可以确定
	// 编译器不会对参数推演的结果进行隐式类型转化
	Add(1, 2);  // Add<int>
	Add(1.0, 2.0); // Add<double>
	Add('1', '2'); // Add<char>
	Add(1, (int)2.0);

	// 显式实例化：明确指定T的实际类型， 参数不匹配时，可能会发生隐式类型转化
	Add<int>(1, 2.0);
	//Add<int>(1, "123");

	Complex c1(1.0, 2.0);
	Complex c2(3.0, 4.0);

	Add(c1, c2);
	return 0;
}
#endif


#if 0
int Add(int left, int right)
{
	return left + right;
}

template<class T1, class T2>
T1 Add(T1 left, T2 right)
{
	return left + right;
}

int main()
{
	Add(1, 2);

	// 对函数模板隐式实例化
	//Add<>(1, 2);  // Add<int>
	Add(1, 2.0);
	return 0;
}
#endif

#if 0
#include <assert.h>


template<class T>
class SeqList
{
public:
	SeqList(size_t capacity = 10)
		: _array(new T[capacity])
		, _capacity(capacity)
		, _size(0)
	{}

	SeqList(size_t n, const T& data = T())
		: _array(new T[n])
		, _capacity(n)
		, _size(n)
	{
		for (size_t i = 0; i < _capacity; ++i)
			_array[i] = data;
	}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_array = nullptr;
			_capacity = 0;
			_size = 0;
		}
	}

	void PushBack(const T& data);
	void PopBack();

	size_t Size()const
	{
		return _size;
	}

	size_t Capacity()const
	{
		return _capacity;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	T& operator[](size_t index)
	{
		assert(index < _size);
		return _array[index];
	}

	const T& operator[](size_t index)const
	{
		assert(index < _size);
		return _array[index];
	}

	void PrintSeqList()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}

private:
	T* _array;
	size_t _capacity;
	size_t _size;
};


template<class T>
void SeqList<T>::PushBack(const T& data)
{
	// _CheckCapacity();
	_array[_size++] = data;
}

template<class T>
void SeqList<T>::PopBack()
{
	if (0 == _size)
		return;

	--_size;
}


int main()
{
	SeqList<int> s1;
	s1.PushBack(1);
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);

	s1.PrintSeqList();

	s1[0] = 0;
	s1.PrintSeqList();
	cout << s1.Size() << endl;
	cout << s1.Capacity() << endl;
	cout << s1[3] << endl;

	// 一段连续空间---可以支持随即访问



	SeqList<double> s2;
	s2.PushBack(1.0);
	s2.PushBack(2.0);
	s2.PushBack(3.0);
	s2.PushBack(4.0);


	const SeqList<int> s3(10, 5);
	cout << s3[5] << endl;

	s3[5] = 10;

	return 0;
}
#endif

int main()
{
	return 0;
}
