#include <iostream>
using namespace std;
#include <string>
#include <unordered_set>
#include <vector>
//×Ö·û´®·Ö¸ôËã·¨
bool wordBreak(string s, unordered_set<string> &dict) {
	if (s.empty())
		return false;
	if (dict.empty())
		return false;
	vector<bool> F(s.size() + 1);
	F[0] = true;
	for (int i = 1; i <= s.size(); ++i)
	{
		for (int j = 0; j<i; ++j)
		{
			if (F[j])
			{
				if (dict.find(s.substr(j, i - j)) != dict.end())
				{
					F[i] = true;
					break;
				}
			}
		}
	}
	return F[s.size()];
}
int main()
{
	string s = "leetcode";
	unordered_set<string> dict = { "leet", "code" };
	if (wordBreak(s, dict) == true)
		cout << "Õæ" << endl;
	else
		cout << "¼Ù" << endl;
	return 0;
}
	