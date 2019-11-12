#pragma once
#include <iostream>
using namespace std;
#include <vector>
//假设哈希表格中的元素是唯一的
enum State
{
	EMPTY, EXIST, DELETE
};
template<class T>
struct Elem
{
	T _value;//元素值域
	State _state;//状态
};
template<class T>
class HashTable
{
public:
	HashTable(size_t capacity = 10)
		:_ht(capacity)
		, _size(0)
	{
		for (auto& e : _ht)
		{
			e._state = EMPTY;//将表格的初始状态初始化为空
		}
	}
	bool Insert(const T& val)
	{
		//检测是否需要扩容
		CheckCapacity();

		//通过哈希函数计算元素在哈希表中的存储位置
		size_t HashAddr = HashFunc(val);
		//检测该位置是否可以插入元素
		//发生哈希冲突，使用二次探测来解决
		while (_ht[HashAddr]._state != EMPTY)
		{
			if (EXIST == _ht[HashAddr]._state && val == _ht[HashAddr]._value)
			{
				//就不用插入了，冲突
				return false;
			}
		  //使用线性探测
			++HashAddr;
			if (HashAddr == _ht.capacity())
				HashAddr = 0;//如果找到最后一个还没有找到空位，从头开始
		}
		//肯定不会让哈希表中的元素放的太多，因为发生冲突的概率会提高，这样哈希表查找的效率就会降低
		//所以不用考虑造成死循环的情况
		//找到空的位置,进行插入
		_ht[HashAddr]._value = val;
		_ht[HashAddr]._state = EXIST;
		++_size;
		return true;
	}
	int Find(const T& val)
	{
		size_t HashAddr = HashFunc(val);//计算哈希地址
		while (_ht[HashAddr]._state != EMPTY)//这个位置可能有元素
		{
			if (_ht[HashAddr]._state == EXIST && _ht[HashAddr]._value == val)
			{
				return HashAddr;
			}
			//使用线性探测
			++HashAddr;
			if (HashAddr == _ht.capacity())
				HashAddr = 0;//如果找到最后一个还没有找到空位，从头开始
		}
		return -1;//没有这个元素
	}
	bool Erase(const T& val)
	{
		int index = Find(val);//在哈希表中找这个元素的位置
		if (index != -1)//找到了
		{
			_ht[index]._state = DELETE;
			_size--;
			return true;
		}
		return false;
	}
	void Swap(HashTable<T>& ht)
	{
		_ht.swap(ht._ht);//先交换内容
		swap(_size, ht._size);
	}
private:
	size_t HashFunc(const T& val)
	{
		return val%_ht.capacity();
	}
	void CheckCapacity()
	{
		//有效元素与容量的比率称为负载因子，因为_size/_ht.capacity()永远是0，因为都是整形，所以给_size乘10/容量>7即可
		if (_size * 10 / _ht.capacity() >= 7)//需要扩容
		{
			//无法使用原来的哪种方法扩容，因为现在哈希函数是val%容量,扩容使容量发生改变，哈希函数也就会变化，
			//如果采用原来的方法将元素进行搬移，可能导致元素找不到了，因此要重新找一种方法来扩容
			//涉及两个问题：元素怎么搬移和搬移哪些元素（只搬移状态为存在的元素）
			//（1）构造新的哈希表，将容量给为新容量（这里是原容量的2倍）
			HashTable<T> newHT(_ht.capacity() * 2);
			//（2）将原哈希表中状态为存在的元素插入到新的哈希表中
			for (size_t i = 0; i < _ht.capacity(); ++i)
			{
				if (_ht[i]._state == EXIST)
					newHT.Insert(_ht[i]._value);
			}
			//（3）交换两个哈希表
			Swap(newHT);
		}
	}
private:
	std::vector<Elem<T>> _ht;
	size_t _size;//哈希表中有效元素个数
};
void TesthashTable()
{
	HashTable<int> ht;
	ht.Insert(4);
	ht.Insert(7);
	ht.Insert(8);
	ht.Insert(27);
	ht.Insert(9);
	ht.Insert(5);
	ht.Insert(3);
	ht.Insert(1);

	ht.Erase(2);
	ht.Erase(8);
}
