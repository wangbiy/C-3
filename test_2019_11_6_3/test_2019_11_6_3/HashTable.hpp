#pragma once
#include <iostream>
using namespace std;
#include <vector>
//�����ϣ����е�Ԫ����Ψһ��
enum State
{
	EMPTY, EXIST, DELETE
};
template<class T>
struct Elem
{
	T _value;//Ԫ��ֵ��
	State _state;//״̬
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
			e._state = EMPTY;//�����ĳ�ʼ״̬��ʼ��Ϊ��
		}
	}
	bool Insert(const T& val)
	{
		//����Ƿ���Ҫ����

		//ͨ����ϣ��������Ԫ���ڹ�ϣ���еĴ洢λ��
		size_t HashAddr = HashFunc(val);
		//����λ���Ƿ���Բ���Ԫ��
		//������ϣ��ͻ��ʹ������̽�������
		while (_ht[HashAddr]._state != EMPTY)
		{
			if (EXIST == _ht[HashAddr]._state && val == _ht[HashAddr]._value)
			{
				//�Ͳ��ò����ˣ���ͻ
				return false;
			}
			//ʹ������̽����������ң�ֱ���ҵ���λ
			++HashAddr;
			if (HashAddr == _ht.capacity())
				HashAddr = 0;//����ҵ����һ����û���ҵ���λ����ͷ��ʼ
		}
		//�϶������ù�ϣ���е�Ԫ�طŵ�̫�࣬��Ϊ������ͻ�ĸ��ʻ���ߣ�������ϣ����ҵ�Ч�ʾͻή��
		//���Բ��ÿ��������ѭ�������
		//�ҵ��յ�λ��,���в���
		_ht[HashAddr]._value = val;
		_ht[HashAddr]._state = EXIST;
		++_size;
		return true;
	}
	int Find(const T& val)
	{
		size_t HashAddr = HashFunc(val);//�����ϣ��ַ
		while (_ht[HashAddr]._state != EMPTY)//���λ�ÿ�����Ԫ��
		{
			if (_ht[HashAddr]._state == EXIST && _ht[HashAddr]._value == val)
			{
				return HashAddr;
			}
			//������λ����ɾ�����߲�����Ҫ�ҵ�ֵ���͹�ϣ��ͻ������̽��
			HashAddr++;
			if (HashAddr == _ht.capacity())
				HashAddr = 0;
		}
		return -1;//û�����Ԫ��
	}
	bool Erase(const T& val)
	{
		int index = Find(val);//�ڹ�ϣ���������Ԫ�ص�λ��
		if (index != -1)//�ҵ���
		{
			_ht[index]._state = DELETE;
			_size--;
			return true;
		}
		return false;
	}
private:
	size_t HashFunc(const T& val)
	{
		return val%_ht.capacity();
	}
private:
	std::vector<Elem<T>> _ht;
	size_t _size;//��ϣ������ЧԪ�ظ���
};
void TesthashTable()
{
	HashTable<int> ht;
	ht.Insert(4);
	ht.Insert(7);
	ht.Insert(8);
	ht.Insert(27);

	ht.Erase(2);
	ht.Erase(8);

}
