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
//C++����ת��
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
	int* p = const_cast<int*>(&c);//ɾ��const���ԣ����㸳ֵ
	double d = 1.34;
	int* ptr = reinterpret_cast<int*>(&d);
	FUNC f = reinterpret_cast<FUNC>(DoSomething);//һ�㲻�ᳫ��ô��
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
void fun(Base* pa)//pa����ָ���������Ҳ����ָ�������
{
	pa->func();//ʵ�ֶ�̬
	// dynamic_cast���ȼ���Ƿ���ת���ɹ����ܳɹ���ת���������򷵻�
	Derived* pb1 = static_cast<Derived*>(pa);
	Derived* pb2 = dynamic_cast<Derived*>(pa);

	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;
}
int main()
{
	Base b;
	Derived d;
	//��ֵ���ݹ���
	b = d;
	Base* pb = &d;
	Base& rb = d;
	Derived* pd = dynamic_cast<Derived*>(&b);//��ļ̳���ϵ�б������麯������ʹ������ת��
	fun(&b);//����ȫ
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
	//1���õ��ι��캯������2020����һ����ʱ����
	//2���ù���õ���ʱ�����d1��ֵ
	//3����ֵ��������ʱ���󽫱�����
	//�������ת������ȷ�ģ�������ǵ��ι��캯����������Ǵ���ģ�
	//����ʹ��explicit�ؼ�������ֹ����ת�����캯�����е���ʽת���ķ���
	//d1 = 2020;//����
	return 0;
}