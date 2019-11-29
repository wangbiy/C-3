#include <iostream>
using namespace std;
#include <algorithm>
#include <functional>
#if 0
int main()
{
	int arr[] = { 8, 7, 9, 0, 5, 6, 3, 1, 2 };
	sort(arr, arr + sizeof(arr) / sizeof(arr[0]));

	sort(arr, arr + sizeof(arr) / sizeof(arr[0]),greater<int>());
	return 0;
}
#endif
#include <string>
struct Goods
{
	string _name;
	double _price;
};
#if 0
bool Compare(const Goods& g1, const Goods& g2)
{
	return g1._price <= g2._price;
}
struct com
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1._price <= g2._price;
	}
};
int main()
{
	Goods gds[] = { { "苹果", 2.2 }, { "香蕉", 1.5 }, { "橘子", 5 } };
	//sort(gds, gds + sizeof(gds) / sizeof(gds[0]), com());//按照价格的升序排列,仿函数
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), Compare);//按照价格的升序排列，函数指针

	return 0;
}
#endif
#if 0
int main()
{
	Goods gds[] = { { "苹果", 2.2 }, { "香蕉", 1.5 }, { "橘子", 5 } };
	sort(gds,gds+sizeof(gds)/sizeof(gds[0]),
		[](const Goods& g1, const Goods& g2)->bool
	{
		return g1._price <= g2._price; 
	});
}
#endif 
#if 0
int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;
	auto Add = [&](const int left, const int right)mutable
	{ 
		cout << &a << endl;
		cout << &b << endl;
		cout << &c << endl;
		c=left + right; 
	};
	Add(1, 2);
	return 0;
}
#endif
#if 0
int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;
	auto Add = [=,&a,&b](const int left, const int right)mutable
	{
		cout << &a << endl;
		cout << &b << endl;
		cout << &c << endl;
		c = left + right;
	};
	Add(1, 2);
	return 0;
}
#endif
#if 0
void(*PF)();//函数指针
int main()
{
	auto f1 = []{cout << "hello world" << endl; };
	auto f2 = []{cout << "hello world" << endl; };
	f1 = f2;//编译报错，找不到operator=()

	auto f3(f2);//允许一个lambda不表达式拷贝一个副本
	f3();
	PF = f2;//可以将lambda表达式赋值给想通过类型的函数指针
	PF();
	return 0;
}
#endif
class Rate
{
public:
	Rate(double rate) : _rate(rate)
	{}
	double operator()(double money, int year)//仿函数类
	{
		return money * _rate * year;
	}
private:
	double _rate;
};
int main()
{
	//创建函数对象
	double rate = 0.49;
	Rate r1(rate);
	//以仿函数方式调用
	r1(10000, 2);
	//lambda表达式
	auto r2 = [=](double money, int year)->double{return money*rate*year;};
	r2(10000, 2);
	return 0;
}