#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#if 0
int main()
{
	const int& cra = 10;//可以,10是一个常量，右值
	int a = 10;
	int& ra = a;
	const int& cra = a;//a是一个变量
	//const类型的引用是一个万能引用，可以引用左值，也可以引用右值
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
	cout << &a << endl;//左值
	int&& rra = 10;//10是右值
	const int c = 20;
	//cout << &c << endl;
	//const int&& rrc = c;//错误，不能进行右值引用，c不是右值
	int b1 = 1, b2 = 2;
	//b1 + b2 = 10;//编译失败
	//&(b1 + b2);//不行，可能是一个右值
	int&& rrb = b1 + b2;
	++b1=20;//++b1这个表达式结果是一个左值
	//Test() = 10;//不行
	//&(Test());//不行
	int&& rra = Test();//Test()的返回值结果是一个右值
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
	Test(b) = 100;//函数的返回结果是一个左值，返回形式是引用
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
	int&& rb = move(b);//move作用是将左值转为右值
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
	//移动构造
	String(String&& s)
		:_str(s._str)//将s中的资源转移给当前对象
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
	//移动赋值
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
		char* str = new char[strlen(_str) + strlen(s._str) + 1];//当前对象的大小和要加的对象的大小+1
		strcpy(str, _str);//将当前对象的内容拷到新开辟的空间
		strcat(str, s._str);//将要加的对象的内容拼接到新空间
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
	String s2(move(s1));//move的误用,调用了移动构造来构造s2，s1的空间就销毁了，然后再修改s1的内容，就发生了错误
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
	return p;//构造临时对象，销毁p，应该调用移动构造，p是将亡值，但是此时编译器将p中的name sex age都不是将亡值，也就是左值，因此应该将其通过move改成右值
}
int main()
{
	Person p(GetTempPerson());
	return 0;
}