#include "miniheap.h"

int Minheap::extract_min()
{
    int root=heap[0];
    heap[0]=heap[heap.size()-1];
    heap.resize(heap.size()-1);
    Minheapify(0);
return root;
}    
int Minheap::insert(int n,int dis)
{
    int i;
    if(key[n]==-1)
    {
        key[n]=dis;
        heap.push_back(n);
        i=heap.size()-1;
    }
    else if(key[n]>dis)
    {
        key[n]=dis;
        for(unsigned j=0;j<heap.size();j++)
        {
            if(heap[j]==n)
            {
                i=j;
                break;
            }
        }
    }
    else
    {
        return 0;
    }
    while(i!=0&&key[heap[i]]<key[heap[parent(i)]])
    {
        int temp=heap[i];
        heap[i]=heap[parent(i)];
        heap[parent(i)]=temp;
        i=parent(i);
    }
return 0;
}
int Minheap::Minheapify(int i)
{
    int l=2*i+1;
    int r=2*i+2;
    int min;
    if(l<heap.size()&&key[heap[i]]>key[heap[l]])
        min=l;
    else
        min=i;
    if(r<heap.size()&&key[heap[r]]<key[heap[min]])
        min=r;
    if(min!=i)
    {
        int temp=heap[i];
        heap[i]=heap[min];
        heap[min]=temp;
        Minheapify(min);
    }
return 0;
}
