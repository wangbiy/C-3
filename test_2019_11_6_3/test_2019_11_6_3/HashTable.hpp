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
		CheckCapacity();

		//ͨ����ϣ��������Ԫ���ڹ�ϣ���еĴ洢λ��
		size_t HashAddr = HashFunc(val);
		//����λ���Ƿ���Բ���Ԫ��
		//������ϣ��ͻ��ʹ�ö���̽�������
		while (_ht[HashAddr]._state != EMPTY)
		{
			if (EXIST == _ht[HashAddr]._state && val == _ht[HashAddr]._value)
			{
				//�Ͳ��ò����ˣ���ͻ
				return false;
			}
		  //ʹ������̽��
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
			//ʹ������̽��
			++HashAddr;
			if (HashAddr == _ht.capacity())
				HashAddr = 0;//����ҵ����һ����û���ҵ���λ����ͷ��ʼ
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
	void Swap(HashTable<T>& ht)
	{
		_ht.swap(ht._ht);//�Ƚ�������
		swap(_size, ht._size);
	}
private:
	size_t HashFunc(const T& val)
	{
		return val%_ht.capacity();
	}
	void CheckCapacity()
	{
		//��ЧԪ���������ı��ʳ�Ϊ�������ӣ���Ϊ_size/_ht.capacity()��Զ��0����Ϊ�������Σ����Ը�_size��10/����>7����
		if (_size * 10 / _ht.capacity() >= 7)//��Ҫ����
		{
			//�޷�ʹ��ԭ�������ַ������ݣ���Ϊ���ڹ�ϣ������val%����,����ʹ���������ı䣬��ϣ����Ҳ�ͻ�仯��
			//�������ԭ���ķ�����Ԫ�ؽ��а��ƣ����ܵ���Ԫ���Ҳ����ˣ����Ҫ������һ�ַ���������
			//�漰�������⣺Ԫ����ô���ƺͰ�����ЩԪ�أ�ֻ����״̬Ϊ���ڵ�Ԫ�أ�
			//��1�������µĹ�ϣ����������Ϊ��������������ԭ������2����
			HashTable<T> newHT(_ht.capacity() * 2);
			//��2����ԭ��ϣ����״̬Ϊ���ڵ�Ԫ�ز��뵽�µĹ�ϣ����
			for (size_t i = 0; i < _ht.capacity(); ++i)
			{
				if (_ht[i]._state == EXIST)
					newHT.Insert(_ht[i]._value);
			}
			//��3������������ϣ��
			Swap(newHT);
		}
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
	ht.Insert(9);
	ht.Insert(5);
	ht.Insert(3);
	ht.Insert(1);

	ht.Erase(2);
	ht.Erase(8);
}
