#include<iostream>
#include<vector>
using namespace std;

class TreeNode {
public:
     int data = 0;
     TreeNode *left = NULL;
     TreeNode *right = NULL;

     TreeNode(int val){
       this -> data = data;
    }
};

int min(TreeNode *node)
{
    TreeNode *curr = node;
    while (curr->left != NULL)
        curr = curr->left;

    return curr->data;
}

int max(TreeNode *node)
{
    TreeNode *curr = node;
    while (curr->right != NULL)
    {
        curr = curr->right;
    }
    return curr->data;
}

int sum(TreeNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int ls = sum(node->left);
    int rs = sum(node->right);

    return ls + rs + node->data;
}

int size(TreeNode *node)
{

    if (node == NULL)
        return 0;

    int tsum = size(node->left);
    int ssum = size(node->right);

    return tsum + ssum + 1;
}

bool find(TreeNode *node, int data)
{
    while (node != NULL)
    {
        if (node->data == data)
        {
            return true;
        }
        else if (node->data > data)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return false;
}

vector<TreeNode *> nodeToRootPath(TreeNode *node, int data){
    vector<TreeNode *> ans;
    
    while (node != NULL)
    {
        ans.push_back(node);
        if (node->data == data)
            break;
        else if (node->data > data)
            node = node->left;
        else
            node = node->right;
    }
    return ans;
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    TreeNode *LCA = NULL;
    while (root != NULL)
    {
        if (root->data < p->data && root->data < q->data)
        {
            root = root->right;
        }
        else if (root->data > p->data && root->data > q->data)
        {
            root = root->left;
        }
        else
            LCA = root;
        break;
    }
    return (LCA != NULL && find(LCA, p->data) && find(LCA, q->data)) ? LCA : NULL;
}

// https://leetcode.com/problems/binary-tree-cameras/
//  -1 : need a camera, 0 : it has a camera, 1 : dosen't required any camera.
int helper(TreeNode *root, int &count)
{
    if (root == NULL)
        return 1;

    int left = helper(root->left, count);
    int right = helper(root->right, count);
    // if either of my child needs a camera i need to acquire a camera myself
    if (left == -1 || right == -1)
    {
        // count of cameras increases
        count++;
        // now i pass a sign that i am a camera
        return 0;
    }
    // if either of my child is a camera then that means i dont need a camera
    else if (left == 0 || right == 0)
        return 1;
    // last case which includes the case when neither of my children
    // need a camera but i do
    // this may happen when my children's child is a camera
    return -1;
}
int minCameraCover(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int count = 0;
    if (helper(root, count) == -1)
        count++;
    return count;
}

// https://leetcode.com/problems/house-robber-iii/

//{rob,without rob}
vector<int> rob_(TreeNode *root)
{
    if (root == NULL)
        return {0, 0};

    vector<int> LR = rob_(root->left); //left result
    vector<int> RR = rob_(root->right); //right result

    vector<int> ans(2);

    ans[0] = LR[1] + root->val + RR[1];  
    ans[1] = max(LR[1], LR[0]) + max(RR[0], RR[1]);

    return ans;
}

int rob(TreeNode *root)
{
    if (root == NULL)
        return 0;

    vector<int> ans = rob_(root);
    return max(ans[0], ans[1]);
}

// https://leetcode.com/problems/distribute-coins-in-binary-tree/submissions/
int moves = 0;
int distributeCoins_(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int Leftcoins = distributeCoins_(root->left);
    int Rightcoins = distributeCoins_(root->right);

    moves += abs(Leftcoins) + abs(Rightcoins);

    return Leftcoins + Rightcoins + (root->val - 1);
}

int distributeCoins(TreeNode *root)
{
    if (distributeCoins_(root) != 0)
        return -1;
    return moves;
}

// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/submissions/

int dfs(vector<vector<int>> &tree, int root, vector<bool> &hasApple, vector<bool> &vis)
{
    int time = 0;
    vis[root] = true;
    for (auto child : tree[root])
    {
        if (!vis[child])
        {
            time += dfs(tree, child, hasApple, vis);
        }
    }
    if (time != 0)
        return time + 2;
    else if (hasApple[root])
        return 2;
    else
        return 0;
}

int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple)
{
    vector<vector<int>> tree(n);
    for (int i = 0; i < n; i++)
        tree[i] = vector<int>();

    for (vector<int> e : edges)
    {
        tree[e[0]].push_back(e[1]);
        tree[e[1]].push_back(e[0]);
    }
    vector<bool> vis(n);
    int ans = dfs(tree, 0, hasApple, vis);

    return ans != 0 ? ans - 2 : ans;
}