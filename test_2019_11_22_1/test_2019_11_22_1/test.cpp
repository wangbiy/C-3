#include <iostream>
using namespace std;
#include <vector>
#include <map>
#if 0
int main()
{
	//���������б��ʼ��
	int x1 = { 10 };
	int x2{ 10 };
	int x3 = 1 + 2;
	int x4 = { 1 + 2 };
	int x5{ 1 + 2 };
	//����
	int arr1[5]{1, 2, 3, 4, 5};
	int arr2[]{1, 2, 3, 4, 5};
	//��̬���飬C++98�в�֧��
	int* arr3 = new int[5]{1, 2, 3, 4, 5};
	//��׼����
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
			:_start(new T[il.size()])//���ٿռ�
		{
			auto it = il.begin();
			_finish = _start;
			while (it != il.end())
			{
				*_finish++ = *it;//��Ԫ��
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
	//��Χfor��Ϊ���û�ʹ�÷���
	//���Ǳ��������ջὫ��Χforת��Ϊ��������ʽ�����ϵ������Ĳ���
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
	map<string, string> m{ { "apple", "ƻ��" }, { "banana", "�㽶" } };
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
auto Add(const T1& left, const T2& right)//��֪���÷���T1����T2
{
	return left + right;
}
//ʹ��auto������Ϊ�������ڱ����ڼ������滻�����Ǵ�ʱ��֪���滻��ʲô����
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
	//û�д����������ݺ�������
	cout << typeid(SH).name() << endl;
	//�����������ݺ�����������
	cout << typeid(decltype(set_malloc_handler(nullptr))).name() << endl;
	return 0;
}
#endif
#if 0
//����ֵ����׷��
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
//Ĭ�Ϻ�������
//���һ����ʲô��û�ж��壬�������Զ�����6��Ĭ�ϳ�Ա����
//���������ɵ�Ĭ�Ϲ��캯��
//��������һ����Ĭ�����ɹ��캯���������񵥶���Date��һ����������Ĭ�ϵĹ��캯���������������Ҫ���Լ��ͻ�����
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