#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <iostream>
#include <map>
#include "miniheap.h"

#define maxsize 10
using namespace std;
//Graph represent by adj-list


class Graphic
{
    friend class GraphicOperaion;
    private:
    vector<int> vertexs; // 
    vector<int> adj[maxsize];//adjlist
    int weight[maxsize][maxsize];//weight matrix
};

class GraphicOperaion:public Minheap
{
private:
    Graphic* Graph;
public:
    GraphicOperaion()
    {
        Graph = new Graphic; //create a new Graph objectGraph
    }
    //initialization
    void initialGraph(vector<int> &ver, vector<vector<int>> &edge);
    //operation
    void BreadFirstSearch(int s);
    void DepthFirstSearch(int s);
    int MST_Prim(int s); // minimum weight spaning tree
    int MST_Kruskal(int s); // minimum weight spaning tree
    list<int> singleSourceShortestPath_Bellman_Ford(Graphic* Graph, int s); //shortest path from s to the other vertexs
    list<int> singleSourceShortestPath_Dijkstra(Graphic* Graph, int s);
    int maximumFlow(Graphic* Graph, int s,int t); //by edmonds karp
};

void GraphicOperaion::initialGraph(vector<int> &ver, vector<vector<int>> &edge)
{
    Graph->vertexs = ver;
    for (unsigned i=0;i<edge.size();i++)
    {
        Graph->adj[edge[i][0]-1].push_back(edge[i][1]-1); // create adjlist
        //Graph->adj[edge[i][0]-1].push_back(edge[i][1]-1);
        Graph->weight[edge[i][0]-1][edge[i][1]-1] = edge[i][2];// assign weight
    }

}

void GraphicOperaion::BreadFirstSearch(int s)
{
    vector<bool> mark(maxsize,false); // 
    queue<int> q; //create a null queue
    q.push(s);
    mark[s]=true;

    while(!q.empty())
    {
        s = q.front();
        cout<<s+1<<endl;
        q.pop();
        for (unsigned i=0;i<Graph->adj[s].size();i++)// all vertexs in adjlists respect to s
        {
            if(!mark[Graph->adj[s][i]])
            {
                mark[Graph->adj[s][i]] = true;
                q.push(Graph->adj[s][i]);
            }
        }
    }
}

void GraphicOperaion::DepthFirstSearch(int s)
{
    stack<int> nodestack;
    vector<bool> visited(maxsize,false);//initial all 0

    nodestack.push(s);//source node push stack
    visited[s] = true;

    int cur_node;
    while(!nodestack.empty())
    {
        cur_node = nodestack.top();
        nodestack.pop();
        cout<<cur_node+1<<" ";
        for(unsigned i=0;i<Graph->adj[cur_node].size();i++)
        {
            if(!visited[Graph->adj[cur_node][i]])
            {
                visited[Graph->adj[cur_node][i]] = true;
                nodestack.push(Graph->adj[cur_node][i]);
            }
        }
    }
}

int GraphicOperaion::MST_Prim(int s)
{
    vector<bool> visited(maxsize,false);
    key[s] = 0;
    visited[s] = true;
    for (unsigned i=0;i<Graph->adj[s].size();i++)
    {
        insert(Graph->adj[s][i], Graph->weight[s][Graph->adj[s][i]]+key[s]);
    }

    int sum = 0;
    while(!heap.size())
    {
        int num = extract_min();
        sum += key[num];//weight increase
        visited[num] = true;
        for(unsigned i=0;i<Graph->adj[num].size();i++)
        {
            if(!visited[i])
            {
                insert(Graph->adj[num][i], Graph->weight[num][Graph->adj[num][i]]);
            }
        }
    }
}