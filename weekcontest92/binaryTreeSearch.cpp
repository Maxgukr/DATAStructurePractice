#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
struct TreeNode
    {
        int value; //element value
        //int key;
        //map<int,int> node;
        TreeNode *left;
        TreeNode *right;
        TreeNode *p; //parent node
        TreeNode(int x) : value(x), left(NULL), right(NULL), p(NULL) {} //默认构造函数
    };
//template <class T>
class binaryTree
{
    private:
        vector<TreeNode*> nodePath;
//TreeNode *root;
    public:
        //binaryTree();
        TreeNode* initBinaryTree(int *array, int size);
        int getNodeValue(TreeNode *t);
        void preOrder(TreeNode *t); //previous order visit binary tree
        void inOrder(TreeNode *t); //middle order visit binary tree
        void postOrder(TreeNode *t); //post order visit binary tree
        void visit(TreeNode *x); //visit node x, output its value
        int getTreeDepth(TreeNode *root); // the height of the binary tree
        int getTreeWideth(TreeNode *root); //get the wideth of the tree 
        vector<TreeNode*> farthestNodes(TreeNode *root); //the farthest nodes from root node
        void depthFirstSearch(TreeNode *root); //depth prior search
        void breadFirstSearch(TreeNode *root); //braedth prior search
        TreeNode* deepestNodesNCA(vector<TreeNode *> &a); // deepest nodes nearest common ancestror 
        TreeNode* nodesNearestCommonAncestor(vector<TreeNode*> &nodes); //结点列表中的最近公共祖先 
        void nodePathTrack(TreeNode *root, vector<TreeNode*> &path, vector<TreeNode*> &nodes); //得到由深度优先搜索算法找到根节点目标结点所经过的路径 
        bool isValidBST(TreeNode* root);
};

TreeNode* binaryTree::initBinaryTree(int *array, int size)
{
    if(size < 1)
    {
        return NULL;
    }
    TreeNode **nodes = new TreeNode*[size]; //申请大小为size的指针数组
    for(int i = 0;i<size;i++)
    {
        if (array[i] == '#')
        {
            nodes[i] = NULL;
        }
        else
        {
            nodes[i] = new TreeNode(array[i]);
        }
    }
    queue<TreeNode*> nodesQueue; //定义一个结点队列
    nodesQueue.push(nodes[0]); //根节点入队

    TreeNode *node;
    int index = 1;
    while(index<size)
    {
        node = nodesQueue.front();//取队列中的第一个数据
        nodesQueue.pop(); //弹出
        nodesQueue.push(nodes[index++]);
        node->left = nodesQueue.back();

        if( node->left!=NULL)
            node->left->p = node;

        nodesQueue.push(nodes[index++]);
        node->right = nodesQueue.back();

        if(node->right!=NULL)
            node->right->p = node;
    }
    return nodes[0]; //返回根节点
}

int binaryTree::getNodeValue(TreeNode *t)
{
    return t->value;
}
 //vector<int> nodes;
void binaryTree::inOrder(TreeNode *t)
{
    //中序遍历二叉树
   
    if(t!=NULL){
        inOrder(t->left);
        visit(t);
        inOrder(t->right);
    }
 
}

void binaryTree::postOrder(TreeNode *t)
{
    //后序遍历二叉树
    if(t!=NULL){
        postOrder(t->left);
        postOrder(t->right); 
        visit(t);
    }
}

void binaryTree::preOrder(TreeNode *t)
{
    //前序遍历二叉树
    if(t!=NULL){
        visit(t);
        preOrder(t->left);
        preOrder(t->right); 
    }
}

void binaryTree::visit(TreeNode *t)
{
    cout<<t->value<<" ";
}

int binaryTree::getTreeDepth(TreeNode *root)
{
    //get the depth of the tree
    if(root == NULL){
        return 0;
    }
        
    int leftDepth = getTreeDepth(root->left);
    int rightDepth = getTreeDepth(root->right);

    return ((leftDepth > rightDepth)?leftDepth:rightDepth) + 1;
}

int  binaryTree::getTreeWideth(TreeNode *root)
{
    if(root == NULL)
        return 0;

    queue<TreeNode *> nodequeue;
    nodequeue.push(root); //push root node in queue
    int wideth = 0;
    //int depth = 0;
    while(!nodequeue.empty()){//in this cycle begin, the queue include all next level nodes
        //depth++;
        int curlevelSize = nodequeue.size(); //current level nodes number
        wideth = (curlevelSize > wideth)?curlevelSize:wideth; // select max level number as wideth
        int cnt = 0; 
        while(cnt < curlevelSize){
            TreeNode *node = nodequeue.front();
            nodequeue.pop();
            cnt++;
            if(node->left){
                nodequeue.push(node->left);
            }
            if(node->right){
                nodequeue.push(node->right);
            }
        }
    }   
    return wideth; 
}

void binaryTree::depthFirstSearch(TreeNode *root)
{
    stack<TreeNode *> nodestack;
    nodestack.push(root); //node push in stack
    TreeNode *node;
    while(!nodestack.empty()){
        node = nodestack.top();
        cout<<node->value<<endl;
        nodestack.pop();
        if(node->right){
            nodestack.push(node->right);
        }
        if(node->left){
            nodestack.push(node->left);
        }
    }
}

void binaryTree::breadFirstSearch(TreeNode *root)
{
    //bread prior search binary tree
    queue<TreeNode *> nodequeue;
    nodequeue.push(root); //root node push in queue
    TreeNode *node;
    while(!nodequeue.empty()){
        node = nodequeue.front();
        cout<<node->value<<endl;
        nodequeue.pop();
        if(node->left){
            nodequeue.push(node->left);
        }
        if(node->right){
            nodequeue.push(node->right);
        }
    }
}

vector<TreeNode*> binaryTree::farthestNodes(TreeNode *root)
{
    if(root == NULL){
        cout<<"tree is null"<<endl;
        vector<TreeNode *> res(1,NULL);
        return res;
    }
    map<int, vector<TreeNode*>> leafnode;
    queue<TreeNode *> nodequeue;
    nodequeue.push(root);
    int depth=0;
    while(!nodequeue.empty()){
        depth++;
        int curlevelSize = nodequeue.size();//current level nodes number
        int cnt = 0;
        while(cnt < curlevelSize){
            TreeNode *node = nodequeue.front();

            if(!node->left&&!node->right){
                // judge this node is leafnode or not
                leafnode[depth].push_back(node); // if this node is leafnode, record it
            }
            nodequeue.pop();
            cnt++;
            if(node->left){
                nodequeue.push(node->left);
            }
            if(node->right){
                nodequeue.push(node->right);
            }
        }
    }
    return leafnode[depth];
}

TreeNode * binaryTree::deepestNodesNCA(vector<TreeNode*> &nodearray)
{
    /*
    此为二叉树中有父节点的版本
    所有的最深结点都在深度为depth的同一层，首先遍历每一结点，找到上一层的父节点；
    对上一层的父节点元素进行去重，再继续往上找上一层的父节点；
    指导只有一个父节点，则此为最终的子树的根节点；
    从此公共父节点开始遍历所有元素。
    */
   vector<TreeNode *> nodes;
    while(nodearray.size()!=1){
        for (int i=0;i<nodearray.size();i++){
            nodes.push_back(nodearray[i]->p);
        }
        //nodearray.pop_back();
        vector<TreeNode *>::iterator it = unique(nodes.begin(), nodes.end());//nodes 去重
        nodes.erase(it, nodes.end());
        nodearray = nodes;
        nodes.clear();
    } 
    if(nodearray.size()==1)
        return nodearray[0];
    else
        return NULL;
}

TreeNode* binaryTree::nodesNearestCommonAncestor(vector<TreeNode*> &nodes)
{
    /*
    思路：首先对每个结点使用深度优先搜索算法，并记录搜索到结点的路径；
    比较每个结点的路径，最深的相同结点即为最近公共祖先
    */

}
vector<vector<TreeNode*>> mypath;
void binaryTree::nodePathTrack(TreeNode *root, vector<TreeNode*> &path, vector<TreeNode*> &nodes)
{   
    /*
    思路：当用前序遍历的方式访问到某一个节点的时候，我们把该节点添加到路径中。
    如果该节点的值和我们要找的值相等，则打印路径，如果不相等，则继续访问它的子节点。
    当前节点访问结束之后，递归函数将自动回到它的父节点。
    因此我们在函数退出之前要在路径上删除当前节点，以确保返回父节点时路径刚好是从根节点到父节点的路径
    */
   //递归的解法，可以输出，但无法正确返回
   
    if(root==NULL)
    {   
        //vector<TreeNode*> res(1,NULL);
        return ;
    }
    path.push_back(root);
    for(int i=0;i<nodes.size();i++)
    {  
        if(root->value==nodes[i]->value)
        {
            //path.push_back(t);
            mypath.push_back(path);
            return ;
        }
    }
    if(root->left!=NULL)
    {
        nodePathTrack(root->left, path, nodes);
    }
    if(root->right!=NULL)
    {
        nodePathTrack(root->right, path, nodes);
    }
    path.pop_back();
}

//中序遍历一个二叉树，判断是否搜索二叉树
bool binaryTree::isValidBST(TreeNode* root) {
    if(root==NULL)
        return true;
    stack<TreeNode*> nodestack;
    TreeNode *cur = root;
    TreeNode *pre = NULL;
    while(cur || !nodestack.empty()){
        while(cur){
            nodestack.push(cur);//循环结束时，cur=NULL;
            cur=cur->left;
        }
        cur = nodestack.top();//先得到最左边的结点
        nodestack.pop();
        if(pre && cur->value <= pre->value)//如果右边值小于或等于左边的值
            return false;
        pre = cur;
        cur = cur->right;
    }
    return true;
}

//递归遍历所有子树判断一颗二叉树是否为搜索二叉树；
bool isValidBST(TreeNode* root) {
       
        return isValidBST(root, LONG_MIN, LONG_MAX);
}
bool isValidBST(TreeNode *root, long mn, long mx) {
    if (!root) return true;
    if (root->value <= mn || root->value >= mx) return false;
    return isValidBST(root->left, mn, root->value) && isValidBST(root->right, root->value, mx);
}
int main()
{
 
    int a[]={3,5,1,6,2,0,8,'#','#',7,4};
    int b[]={1,1,'#'};
    binaryTree btree;
    int size = sizeof(a)/sizeof(int);
    //初始化
    TreeNode *tree = btree.initBinaryTree(a, size);
    //bt.setNodePointer(tree);
    TreeNode *tree2 = btree.initBinaryTree(b, 3);
    btree.isValidBST(tree2);
    cout<<"inorder traverse"<<endl;
    btree.inOrder(tree);
    cout<<"post order tarverse"<<endl;
    btree.postOrder(tree);
    cout<<"previous order traverse"<<endl;
    btree.preOrder(tree);
    cout<<endl;
    cout<<"get depth:"<<endl;
    cout<<btree.getTreeDepth(tree)<<endl;

    cout<<"get wideth:"<<endl;
    cout<<btree.getTreeWideth(tree)<<endl;

    cout<<"depth first search:"<<endl;
    btree.depthFirstSearch(tree);

    cout<<"bread first search:"<<endl;
    btree.breadFirstSearch(tree);

    cout<<"fartest leafnodes:"<<endl;
    vector<TreeNode*> leafnode = btree.farthestNodes(tree);//返回最远结点的指针
    for(int i =0; i<leafnode.size();i++)
    {
        cout<<btree.getNodeValue(leafnode[i]);
    }
    cout<<endl;

    TreeNode *n = btree.deepestNodesNCA(leafnode);//含有父节点指针时的方法。
    cout<<"fartest leafnodes common ancestor:"<<endl;
    cout<<btree.getNodeValue(n)<<endl;
    btree.breadFirstSearch(n);

    //找到到指定结点的路径
    vector<TreeNode*> path;
    btree.nodePathTrack(tree, path, leafnode);

    system("pause");
    return 0;
}