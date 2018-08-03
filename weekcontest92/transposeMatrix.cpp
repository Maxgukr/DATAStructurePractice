#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> transpose(vector<vector<int>>& A) {
        if (A.size()>=1 && A.size()<=1000 && A[0].size()>=1 && A[0].size()<=1000)
        {
            //# vector<vector<int>>::iterator it=A.begin()
            //# initial transpose matrix
            vector<vector<int>> t(A[0].size(),vector<int>(A.size(), 0));
            for (int i=0;i<A[0].size();i++)
                for(int j=0;j<A.size();j++){
                    t[i][j]=A[j][i];
                }
            return t;                           
        }
         
    }