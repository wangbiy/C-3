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
//C++ÀàÐÍ×ª»»
#include <iostream>
using namespace std;
int main()
{
	double d = 12.34;
	int a = static_cast<int>(d);
	cout << a << endl;
	const int c = 2;
	int* p = const_cast<int*>(&c);
	double d = 1.34;
	int* ptr = reinterpret_cast<int*>(&d);
	return 0;
}