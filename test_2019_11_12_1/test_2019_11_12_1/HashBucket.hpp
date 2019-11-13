#pragma once
#include "common.h"
#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <assert.h>
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
size_t BKDRHash(const char* str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * 131 + ch;
	}
	return hash;
}
class StringToINT
{
public:
	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());//ֱ�ӷ��ص�ַ
	}
};
//ʵ�ֵ������Ĳ���
template <class T,class K,class KeyOfValue,class HF=DFDef<int>>//ͨ��KeyOfValueʵ��ͨ��key����ȡvalue
class HashBucket;
template <class T,class K,class KeyOfValue,class HF>//ͨ��KeyOfValueʵ��ͨ��key����ȡvalue
struct HBIterator
{
	typedef HBNode<T> Node;
	typedef HBIterator<T,K,KeyOfValue,HF> Self;
public:
	HBIterator(Node* pNode,HashBucket<T,K,KeyOfValue,HF>* ht)//���캯��
		:_pNode(pNode)
		, _ht(ht)
	{}
	T& operator*()
	{
		return _pNode->_data;
	}
	T* operator->()
	{
		return &(operator*());
	}
	//�������ƶ�������--����Ϊ��ϣͰ�Ľṹ�ǵ�����
	//�������ڵ�Ͱ����һ��Ͱ�����������ɺ��ٱ�����һ��Ͱ������
	Self& operator++()//ǰ��++
	{
		Next();
		return *this;
	}
	Self& operator++(int)
	{
		Self tmp(*this);
		Next();
		return tmp;
	}
	void Next()
	{
		if (_pNode->_pNext)//��Ϊ�գ���ǰ����û�д������
		{
			_pNode = _pNode->_pNext;
		}
		else//����һ�����ڵ�Ͱ
		{
			size_t bucketNo = _ht->HashFunc(KeyOfValue()(_pNode->_data)) + 1;//��ϣ�����ǹ�ϣͰ���˽�г�Ա��������Ҫʹ����Ԫ��
			for (; bucketNo < _ht->BucketCount(); ++bucketNo)
			{
				if (_ht->_table[bucketNo])
				{
					_pNode = _ht->_table[bucketNo];
					return;
				}
			}
			_pNode = nullptr;
		}
	}
	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode && _ht == s._ht;//ͬһ����ϣͰ�Ĳ�ͬ���
	}
	bool operator==(const Self& s)const
	{
		return !(*this != s);
	}

private:
	Node* _pNode;
	HashBucket<T, K,KeyOfValue,HF>* _ht;
};
template <class T, class K,class KeyOfValue,class HF>//HF����Ϊ����Ĭ��Ϊ�����ķ�ʽ������ͨ��KeyOfValueʵ��ͨ��key����ȡvalue
class HashBucket
{
	friend HBIterator<T,K,KeyOfValue, HF>;//�ǵ����������Ԫ������������Է��ʹ�ϣͰ���˽�г�Ա
	typedef HashBucket<T, K,KeyOfValue, HF> Self;
public:
	typedef HBIterator<T,K,KeyOfValue,HF> Iterator;//��������ȡ����
public:
	HashBucket(size_t capacity=10)
		:_table(GetNextPrime(capacity), nullptr)
		, _size(0)
	{}
	~HashBucket()
	{
		clear();
	}
	Iterator Begin()
	{
		for (size_t bucketNo = 0; bucketNo < BucketCount(); ++bucketNo)
		{
			if (_table[bucketNo])
				return Iterator(_table[bucketNo],this);
		}
		return End();
	}
	Iterator End()
	{
		return Iterator(nullptr, this);
	}
	pair<Iterator,bool> Insert(const T& data)
	{
		CheckCapacity();
		size_t bucketNo = HashFunc(KeyOfValue()(data));//����Ͱ��,����һ�����
		//����Ԫ���Ƿ���Ͱ��
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				//return false;
				return make_pair(Iterator(pCur,this),false);
			pCur = pCur->_pNext;
		}
		//����Ԫ��
		pCur = new HBNode<T>(data);
		//ͷ��,���ܱȽϸ�
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		//return true;
		return make_pair(Iterator(pCur,this),true);
	}
	Iterator Find(const K& key)
	{
		size_t bucketNo = HashFunc(key);
		HBNode<T>* pCur = _table[bucketNo];
		while (pCur)
		{
			if (KeyOfValue()(pCur->_data) == key)
				return Iterator(pCur,this);
			pCur = pCur->_pNext;
		}
		return End();
	}
	size_t Erase(const K& key)
	{
		size_t bucketNo = HashFunc(key);
		HBNode<T>* pCur = _table[bucketNo];
		HBNode<T>* pPre = nullptr;
		while (pCur)
		{
			if (KeyOfValue()(pCur->_data) == key)//�ҵ������Ͱ
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
				return 1;
			}
			pPre = pCur;
			pCur = pCur->_pNext;
		}
		return 0;
	}
	size_t Size()const
	{
		return _size;
	}
	bool Empty()const
	{
		return 0 == _size;
	}
	size_t BucketCount()
	{
		return _table.capacity();
	}
	size_t BucketSize(size_t bucketNo)const//����Ͱ������ȡ��ǰͰ���м���Ԫ��
	{
		assert(bucketNo < _table.capacity());
		HBNode<T>* pCur = _table[bucketNo];
		size_t count = 0;
		while (pCur)
		{
			count++;
			pCur = pCur->_pNext;
		}
		return count;
	}
	void Swap(HashBucket<T,K,KeyOfValue,HF>& hb)
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
	size_t HashFunc(const K& key)
	{
		//ͨ��KeyOfValueʵ��ͨ��key����ȡvalue
		//HF��ʾ���շº����ķ�ʽ�������������͵�ʵ�֣�������Σ�����Ĭ�ϵģ���������ַ���ת��Ϊ���ε�Ԫ��
		return HF()(key) % _table.capacity();//�º����ķ�ʽ
	}
	void CheckCapacity()
	{
		size_t oldCapacity = _table.capacity();
		if (_size == oldCapacity)
		{
			Self newHB(GetNextPrime(oldCapacity));//��Ϊ������������ϵ
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
					size_t newbucketNo = newHB.HashFunc(KeyOfValue()(pCur->_data));
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
#if 0
//����������������û������KeyOfValue�ķ���ʱ���Ե�
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
	ht.Insert(53);
	cout << ht.Size() << endl;
	auto it = ht.Begin();
	while (it != ht.End())
	{
		cout << *it<<" ";
		++it;
	}
	cout << endl;
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
void TestHashBucket2()
{
	HashBucket<string, StringToINT> ht;
	ht.Insert("hello");
	ht.Insert("CCP");
	ht.Insert("I");
	ht.Insert("Love");
	ht.Insert("You");
	ht.Print();
	cout << ht.Size() << endl;

	ht.Erase("I");
	ht.Print();

	ht.Erase("hello");
	if (nullptr == ht.Find("hello"))
	{
		cout << "hello is not in" << endl;
	}
	else
		cout << "hello is in" << endl;
	cout << ht.Size() << endl;
}
#endif