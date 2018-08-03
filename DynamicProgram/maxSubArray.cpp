#include <vector>
#include <algorithm>

using namespace std;

int sum(vector<int>& a)
{
    int s = 0;
    for(int i =0;i<a.size();i++)
    {
        s+=a[i];
    }
    return s;
}

int maxSubArray(vector<int>& nums)
{
    vector<int>::iterator i,j;
    i = max_element(nums.begin(), nums.end()); // 返回最大值所在位置
    j = max_element(nums.begin(), nums.end()); 
    int s = 0;
    int n = 0;
    while(n<=nums.size())
    {
        
    }

}