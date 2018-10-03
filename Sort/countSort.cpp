#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

//template <typename T>


void countingSort(vector<int> &a, vector<int> &b, int k)
{
    vector<int> c(k+1,0);
    for(unsigned j=0;j<a.size();j++){
        c[a[j]]++; // c contains the number of elements equals to i
    }
    for(unsigned i=1;i<c.size();i++){
        c[i] = c[i-1] + c[i];
    }
    for(int j=int(a.size()-1);j>=0;j--){ //用递减的时候前面不能使用无符号整数，0-1会变成最大的数。
        b[c[a[j]]-1] = a[j];
        c[a[j]] = c[a[j]] - 1;
    }
    
    for(unsigned i=0;i<a.size();i++)
    {
        cout<<b[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int array[8]={2,5,3,0,2,3,0,3};
    vector<int> a(array, array+8);
    vector<int> b(a.size(),0);
    vector<int>::iterator max=max_element(a.begin(),a.end());
    countingSort(a,b,*max);
    //cout<<"$$$$"<<endl;
    return 0;
}