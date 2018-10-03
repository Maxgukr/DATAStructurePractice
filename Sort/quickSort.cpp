#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <typename T>
int Partion(vector<T> &a, int p, int r)
{
    T x=a[r];
    int i = p-1;
    for(int j=p;j<r;j++)
    {
        if(a[j]<=x){
            i++;
            iter_swap(a.begin()+i,a.begin()+j);
        }
    }
    iter_swap(a.begin()+i+1, a.begin()+r);

    return i+1;
}

template <typename T>
void quickSort(vector<T> &a, int p, int r)
{
    if(p<r){
        int q=Partion(a, p, r);
        quickSort(a,p,q-1);
        quickSort(a,q+1,r);
    }
}

int main()
{
    vector<double> a;
    srand((unsigned)time(NULL));
    for(int i=0;i<10;i++){
        a.push_back((rand()/double(RAND_MAX))*10);
    }
    quickSort<double>(a,0,int(a.size()-1));
    for(unsigned i=0;i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;

    return 0;
}
