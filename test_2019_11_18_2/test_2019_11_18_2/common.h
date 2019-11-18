#pragma once
#include <string>
using namespace std;
template <class k>
struct STRTOINT1
{
	size_t operator()(const string& s)
	{
		return SDBMHash(s.c_str());
	}
	size_t SDBMHash(const char*str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}
};
template <class k>
struct STRTOINT2
{
	size_t operator()(const string& s)
	{
		return RSHash(s.c_str());
	}
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};
template <class k>
struct STRTOINT3
{
	size_t operator()(const string& s)
	{
		return APHash(s.c_str());
	}
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};
template <class k>
struct STRTOINT4
{
	size_t operator()(const string& s)
	{
		return JSHash(s.c_str());
	}
	size_t JSHash(const char *str)
	{
		if (!*str)        
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
};
template <class k>
struct STRTOINT5
{
	size_t operator()(const string& s)
	{
		return DEKHash(s.c_str());
	}
	size_t DEKHash(const char* str)
	{
		if (!*str)       
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash = ((hash << 5) ^ (hash >> 27)) ^ ch;
		}
		return hash;
	}
};