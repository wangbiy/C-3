#pragma once
#include "HashBucket.hpp"
namespace Daisy
{
	template <class K,class V,class HF=DFDef<K>>
	class unordered_map
	{
		typedef pair<K, V> ValueType;
		struct KeyOfValue
		{
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};
		typedef HashBucket<ValueType, K,KeyOfValue, HF> HB;
		typedef unordered_map<K, V, HF> Self;
	public:
		typename typedef HB::Iterator iterator;//可能会把HB中的Iterator当成静态成员变量，因此用typename关键字
	public:
		unordered_map(size_t n)
			: _hb(n)
		{}
		///////迭代器的begin和end
		iterator begin()
		{
			return _hb.Begin();
		}
		iterator end()
		{
			return _hb.End();
		}
		iterator find(const K& key)
		{
			return _hb.Find(key);
		}
		//////////////////
		V& operator[](const K& key)
		{
			return (*(_hb.Insert(ValueType(key, V())).first)->second);
		}
		pair<iterator, bool> insert(const ValueType data)
		{
			return _hb.Insert(data);
		}

		size_t erase(const K& key)
		{
			return _hb.Erase(key);
		}

		void clear()
		{
			_hb.clear();
		}
		void swap(Self& s)
		{
			_hb.Swap(s._hb);
		}
		size_t bucket_count()const
		{
			return _hb.BucketCount();
		}
		size_t size()const
		{
			return _hb.Size();
		}
		size_t bucket_size(size_t n)const
		{
			return _hb.BucketSize(n);
		}
		bool empty()const
		{
			return _hb.Empty();
		}
	private:
		HB _hb;
	};
}
void Testunordered_map()
{
	Daisy::unordered_map<int, int> m(10);
	int array[] = { 4, 5, 7, 8, 1, 0, 9, 2, 6 ,3 };
	for (auto e : array)
		m.insert(make_pair(e, e));
	cout << m.bucket_size(3) << endl;//看一下3号桶的元素个数
	cout << m.size() << endl;
	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "---->"<<it->second<<" ";
		it++;
	}
	cout << endl;
	for (auto e : m)
	cout << e.first << "----->" << e.second<<" ";
	cout << endl;
	if (m.end() != m.find(3))
		cout << "3 is in unordered_map" << endl;
	else
		cout << "3 is not in unordered_map" << endl;
	m.erase(3);
	if (m.end() != m.find(3))
		cout << "3 is in unordered_map" << endl;
	else
		cout << "3 is not in unordered_map" << endl;
}