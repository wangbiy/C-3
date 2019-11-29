#include <string>
#include <iostream>
using namespace std;
int main()
{
	//这个代码可以编译通过，因为c_str()函数返回一个const char*指针，
	//指向一个以空字符结束的字符数组，
	//但是这个数组的数据不能保证一直有效，
	//在改变这个数据的成员函数被调用之后，
	//这个数组的数据就失效了，因此发生了改变；
	//解决的办法就是现用现转换或者把它的数据拷贝到用户自己管理的内存中即可
	string s = "abcde";
	const char* str = s.c_str();
	cout << str << endl;
	s[0] = 'A';
	cout << str << endl;
	return 0;

}