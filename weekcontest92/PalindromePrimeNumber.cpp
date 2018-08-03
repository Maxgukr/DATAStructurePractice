#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

bool isPalindrome(int x){
    vector<int> num;
    if(x<0) 
    {
        return false;//负数肯定不是回文数。
    }
    while(x%10!=x){
        num.push_back(x%10);
        x=x/10;
    }
    num.push_back(x);
    for(int i=0;i<num.size();i++)
    {
        if(num[i]!=num[num.size()-1-i])
            return false;
    }
    return true;
    
}

bool isPrime(int n)
{
    
}

int primePalindrome(int N) {
        
}

int main()
{
    if(isPalindrome(121))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    return 0;
}