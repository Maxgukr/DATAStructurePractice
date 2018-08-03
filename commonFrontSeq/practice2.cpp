#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isPair(char c1, char c2)
{
	if (c1 == '('&&c2 == ')' || c1 == '['&&c2 == ']' || c1 == '{'&&c2 == '}')
		return true;
	else
		return false;
}

bool matchBrackets()
{
	stack<char> str;
	string s = "()[]{}";
	for (unsigned int i = 0; i<s.size(); i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			str.push(s[i]);
		else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
		{
			if (str.empty())
				return false;
			else
			{
				if (isPair(str.top(), s[i]))
					str.pop();
				else
					return false;
			}
		}
	}
	if (str.empty())
		return true;
	else
		return false;
}