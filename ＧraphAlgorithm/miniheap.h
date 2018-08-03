#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;
class Minheap{
    public:
    vector<int> heap;
    int *key;
    int intialise(int v)
    {
       key=new int[v+1];
       for(int i=0;i<=v;i++)
       {
           key[i]=-1;
       }
      return 0;
    }
    int Minheapify(int);
    int parent(int i)
    {
        return (i-1)/2;
    }
    int extract_min();
    int insert(int n,int dis);
};
