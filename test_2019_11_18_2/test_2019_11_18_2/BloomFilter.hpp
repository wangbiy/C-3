#include <iostream>
#include <bitset>
#include "common.h"
namespace Daisy
{
	template < size_t N, class k=string,
						 class HF1 = STRTOINT1<k>, 
						 class HF2 = STRTOINT2<k>,
						 class HF3 = STRTOINT3<k>,
						 class HF4 = STRTOINT4<k>,
						 class HF5 = STRTOINT5<k>>
	
	class BloomFilter
	{
	public:
		BloomFilter(size_t size)
			:_size(size)
		{}
		void Insert(const k& data)
		{
			size_t index1 = HF1()(data) % N;
			size_t index2 = HF2()(data) % N;
			size_t index3 = HF3()(data) % N;
			size_t index4 = HF4()(data) % N;
			size_t index5 = HF5()(data) % N;
			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
			_bs.set(index4);
			_bs.set(index5);
			++_size;
		}
		bool IsIn(const k& data)
		{
			size_t index = HF1()(data)%N;
			if (_bs.test(index))//如果这个bit位是0，这个数据不在
				return false;
			index = HF2()(data) % N;
			if (_bs.test(index))//如果这个bit位是0，这个数据不在
				return false;
			index = HF3()(data) % N;
			if (_bs.test(index))//如果这个bit位是0，这个数据不在
				return false;
			index = HF4()(data) % N;
			if (_bs.test(index))//如果这个bit位是0，这个数据不在
				return false;
			index = HF5()(data) % N;
			if (_bs.test(index))//如果这个bit位是0，这个数据不在
				return false;
			return true;//可能在
		}
	private:
		bitset<N> _bs;
		size_t _size;
	};
}
void TestBloomFilter1()
{
	Daisy::BloomFilter<100>bf(30);
	string s1("hhh");
	bf.Insert(s1);
	bf.Insert("zhangsan");
	bf.Insert("lisi");
	bf.Insert("wangwu");
	bf.Insert("zhaoliu");
	if (bf.IsIn("hh"))
		cout << "hh is in bf" << endl;
	else
		cout << "hh is not in bf" << endl;
	if (bf.IsIn("hhh"))
		cout << "hhh is in bf" << endl;
	else
		cout << "hhh is not in bf" << endl;
	if (bf.IsIn("wangwu"))
		cout << "wangwu is in bf" << endl;
	else
		cout << "wangwu is not in bf" << endl;

}
