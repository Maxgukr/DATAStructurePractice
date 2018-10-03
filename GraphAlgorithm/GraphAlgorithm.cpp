#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <iostream>
#include <utility>
using namespace std;

#define MAXSIZE 100 //define max vertex number

/*adjTable, directed  weight graph*/

struct EdgeNode
{
    int adjvex; //邻接点域，存储顶点对应的下标
    int weight; //存储边对应的权重
    EdgeNode(int v, int w):adjvex(v), weight(w) {}
    EdgeNode* next=NULL; //save next adjvex pointer
    EdgeNode() {}
    //EdgeNode(int v, int w, EdgeNode* p): adjvex(v), weight(w), next()
}Edge[MAXSIZE];

typedef struct VertexNode
{
    int data; // save vertex info
    EdgeNode* first; //head pointer
}VertexNode,adjTable[MAXSIZE];

typedef struct
{
    adjTable adj;
    int numNodes,numEdges; //vertex number and edge number in graph
}Graphadj;


class Graph
{
private:
    Graphadj *Gp;//邻接链表表示，有点复杂，设计指针操作
    vector<int> adj[MAXSIZE];//领接数组的表示法，很简单
    vector<EdgeNode> adjW[MAXSIZE];//带权重的领接数组
    int vNum;//顶点个数
    int eNum;//边的数量
    bool weighted;//有权图或无全图,默认有权图
    bool directed;
public:
    Graph(int v, int e, bool w, bool d):vNum(v), eNum(e), weighted(w), directed(d) {}
    int get_vNum() {return this->vNum;}
    int get_eNum() {return this->eNum;}
    void CreateGraphAdjList(vector<vector<int>> &edge, vector<int> &vex);  
    void CreateGraphAdjArray(vector<vector<int>> &edge);
    void BreadFirstSearch(int s); // 广度优先搜索
    void DepthFirstSearch(int s); // 深度优先搜索
    int* findPathDFS(int source, int destination); //寻找无权无向图中两点之间的最短路径。
    int* findPathBFS(int source, int destination); //寻找无权无向图中两点之间的最短路径。
    //int* findPathRecurise(int source, int destination); //寻找无权无向图中两点之间的最短路径。
    //bool rFindPath(int s, int *mask);
    vector<int> Dijkstra(int s);//有权有向图的单源最短路径
    void print_dijkstra(int source, vector<int> &d);
    int miniSpanTreePrim(int root);//利用Prim算法实现最小生成树，返回最小生成树的权重和
};

void Graph::CreateGraphAdjList(vector<vector<int>> &edge, vector<int> &vex)
{
    int i,j;
    EdgeNode *pE;//edge pointer
    Gp->numNodes = vex.size();
    Gp->numEdges = edge.size();

    for(i=0;i<Gp->numNodes;i++)
    {
        Gp->adj[i].data = vex[i];
        Gp->adj[i].first = NULL;
    }

    for(j=0;j<Gp->numEdges;j++)
    {
        //头插法
        pE = new EdgeNode;
        pE->adjvex = edge[j][0];
        pE->next = Gp->adj[edge[j][1]].first; //in directed graph, each vertex show once time
        pE->weight = edge[j][2];
        Gp->adj[edge[j][0]].first = pE;
    }
}

void Graph::CreateGraphAdjArray(vector<vector<int>> &edge)
{
    if(!this->weighted)//无全图
    {
        for(unsigned i=0;i<edge.size();i++)
        {
            edge[i][0]--;
            edge[i][1]--;
            if(!this->directed)//无向图，插入2次，不用反向操作
            {
                adj[edge[i][0]].push_back(edge[i][1]);
                adj[edge[i][1]].push_back(edge[i][0]);
            }
            else
            {
                adj[edge[i][0]].push_back(edge[i][1]);
            }
        }
    }
    else//有权图
    {
        for(unsigned i=0;i<edge.size();i++)
        {
            edge[i][0]--;
            edge[i][1]--;
            if(this->directed)
            {
                adjW[edge[i][0]].push_back(EdgeNode(edge[i][1], edge[i][2]));//有向图，只插入一次，不用反向操作
            }
            else
            {
                adjW[edge[i][0]].push_back(EdgeNode(edge[i][1], edge[i][2]));//无向图，插入二次，反向操作
                adjW[edge[i][1]].push_back(EdgeNode(edge[i][0], edge[i][2]));
            }
               
        }
    }
}

void Graph::BreadFirstSearch(int s)
{
    vector<bool> mask(this->vNum,false);
    queue<int> q;
    q.push(s);//源节点入队
    mask[s] = true;
    while(!q.empty())
    {
        s = q.front();
        q.pop();
        cout<<s+1<<" ";
        for(unsigned i=0;i<this->adj[s].size();i++)//遍历s点对应的邻接表
        {
            if(!mask[adj[s][i]])//存在没有访问到的点
            {
                mask[adj[s][i]] = true;//标记该节点
                q.push(adj[s][i]);//访问过的结点入队
            }
        }
    }
    cout<<endl;
}

void Graph::DepthFirstSearch(int s)
{
    //思路和广度遍历一模一样，就是数据结构有队列换成栈
    vector<bool> mask(this->vNum,false);
    stack<int> stack_dfs;
    stack_dfs.push(s);//源节点入栈
    mask[s] = true;
    int cur_node;
    while(!stack_dfs.empty())
    {
        cur_node = stack_dfs.top();
        cout<<cur_node+1<<" ";
        stack_dfs.pop();
        for(unsigned i=0;i<adj[cur_node].size();i++)//遍历curNode对应的所有结点
        {
            if(!mask[adj[cur_node][i]])
            {
                mask[adj[cur_node][i]] = true;
                stack_dfs.push(adj[cur_node][i]);
            }
        }
    }
    cout<<endl;
}

int* Graph::findPathDFS(int s, int d)
{
    //利用深度优先搜索找到的路径不一定是最短的
    //存在问题 不在路径上的点没有删除
    s--;
    d--;
    int *path = new int[this->vNum+1];
    //path[1] = s+1;//第一个点是起点，path[0]表示路径长度
    int lenPath = 1;
    int destination = s;//初始将终点设置为原点
    vector<bool> mask(this->vNum,false);
    stack<int> nodestack;

    nodestack.push(s);//源节点入栈
    mask[s] = true;//记录访问

    while(destination!=d)
    {
        destination = nodestack.top();
        if(destination==d)
            break;
        else
        {
            path[lenPath] = destination+1;
            lenPath++;
        }
        nodestack.pop();
        for(unsigned i=0;i<adj[destination].size();i++)
        {
            if(!mask[adj[destination][i]])
            {
                mask[adj[destination][i]] = true;
                nodestack.push(adj[destination][i]);
            }
        }
    }
    path[0] = lenPath;
    path[lenPath] = destination+1;
    return path;
}

int* Graph::findPathBFS(int s, int d)
{
    //利用广度优先搜索找到的路径就是两点之间的最短路径,仅适用于无权重的图
    //存在问题 不在路径上的点没有删除
    s--;
    d--;
    int *path = new int[this->vNum+1];
    //path[1] = s-1;//第一个点是起点，path[0]表示路径长度
    int lenPath = 1;
    int destination = s;//初始将终点设置为原点
    vector<bool> mask(this->vNum,false);
    queue<int> nodequeue;

    nodequeue.push(s);//源节点入队
    mask[s] = true;
    while(destination!=d)
    {
        destination = nodequeue.front();
        if(destination==d)
        {
            break;
        }
        else
        {
            path[lenPath] = destination+1;
            lenPath++;
        }
        nodequeue.pop();
        for(unsigned i=0;i<adj[destination].size();i++)
        {
            if(!mask[adj[destination][i]])
            {
                mask[adj[destination][i]] = true;
                nodequeue.push(adj[destination][i]);
            }
        }
    }
    path[0] = lenPath;
    path[lenPath] = destination+1;
    return path;
}


struct cmp
{
    bool operator()(pair<int,int> &p1, pair<int,int> &p2)
    {
        return p1.first>p2.first;//实现最小优先队列
    }
};
vector<int> Graph::Dijkstra(int s)
{
    // single source shortest path in a directed-weighted Graph
    // 返回每个定点到源点的距离（路径权重和）
    s--;
    typedef pair<int,int> p;
    vector<int> d(this->vNum, INT32_MAX);//保存每个结点到源节点的距离，初始化为最大值
    vector<int> parent(MAXSIZE,0);//每个结点的父节点
    d[s] = 0;//原点的距离为0
    priority_queue<p, vector<p>, cmp> miniHeap;//利用优先队列实现最小堆, 按照到源点的距离排序
    miniHeap.push(p(0,s));//first 是到原点的距离，second是节点下标
    while(!miniHeap.empty())
    {
        p v_min = miniHeap.top();//返回堆顶最小值
        //cout<<v_min.first<<" ";
        miniHeap.pop();
        int u = v_min.second;
        if(d[u]<v_min.first)//小于上界，已经更新过了
            continue;
        for(unsigned i=0;i<adjW[u].size();i++)
        {
            EdgeNode e = adjW[u][i];
            //对该边进行松弛操作
            if(d[e.adjvex]>d[u]+e.weight)
            {
                d[e.adjvex] = d[u] + e.weight;
                parent[e.adjvex] = u;
                miniHeap.push(p(d[e.adjvex], e.adjvex));
            }
        }
    }
    cout<<endl;
    return d;
}

void Graph::print_dijkstra(int s, vector<int> &d)
{
    for(int i=0;i<this->vNum;i++)
    {
        cout<<"source point "<<s<<" to "<<i+1<<" shortest distances:";
        cout<<s<<" "<<d[i]<<endl;
    }
}

 struct node     //保存key值的结点
{
    int v;
    int key;
    friend bool operator<(node a, node b)   //自定义优先级，key小的优先
    {
         return a.key > b.key;
    }
 };

 
int Graph::miniSpanTreePrim(int r)
{
    // undirected-weighted Graph
    r--;
    typedef pair<int,int> p;
    vector<int> visited(this->vNum, false);// 记录节点的访问 访问过的节点属于生成树中的节点
    vector<int> parent(this->vNum, -1);
    vector<int> d(this->vNum, INT16_MAX);
    
    priority_queue<p, vector<p>, cmp> miniHeap;//利用优先队列实现最小堆
    
    d[r] = 0;//起点
    miniHeap.push(p(0,r));
    int sum = 0;
    while(!miniHeap.empty())
    {
        p v_min = miniHeap.top();//v_min为队列中权值最小的顶点
        miniHeap.pop();
        int u = v_min.second; //定点下标
        if(visited[u])
            continue;
        visited[v_min.second] = true;
        sum += d[u];
        for(unsigned i=0;i<adjW[u].size();i++)//遍历该节点的所有邻接点，并更新权值以及入队
        {
            EdgeNode e = adjW[u][i];
            if(!visited[e.adjvex] && d[e.adjvex] > e.weight)
            {
                parent[e.adjvex] = u;
                d[e.adjvex] = e.weight;
                //vx[e.adjvex].v = adjW[nd.v][i].adjvex;
                miniHeap.push(p(d[e.adjvex], e.adjvex));
            }
        }
    }
    return sum;
}


int main()
{
    //创建一个有向无权图
    vector<vector<int>> edge = {{1,2},{1,5},{2,6},{3,4},{3,6},{3,7},{4,7},{4,8},{6,7},{8,7}};
    Graph g(8, 10, false, false); //初始化一个8个顶点，10边的无权无向图。
    g.CreateGraphAdjArray(edge);
    cout<<"Creat a Graph with "<<g.get_vNum()<<" vertexs and "<<g.get_eNum()<<" edges"<<endl;

    cout<<"BreadFirst search result:"<<endl;
    g.BreadFirstSearch(1);
    cout<<"DepthFirst search result:"<<endl;
    g.DepthFirstSearch(1);
    
    int s=0;
    int d=0;
    cout<<"find path:"<<endl;
    cout<<"input source point and distant point:";
    //cin>>s>>d;
    cout<<"Path between "<<s<<" and "<<d<<" with BFS:"<<endl;
    int *path = g.findPathBFS(2,8);
    for(int i=1;i<=*path;i++)
    {
        cout<<path[i]<<" ";
    }
    cout<<endl;

    // 有权有向图的单源最短路径 Dijkstra
    vector<vector<int>> edge_w={{1,2,10},{1,4,5},{2,3,1},{2,4,2},
                                {3,5,4},{4,2,3},{4,3,9},{4,5,2},{5,1,7},{5,3,6}};
    Graph g_w_d(5, 10, true, true); // 5个定点10条边的有权有向图
    g_w_d.CreateGraphAdjArray(edge_w);
    vector<int> dist = g_w_d.Dijkstra(1);
    g_w_d.print_dijkstra(1, dist);
    
    // 有权无向图的最小生成树 Prim算法实现
    vector<vector<int>> edge_w2 = {{1,2,4},{1,8,8},{2,3,8},{2,8,11},{3,4,7},{3,6,4},{3,9,2},
                           {4,5,9},{4,6,14},{5,6,10},{6,7,2},{7,8,1},{7,9,6},{8,9,7}};
    Graph g_w(9, 14, true, false); //5个顶点14条边的有权无向图
    g_w.CreateGraphAdjArray(edge_w2);
    cout<<"miniSpanTree with Prim weight sum:";
    cout<<g_w.miniSpanTreePrim(1)<<endl;

    
    return 0;
}