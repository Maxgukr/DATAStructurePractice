#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int conSeq()
{
	string str1[3] = { "flower", "flow", "flight" };
	// cout<<str1[0][0:3]<<endl;
	
	vector<int> index;
	vector<string> str(str1, str1 + sizeof(str1) / sizeof(str1[0]));
	//if (str.empty())
		//return "";    //记得检查非空，养成好习惯。！！！
	for (unsigned int i = 0; i<str.size(); i++)
	{
		index.push_back(str[i].size());
	}
	vector<int>::const_iterator index_min = min_element(index.begin(), index.end());
	int min_index = index_min - index.begin();
	string str_min = str[min_index];
	int counter = -1;
	unsigned int cnt = 0;
	vector<string>::iterator it = str.begin();
	for (unsigned int j = 0; j<str_min.size(); j++)
	{
		for (; it != str.end(); it++)
		{
			if (str_min[j] == (*it)[j])
				cnt++;
		}
		it = str.begin();
		if (cnt == str.size())
		{
			counter = j;
			cnt = 0;
		}
		else
		    break;
	}
	/*
	if(counter==-1)
	return "";
	else
	return str_min[0:counter];
	*/
	cout << str_min.substr(0, counter + 1) << endl;
	system("pause");
	return counter;
}
