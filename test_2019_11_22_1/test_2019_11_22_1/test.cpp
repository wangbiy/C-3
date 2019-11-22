#include <iostream>
using namespace std;
#include <vector>
#include <map>
#if 0
int main()
{
	//内置类型列表初始化
	int x1 = { 10 };
	int x2{ 10 };
	int x3 = 1 + 2;
	int x4 = { 1 + 2 };
	int x5{ 1 + 2 };
	//数组
	int arr1[5]{1, 2, 3, 4, 5};
	int arr2[]{1, 2, 3, 4, 5};
	//动态数组，C++98中不支持
	int* arr3 = new int[5]{1, 2, 3, 4, 5};
	//标准容器
	vector<int> v{ 1, 2, 3, 4, 5 };
	map<string, string> m{ { "one", "1" }, { "two", "2" } };
	return 0;
}
#endif
#if 0
class Date
{
public:
	Date(int year,int month,int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d2{ 2019, 11, 22 };
	return 0;
}
#endif
#if 0
#include <initializer_list>
namespace Daisy
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
	public:
		vector()
		{
			_start = _finish = endofstorage;
		}
		vector(const initializer_list<T>& il)
			:_start(new T[il.size()])//开辟空间
		{
			auto it = il.begin();
			_finish = _start;
			while (it != il.end())
			{
				*_finish++ = *it;//放元素
				++it;
			}
		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		iterator _start;
		iterator _finish;
		iterator endofstorage;
	};
}
int main()
{
	Daisy::vector<int> v1;
	Daisy::vector<int> v2{ 1, 2, 3, 4, 5 };
	//范围for是为了用户使用方便
	//但是编译器最终会将范围for转换为迭代器形式，加上迭代器的操作
	for (auto e : v2)
		cout << e << " ";
	cout << endl;
	return 0;
}
#endif
#if 0
#include <string>
int main()
{
	short a = 32670;
	short b = 32670;
	short c = a + b;
	map<string, string> m{ { "apple", "苹果" }, { "banana", "香蕉" } };
	map<string, string>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << " " << it->second;
		++it;
	}
	cout << endl;

	return 0;
}
#endif
#if 0
template < class T1, class T2>
auto Add(const T1& left, const T2& right)//不知道该返回T1还是T2
{
	return left + right;
}
//使用auto报错，因为编译器在编译期间会进行替换，但是此时不知道替换成什么类型
int main()
{
	return 0;
}
#endif
#if 0
//decltype
int main()
{
	short a = 32760;
	short b = 32760;
	decltype(a + b)c;
	cout << typeid(c).name()<< endl;
	return 0;
}
#endif
#if 0
void TestFunc(int)
{}
void(*set_malloc_handler(void(*f)()))()
{
	return nullptr;
}
typedef decltype(set_malloc_handler) SH;
int main()
{
	//没有带参数，推演函数类型
	cout << typeid(SH).name() << endl;
	//带参数，推演函数调用类型
	cout << typeid(decltype(set_malloc_handler(nullptr))).name() << endl;
	return 0;
}
#endif
#if 0
//返回值类型追踪
template <class T1,class T2>
auto Add(const T1& left, const T2& right)->decltype(left + right)
{
	return left + right;
}
int main()
{
	cout << typeid(Add(1, 2.0)).name() << endl;
	return 0;
}
#endif
//默认函数控制
//如果一个类什么都没有定义，编译器自动生成6个默认成员函数
//编译器生成的默认构造函数
//编译器不一定会默认生成构造函数，但是像单独的Date类一定不会生成默认的构造函数，如果编译器需要，自己就会生成
#if 0
class Date
{
public:
	Date() = default;
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d;
	return 0;
}
#endif