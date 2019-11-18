#if 0
#include <bitset>
#include <iostream>
using namespace std;
void TestBitSet()
{
	bitset<100> bs;//一共100个bit位
	int array[] = { 1, 3, 7, 4, 12, 16, 19, 13, 22, 18 };
	for (auto e : array)
		bs.set(e);//将数据映射到位图中
	cout << bs.count() << endl;//计算有多少个数据
	cout << bs.size() << endl;//bit位总个数
	if (bs.test(13))//检验这个元素在不在位图中
		cout << "13 is in bitset" << endl;
	else
		cout << "13 is not in bitset" << endl;
	bs.reset(13);//将这个bit位清0
	if (bs.test(13))
		cout << "13 is in bitset" << endl;
	else
		cout << "13 is not in bitset" << endl;
}
int main()
{
	TestBitSet();

	return 0;
}
#endif
#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
namespace Daisy
{
	template<size_t N>//N代表bit位的个数
	class bitset
	{
	public:
		bitset()
		{
			_bs.resize((N >> 3) + 1);//也就是将bit位个数/8+1就是所需字节数
		}
		//将num的bit位置1
		bitset<N>& set(size_t num)
		{
			assert(num < N);
			//计算num在哪一个字节中
			size_t index = num>>3;//也就是/8
			size_t pos = num % 8;//计算bit位
			_bs[index] |= (1 << pos);
			return*this;
		}
		//将num的bit位置0
		bitset<N>& reset(size_t num)
		{
			assert(num < N);
			size_t index = num >> 3;
			size_t pos = num % 8;
			_bs[index] &= ~(1 << pos);//置0就是将1向左移动pos个bit位，然后取反，就只有pos这个位置逻辑与的是0，就置成了0
			return *this;
		}
		bool test(size_t num)const
		{
			assert(num < N);
			//计算num在哪一个字节中
			size_t index = num >> 3;//也就是/8
			size_t pos = num % 8;//计算bit位
			return 0!=(_bs[index] & (1 << pos));
		}
		size_t size()const
		{
			return N;
		}
		size_t count()const//总共有多少个bit位是1
		{
			int bitCnttable[256] = {
				0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
				3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
				3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
				4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
				3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
				6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
				4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
				6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
				3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
				4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
				6, 7, 6, 7, 7, 8 };//对应的是形如1,2,3,4,5的对应bit位有几个
			size_t szcount = 0;
			for (auto e : _bs)
			{
				szcount += bitCnttable[e];
			}
			return szcount;
		}
	private:
		vector<unsigned char> _bs;//我们使用的是unsigned char是一个字节一个字节的，使用unsigned是为了防止负数的出现，也就是8个bit，如果是整形，就是32个bit了
	};
}
void TestBitSet()
{
	Daisy::bitset<100> bs;//一共100个bit位
	int array[] = { 1, 3, 7, 4, 12, 16, 19, 13, 22, 18 };
	for (auto e : array)
		bs.set(e);//将数据映射到位图中
	cout << bs.count() << endl;//计算有多少个数据
	cout << bs.size() << endl;//bit位总个数
	if (bs.test(13))//检验这个元素在不在位图中
		cout << "13 is in bitset" << endl;
	else
		cout << "13 is not in bitset" << endl;
	bs.reset(13);//将这个bit位清0
	if (bs.test(13))
		cout << "13 is in bitset" << endl;
	else
		cout << "13 is not in bitset" << endl;
}
int main()
{
	TestBitSet();
	return 0;
}