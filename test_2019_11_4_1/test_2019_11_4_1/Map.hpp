#include "RBTree.hpp"
#include <iostream>
using namespace std;
namespace Daisy
{
	template <class K,class V>
	class map
	{
		typedef pair<K, V> DataType;
		struct KeyofValue//仿函数
		{
			const K& operator()(const DataType& val)//val是键值对
			{
				return val.first;//获得键值对中的key
			}
		};
		typedef RBTree<DataType, K, KeyofValue> RBT;//取个别名
		
	public:
		typename typedef RBT::iterator iterator;//由于编译器可能会把RBT::iterator当做类中的静态成员变量，所以要使用typename
		map()
			:_t()
		{}
		//////////////////////////////
		iterator begin()
		{
			return _t.begin();//返回红黑树中的起始位置
		}
		iterator end()
		{
			return _t.end();
		}
		/////////////////////////////////
		//容量相关
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
			//调用红黑树的插入方法，它的参数是一个键值对，也就是将一个键值对插入了，
			//然后拿到这个位置的key，相当于指向数组的指针，然后解引用，
			//拿到这个节点的值域，也就是这个节点的键值对，然后取second就得到了value
		}
		//////////////////////////
		//modify
		pair<iterator, bool> insert(const DataType& val)//val是一个键值对
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
//RBT是RBTree<DataType, K, KeyofValue>，map中value就是键值对，因此这里将键值对DataType当做value

	};
}
#include <string>
void TestMap()
{
	Daisy::map<string, string> m;
	m.insert(pair<string,string>("banana", "香蕉"));
	m.insert(make_pair("orange", "橘子"));
	m.insert(make_pair("apple", "苹果"));

	cout << m["orange"] << endl;
	cout << m["apple"] << endl;
	cout << m.size() << endl;
	cout << m["watermelon"] << endl;
	m["watermelon"] = "西瓜";

	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "---->" << it->second << endl;
		++it;
	}
	m.clear();
	cout << m.size() << endl;
}
