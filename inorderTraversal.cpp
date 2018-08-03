 #include <vector>
 using namespace std;
  //Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

 vector<int> inorderTraversal(TreeNode* root) {
        vector<int> nodes;
        if(root->left!=NULL&&root->right!=NULL)
        {
            nodes = inorderTraversal(root->left);
            nodes = inorderTraversal(root->right);
            
        }
        nodes.push_back(root->val);
        return nodes;
 }