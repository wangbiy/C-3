#pragma once
#include "common.h"
#include <iostream>
using namespace std;
#include <vector>
template <class T>
//Ĭ�Ϲ�ϣ���е�Ԫ����Ψһ��
struct HBNode
{
	T _data;
	HBNode<T>* _pNext;
	HBNode(const T& data)
		:_data(data)
		, _pNext(nullptr)
	{}
};
//T--->����ϵ��
template <class T>
class DFDef//ʵ�ַº���
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
		return (size_t)(s.c_str());//ֱ�ӷ��ص�ַ
	}
};
template <class T��class HF = DFDef<int>>//����Ĭ��Ϊ�����ķ�ʽ������
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
		size_t bucketNo = HashFunc(data);//����Ͱ��,����һ�����
		//����Ԫ���Ƿ���Ͱ��
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return false;
			pCur = pCur->_pNext;
		}
		//����Ԫ��
		pCur = new HBNode<T>(data);
		//ͷ��,���ܱȽϸ�
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
			if (pCur->_data == data)//�ҵ������Ͱ
			{
				if (pCur == _table[bucketNo])//�ҵ���
				{
					_table[bucketNo] = pCur->_pNext;//ɾ�����ǵ�һ�����,Ҳ����ͷɾ
				}
				else//ɾ���Ĳ��ǵ�һ�����,��������λ��ɾ��
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
				//ͷɾ
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
	//��ϣ����
	size_t HashFunc(const T& data)
	{
		return HF()(data) % _table.capacity();//�º����ķ�ʽ
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
				////�������ַ�ʽ��̫�ã�Ч�ʱȽϵͣ���Ϊ�����´����˽��
				//while (pCur)
				//{
				//	newHB.Insert(pCur->_data);
				//	pCur = pCur->_pNext;
				//}
				while (pCur)
				{
					//1�����㵱ǰ������¹�ϣͰ�е���Ͱ��
					size_t newbucketNo = newHB.HashFunc(pCur->_data);
					//2�������ӹ�ϣ��Ĺ�ϣͰ�в�����
					_table[bucketNo] = pCur->_pNext;//��pCur�ó���
					//ͷ��
					pCur->_pNext = newHB._table[newbucketNo];
					newHB._table[newbucketNo] = pCur;
					pCur = _table[bucketNo];//��pCur��ԭ��ϣͰ����һ���ڵ�
				}
			}
			Swap(newHB);
		}
	}
private:
	vector<HBNode<T>*> _table;//��ϣ��
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