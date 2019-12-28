#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#if 0
int main()
{
	const int& cra = 10;//����,10��һ����������ֵ
	int a = 10;
	int& ra = a;
	const int& cra = a;//a��һ������
	//const���͵�������һ���������ã�����������ֵ��Ҳ����������ֵ
	return 0;
}
#endif
#if 0
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
	cout << &a << endl;//��ֵ
	int&& rra = 10;//10����ֵ
	const int c = 20;
	//cout << &c << endl;
	//const int&& rrc = c;//���󣬲��ܽ�����ֵ���ã�c������ֵ
	int b1 = 1, b2 = 2;
	//b1 + b2 = 10;//����ʧ��
	//&(b1 + b2);//���У�������һ����ֵ
	int&& rrb = b1 + b2;
	++b1=20;//++b1������ʽ�����һ����ֵ
	//Test() = 10;//����
	//&(Test());//����
	int&& rra = Test();//Test()�ķ���ֵ�����һ����ֵ
	return 0;
}
#endif
#if 0
int& Test(int& a)
{
	a = 10;
	return a;
}
int main()
{
	int b = 0;
	Test(b) = 100;//�����ķ��ؽ����һ����ֵ��������ʽ������
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
		cout << "~Test()" << this << endl;
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
	int&& rb = move(b);//move�����ǽ���ֵתΪ��ֵ
	return 0;
}
#endif
#include <string.h>
#include <stdlib.h>
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
		:_str(new char[strlen(s._str)+1])
	{
		strcpy(_str, s._str);
	}
	//�ƶ�����
	String(String&& s)
		:_str(s._str)//��s�е���Դת�Ƹ���ǰ����
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
	//�ƶ���ֵ
	String& operator=(String&& s)
	{
		if (this != &s)
		{
			delete[]_str;
			_str = s._str;
			s._str = nullptr;
		}
		return *this;
	}
	~String()
	{
		if (_str)
		{
			delete[]_str;
			_str = nullptr;
		}
	}
	String operator+(const String& s)
	{
		char* str = new char[strlen(_str) + strlen(s._str) + 1];//��ǰ����Ĵ�С��Ҫ�ӵĶ���Ĵ�С+1
		strcpy(str, _str);//����ǰ��������ݿ����¿��ٵĿռ�
		strcat(str, s._str);//��Ҫ�ӵĶ��������ƴ�ӵ��¿ռ�
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
	TestString();
	String s1("hello");
	String s2(move(s1));//move������,�������ƶ�����������s2��s1�Ŀռ�������ˣ�Ȼ�����޸�s1�����ݣ��ͷ����˴���
	s1[0] = 'H';
	return 0;
}
#endif
#if 0
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
	return p;//������ʱ��������p��Ӧ�õ����ƶ����죬p�ǽ���ֵ�����Ǵ�ʱ��������p�е�name sex age�����ǽ���ֵ��Ҳ������ֵ�����Ӧ�ý���ͨ��move�ĳ���ֵ
}
int main()
{
	Person p(GetTempPerson());
	return 0;
}
#endif
#if 0
void Fun(int &x)//��ֵ����
{ 
	cout << "lvalue ref" << endl; 
}
void Fun(int &&x)//��ֵ����
{ 
	cout << "rvalue ref" << endl;
}
void Fun(const int &x)//const���͵���ֵ����
{ 
	cout << "const lvalue ref" << endl; 
}
void Fun(const int &&x)//const���͵���ֵ����
{ 
	cout << "const rvalue ref" << endl; 
}
template<class T>
void PerfectForward(T &&t)
{ 
	Fun(t); 
}
int main()
{
	PerfectForward(10);//Ӧ�õ�����ֵ���� 

	int a;
	PerfectForward(a); //Ӧ�õ�����ֵ����
	PerfectForward(std::move(a)); //Ӧ�õ�����ֵ����

	const int b = 8;
	PerfectForward(b);//Ӧ�õ���const���͵���ֵ���� 
	PerfectForward(std::move(b)); //Ӧ�õ���const���͵���ֵ����

	return 0;
}
#endif
#if 0
void Fun(int &x)//��ֵ����
{
	cout << "lvalue ref" << endl;
}
void Fun(int &&x)//��ֵ����
{
	cout << "rvalue ref" << endl;
}
void Fun(const int &x)//const���͵���ֵ����
{
	cout << "const lvalue ref" << endl;
}
void Fun(const int &&x)//const���͵���ֵ����
{
	cout << "const rvalue ref" << endl;
}
template<class T>
void PerfectForward(T &&t)
{
	Fun(forward<T>(t));
}
int main()
{
	PerfectForward(10);//Ӧ�õ�����ֵ���� 

	int a;
	PerfectForward(a); //Ӧ�õ�����ֵ����
	PerfectForward(std::move(a)); //Ӧ�õ�����ֵ����

	const int b = 8;
	PerfectForward(b);//Ӧ�õ���const���͵���ֵ���� 
	PerfectForward(std::move(b)); //Ӧ�õ���const���͵���ֵ����

	return 0;
}
#endif
#include <thread>
#if 0
void threadFunc(int a)
{
	cout << "thread1:" << a << endl;
}
class TF
{
	void operator()()
	{
		cout << "thread2" << endl;
	}
};
int main()
{
	thread t1(threadFunc, 10);//�̺߳���Ϊ����ָ��
	TF t;
	thread t2(t);//�̺߳���Ϊ��������
	thread t3([]{
		cout << "thread3" << endl;
	});//�̺߳���Ϊlambda���ʽ
	t1.join();
	t2.join();
	t3.join();
	cout << "Main thread end!" << endl;
	return 0;
}
#endif
#if 0
void ThreadFunc1(int& x) 
{ 
	x += 10;
}
void ThreadFunc2(int* x) 
{ 
	*x += 10; 
}
int main() 
{ 
	int a = 10; 
	//���̺߳����ж�a�޸ģ�����Ӱ���ⲿʵ�Σ���Ϊ�̺߳���������Ȼ�����÷�ʽ������ʵ�����õ����߳�ջ�еĿ��� 
	thread t1(ThreadFunc1, a);
	t1.join(); 
	cout << a << endl; 
	//�����Ҫͨ���βθı��ⲿʵ��ʱ���������std::ref()���� 
	thread t2(ThreadFunc1, std::ref(a));
	t2.join(); 
	cout << a << endl; // ��ַ�Ŀ��� 
	thread t3(ThreadFunc2, &a); 
	t3.join(); 
	cout << a << endl; 
	return 0; 
}
#endif
#if 0
void ThreadFunc() 
{ 
	cout << "ThreadFunc()" << endl; 
} 
bool DoSomething() 
{ 
	return false; 
} 
int main() 
{ 
	thread t(ThreadFunc); 
	if (!DoSomething()) 
		return -1; 
	t.join(); 
	return 0; 
}
#endif
#if 0
void ThreadFunc() 
{ 
	cout << "ThreadFunc()" << endl; 
} 
void Test1() 
{ 
	throw 1; 
} 
void Test2() 
{ 
	int* p = new int[10]; 
	std::thread t(ThreadFunc); 
	try 
	{ 
		Test1(); 
	} 
	catch (...) 
	{ 
		delete[] p; 
		throw; 
	}
	t.join(); 
}
#endif
#if 0
unsigned long sum = 0L;
void func(size_t num)
{
	for (int i = 0; i < num; ++i)
	{
		sum++;
	}
}
int main()
{
	cout << "Before" << sum << endl;
	thread t1(func, 10000000);
	thread t2(func, 10000000);
	t1.join();
	t2.join();
	cout << "After" << sum << endl;
	return 0;
}
#endif
#if 0
#include <atomic>
atomic_long sum{ 0L };
void func(size_t num)
{
	for (int i = 0; i < num; ++i)
	{
		sum++;
	}
}
int main()
{
	cout << "Before" << sum << endl;
	thread t1(func, 10000000);
	thread t2(func, 10000000);
	t1.join();
	t2.join();
	cout << "After" << sum << endl;
	return 0;
}
#endif 
#if 0
#include <atomic>
struct Date
{};
int main()
{
	atomic<Date> t;
}
#endif
#include <mutex>
mutex m;
int number = 0;
int func1()
{
	for (int i = 0; i < 100; ++i)
	{
		m.lock();
		number++;
		cout << "number:" << number << endl;
		m.unlock();
	}
	return 0;
}
int func2()
{
	for (int i = 0; i < 100; ++i)
	{
		m.lock();
		number--;
		cout << "number:" << number << endl;
		m.unlock();
	}
	return 0;
}
int main()
{
	thread t1(func1);
	thread t2(func2);
	t1.join();
	t2.join();
	cout << number << endl;
	return 0;
}
  