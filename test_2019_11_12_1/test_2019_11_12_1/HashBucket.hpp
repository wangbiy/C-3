#pragma once
#include "common.h"
#include <iostream>
using namespace std;
#include <vector>
template <class T>
//默认哈希表中的元素是唯一的
struct HBNode
{
	T _data;
	HBNode<T>* _pNext;
	HBNode(const T& data)
		:_data(data)
		, _pNext(nullptr)
	{}
};
//T--->整形系列
template <class T>
class DFDef//实现仿函数
{
public:
	T operator()(const T& data)
	{
		return data;
	}
};
//T--->string
#include <string>
class StringToINT
{
public:
	size_t operator()(const string& s)
	{
		return (size_t)(s.c_str());//直接返回地址
	}
};
template <class T，class HF = DFDef<int>>//按照默认为整数的方式来处理
class HashBucket
{
public:
	HashBucket(size_t capacity=10)
		:_table(GetNextPrime(capacity), nullptr)
		, _size(0)
	{}
	~HashBucket()
	{
		clear();
	}
	bool Insert(const T& data)
	{
		CheckCapacity();
		size_t bucketNo = HashFunc(data);//计算桶号,即第一个结点
		//检测该元素是否在桶中
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return false;
			pCur = pCur->_pNext;
		}
		//插入元素
		pCur = new HBNode<T>(data);
		//头插,性能比较高
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		return true;
	}
	HBNode<T>* Find(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return pCur;
			pCur = pCur->_pNext;
		}
		return nullptr;
	}
	bool Erase(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		HBNode<T>* pCur = _table[bucketNo];
		HBNode<T>* pPre = nullptr;
		while (pCur)
		{
			if (pCur->_data == data)//找到了这个桶
			{
				if (pCur == _table[bucketNo])//找到了
				{
					_table[bucketNo] = pCur->_pNext;//删除的是第一个结点,也就是头删
				}
				else//删除的不是第一个结点,就是任意位置删除
				{
					pPre->_pNext = pCur->_pNext;
				}
				delete pCur;
				--_size;
				return true;
			}
			pPre = pCur;
			pCur = pCur->_pNext;
		}
		return false;
	}
	size_t Size()const
	{
		return _size;
	}
	void Swap(HashBucket<T>& hb)
	{
		_table.swap(hb._table);
		swap(_size, hb._size);
	}
	void clear()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			HBNode<T>* pCur = _table[bucketNo];
			while (pCur)
			{
				//头删
				_table[bucketNo] = pCur->_pNext;
				delete pCur;
				pCur = _table[bucketNo];
			}
		}
		_size = 0;
	}
	void Print()
	{
		for (size_t i = 0; i < _table.capacity(); ++i)
		{
			cout << "H[" << i << "]" << ":";
			HBNode<T>* pCur = _table[i];
			while (pCur)
			{
				cout << pCur->_data << "----->";
				pCur = pCur->_pNext;
			}
			cout << "NULL" << endl;
		}
	}
private:
	//哈希函数
	size_t HashFunc(const T& data)
	{
		return HF()(data) % _table.capacity();//仿函数的方式
	}
	void CheckCapacity()
	{
		size_t oldCapacity = _table.capacity();
		if (_size == oldCapacity)
		{
			HashBucket<T> newHB(GetNextPrime(oldCapacity));
			for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
			{
				HBNode<T>* pCur = _table[bucketNo];
				////但是这种方式不太好，效率比较低，因为又重新创建了结点
				//while (pCur)
				//{
				//	newHB.Insert(pCur->_data);
				//	pCur = pCur->_pNext;
				//}
				while (pCur)
				{
					//1、计算当前结点在新哈希桶中的新桶号
					size_t newbucketNo = newHB.HashFunc(pCur->_data);
					//2、将结点从哈希表的哈希桶中拆下来
					_table[bucketNo] = pCur->_pNext;//将pCur拿出来
					//头插
					pCur->_pNext = newHB._table[newbucketNo];
					newHB._table[newbucketNo] = pCur;
					pCur = _table[bucketNo];//让pCur到原哈希桶的下一个节点
				}
			}
			Swap(newHB);
		}
	}
private:
	vector<HBNode<T>*> _table;//哈希表
	size_t _size;
};
void TestHashBucket1()
{
	HashBucket<int> ht(10);
	ht.Insert(3);
	ht.Insert(8);
	ht.Insert(4);
	ht.Insert(0);
	ht.Insert(7);
	ht.Insert(13);
	ht.Insert(33);
	cout << ht.Size() << endl;
	ht.Print();

	ht.Erase(13);
	ht.Print();

	ht.Erase(3);
	if (nullptr == ht.Find(3))
		cout << "3 is not in" << endl;
	else
		cout << "3 is in" << endl;
	ht.clear();
	cout << ht.Size() << endl;
}
void TestBucket2()
{
	HashBucket<string, StringToINT> ht;
	ht.Insert("hello");
	ht.Insert("CCP");
	ht.Insert("I");
	ht.Insert("Love");
	ht.Insert("You");
}