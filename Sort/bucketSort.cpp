#include <algorithm>
#include <list>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void bucketSort(vector<double> &a)
{
    int n=a.size();
    vector< vector<double> > b(a.size());
    b.clear();

    for(int i=0;i<n;i++){
        b[floor(a.size()*a[i])].push_back(a[i]); // 第i个桶中存放的是半开区间[i/n,(i+1)/n)中的值
    }
    for(int i=0;i<n;i++){
        sort(b[i].begin(),b[i].end()); // 对每个桶中的元素排序。
    }
    //vector<double> res(n);
    for(int i=0;i<n;i++){
        //merge(b[i].begin(),b[i].end(),b[i+1].begin(),b[i+1].end(), res.begin());
        if(!b[i].empty())
        {   
            vector<double>::iterator it=b[i].begin();
            while(it!=b[i].end()){
                //res.push_back(*it);
                cout<<*it<<" ";
                it++;
            }
        }
    }
    cout<<endl;
}

int main()
{
    vector<double> a;
    srand((unsigned)time(NULL));
    for(int i=0;i<20;i++){
        a.push_back(rand()/double(RAND_MAX));
    }

    bucketSort(a);
    return 0;
}