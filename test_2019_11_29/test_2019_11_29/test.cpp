#include <string>
#include <iostream>
using namespace std;
int main()
{
	//���������Ա���ͨ������Ϊc_str()��������һ��const char*ָ�룬
	//ָ��һ���Կ��ַ��������ַ����飬
	//���������������ݲ��ܱ�֤һֱ��Ч��
	//�ڸı�������ݵĳ�Ա����������֮��
	//�����������ݾ�ʧЧ�ˣ���˷����˸ı䣻
	//����İ취����������ת�����߰��������ݿ������û��Լ�������ڴ��м���
	string s = "abcde";
	const char* str = s.c_str();
	cout << str << endl;
	s[0] = 'A';
	cout << str << endl;
	return 0;

}