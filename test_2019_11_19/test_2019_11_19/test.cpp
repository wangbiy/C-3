//static int j;
//void fun1(void){
//	static int i = 0;
//	i++;
//}
//void fun2(void){
//	j = 0;
//	j++;
//}
//int main()
//{
//	for (int k = 0; k<10; k++)
//	{
//		fun1();
//		fun2();
//	}
//	return 0;
//}
//C++类型转换
#include <iostream>
using namespace std;
#if 0
typedef void(*FUNC)();
int DoSomething(int i)
{
	cout << "Do Something" << endl;
}
int main()
{
	double d = 12.34;
	int a = static_cast<int>(d);
	cout << a << endl;
	const int c = 2;
	int* p = const_cast<int*>(&c);//删除const属性，方便赋值
	double d = 1.34;
	int* ptr = reinterpret_cast<int*>(&d);
	FUNC f = reinterpret_cast<FUNC>(DoSomething);//一般不提倡这么做
	f();
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
class Derived :public Base
{
public:
	void funcD()
	{
		cout << "Derived::funcD()" << endl;
	}
protected:
	int _d;
};
void fun(Base* pa)//pa可能指向子类对象，也可能指向父类对象
{
	pa->func();//实现多态
	// dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回
	Derived* pb1 = static_cast<Derived*>(pa);
	Derived* pb2 = dynamic_cast<Derived*>(pa);

	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;
}
int main()
{
	Base b;
	Derived d;
	//赋值兼容规则
	b = d;
	Base* pb = &d;
	Base& rb = d;
	Derived* pd = dynamic_cast<Derived*>(&b);//类的继承体系中必须有虚函数才能使用这种转换
	fun(&b);//不安全
	fun(&d);
}
#endif
class Date
{
public:
	explicit Date(int year)
		:_year(year)
		, _month(1)
		, _day(1)
	{
		cout << "Date::Date(int)" << endl;
	}
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
			return *this;
		}
	}
	~Date()
	{
		cout << "Date::~Date()" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2019);
	//1、用单参构造函数，用2020构造一个临时对象
	//2、用构造好的临时对象给d1赋值
	//3、赋值结束后，临时对象将被销毁
	//因此这种转换是正确的，如果不是单参构造函数，这里就是错误的，
	//可以使用explicit关键字来阻止经过转换构造函数进行的隐式转换的发生
	//d1 = 2020;//错误
	return 0;
}