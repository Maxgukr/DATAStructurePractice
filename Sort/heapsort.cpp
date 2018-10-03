#include <vector>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <typename myType> //与数据类型无关

class heapsort{
    private:
    vector<myType> heap;
    int hpsz;
    public:
    heapsort(const vector<myType> &array)
        //:heap()
    {
        hpsz = array.size();
        heap.push_back(100);
        heap.insert(heap.end(),array.begin(),array.end());
        for(int i=hpsz/2;i>0;i--)
        {
            max_heapify(i);
        } 
    }
    //void max_heapify(int i); // maintain the property of max heap
    void max_heapify (int i)
    {
        int mp=i,left=2*i,right=(2*i)+1;

        if((left<=hpsz) && (heap[left]>heap[mp])) 
        {
                mp = left;
        }
        if((right<=hpsz) && (heap[right]>heap[mp])) 
        {
                mp = right;
        }
        if(mp!=i) 
        {
                iter_swap(heap.begin() + i, heap.begin() + mp);
                max_heapify(mp);
        }
    }
    
    void heapSort()
    {
        int temp = hpsz;
        for (int i = hpsz; i > 1; i--)  
        {
                iter_swap(heap.begin() + 1, heap.begin() + i);
                hpsz--;
                max_heapify(1);
        }
        hpsz = temp;
    }

    void printHeap()
    {
        for (int i = 1; i <= hpsz; i++) 
        {
            cout<<heap[i]<<" ";
        }
        //printf("\n");
        cout<<endl;
    }
};

int main()
{
    int a[] = {3,4,10,8,15,16,17,12,11,20};
    vector<int> heapin (a, a + sizeof(a) / sizeof(a[0]) ); //C++2003
        //std::vector<int> heapin ({3,4,10,8,15,16,17,12,11,20}); //C++2011
        // std::vector<int> heapin(std::begin(a), std::end(a));    //C++2003
    heapsort<int> test(heapin);
    cout<<"int"<<endl;
    test.printHeap();
    test.heapSort();
    test.printHeap();

    srand((unsigned)time(NULL));
    vector<double> heapin_d;
    for(int i=0;i<10;i++)
    {
        heapin_d.push_back((rand()/double(RAND_MAX))*10);
    }
    cout<<"double"<<endl;
    heapsort<double> test_d(heapin_d);
    test_d.printHeap();
    test_d.heapSort();
    test_d.printHeap();

    return 0;
}