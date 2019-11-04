#include "RBTree.hpp"
#include <iostream>
using namespace std;
namespace Daisy
{
	template <class K,class V>
	class map
	{
		typedef pair<K, V> DataType;
		struct KeyofValue//�º���
		{
			const K& operator()(const DataType& val)//val�Ǽ�ֵ��
			{
				return val.first;//��ü�ֵ���е�key
			}
		};
		typedef RBTree<DataType, K, KeyofValue> RBT;//ȡ������
		
	public:
		typename typedef RBT::iterator iterator;//���ڱ��������ܻ��RBT::iterator�������еľ�̬��Ա����������Ҫʹ��typename
		map()
			:_t()
		{}
		//////////////////////////////
		iterator begin()
		{
			return _t.begin();//���غ�����е���ʼλ��
		}
		iterator end()
		{
			return _t.end();
		}
		/////////////////////////////////
		//�������
		size_t size()const
		{
			return _t.Size();
		}
		bool empty()const
		{
			return _t.Empty();
		}
		////////////////////////////
		//access
		V& operator[](const K& key)
		{
			return (*(_t.Insert(pair<K, V>(key, V())).first)).second;
			//���ú�����Ĳ��뷽�������Ĳ�����һ����ֵ�ԣ�Ҳ���ǽ�һ����ֵ�Բ����ˣ�
			//Ȼ���õ����λ�õ�key���൱��ָ�������ָ�룬Ȼ������ã�
			//�õ�����ڵ��ֵ��Ҳ��������ڵ�ļ�ֵ�ԣ�Ȼ��ȡsecond�͵õ���value
		}
		//////////////////////////
		//modify
		pair<iterator, bool> insert(const DataType& val)//val��һ����ֵ��
		{
			return _t.Insert(val);
		}
		void swap(map<K, V>& m)
		{
			 _t.Swap(m._t);
		}
		void clear()
		{
			_t.Clear();
		}
		///////////////////
		iterator find(const K& key)
		{
			return _t.Find(key);
		}
	private:
		RBT _t;
//RBT��RBTree<DataType, K, KeyofValue>��map��value���Ǽ�ֵ�ԣ�������ｫ��ֵ��DataType����value

	};
}
#include <string>
void TestMap()
{
	Daisy::map<string, string> m;
	m.insert(pair<string,string>("banana", "�㽶"));
	m.insert(make_pair("orange", "����"));
	m.insert(make_pair("apple", "ƻ��"));

	cout << m["orange"] << endl;
	cout << m["apple"] << endl;
	cout << m.size() << endl;
	cout << m["watermelon"] << endl;
	m["watermelon"] = "����";

	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "---->" << it->second << endl;
		++it;
	}
	m.clear();
	cout << m.size() << endl;
}
