#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <iostream>
#define maxsize 10
using namespace std;
//Graph represent by adj-list


struct edgeAdj //
{
    int adjData; //save adj vertex node sub
    int weight; // weight between two vertexs
    edgeAdj* next; // point to next adj vertex
};

struct vertexNode
{
    int data; // save each adjlist's vertex data
    edgeAdj* firstEdge;
};//vertexNode, Adjlist[maxsize];

class eEdge
{
    friend class GraphicOperaion;
private:
    int v1;
    int v2;
    int weight;
};
   map<pair<int,int>,int> weight;
typedef struct Graphic
{
    vector<int> vertexs; // number of vertexs
    vector<eEdge*> edges; //number of edges
    vertexNode adjlist[maxsize]; //adjlist of Graph
    //list<pair<int,int>> *adj;

}Graphic;

class GraphicOperaion
{
private:
    Graphic* Graph;
public:
    GraphicOperaion()
    {
        Graph = new Graphic; //create a new Graph objectGraph
    }
    //initialization
    void CreatGraphic(vector<int> &vertexList, vector<eEdge*> &edge); //only vertex no edges
    vector<eEdge*> CreateEdge(vector<vector<int>> &edge);
    void InsertGraphic(eEdge* E); //insert a edge
    void BuildGraphic(vector<int> &vertexList, vector<eEdge*> &edges);
    //operation
    void BreadFirstSearch(Graphic* Graph);
    void DepthFirstSearch(Graphic* Graph);
    int MST_Prim(Graphic* Graph, int s); // minimum weight spaning tree
    int MST_Kruskal(Graphic* Graph, int s); // minimum weight spaning tree
    list<int> singleSourceShortestPath_Bellman_Ford(Graphic* Graph, int s); //shortest path from s to the other vertexs
    list<int> singleSourceShortestPath_Dijkstra(Graphic* Graph, int s);
    int maximumFlow(Graphic* Graph, int s,int t); //by edmonds karp
};

void GraphicOperaion::CreatGraphic(vector<int> &vertexList, vector<eEdge*> &edge)
{
    Graph->vertexs = vertexList; // vertexs
    Graph->edges = edge; // edges

    for(unsigned v=0;v<vertexList.size();v++)
    {
        (Graph->adjlist+vertexList[v])->firstEdge = NULL;
    }
}

vector<eEdge*> GraphicOperaion::CreateEdge(vector<vector<int>> &edge)
{
    vector<eEdge*> Edge;
    for (unsigned i=0;i<edge.size();i++)
    {
        Edge[i] = new eEdge();
        Edge[i]->v1 = edge[i][0];
        Edge[i]->v2 = edge[i][1];
        Edge[i]->weight = edge[i][2];
    }
    return Edge;
}

void GraphicOperaion::InsertGraphic(eEdge* e)
{
    edgeAdj* newnode = new edgeAdj;
    newnode->weight = e->weight;
    // uodate node
    newnode->next = (Graph->adjlist+e->v1)->firstEdge;
    (Graph->adjlist+e->v1)->firstEdge = newnode;
}

void GraphicOperaion::BuildGraphic(vector<int> &vertexList, vector<eEdge*> &edges)
{
    CreatGraphic(vertexList, edges);
    //Graph->Ne = edges.size();

    //create and insert edges
    if (edges.size() != 0)
    {
        //eEdge* E = new eEdge();
        for(unsigned i=0; i<edges.size(); i++)
        {
            //cin>>E->v1>>E->v2>>E->weight;
            InsertGraphic(edges[i]);
        }
    }
}
