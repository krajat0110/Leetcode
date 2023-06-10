#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class TreeNode
{
public:
    int val = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    TreeNode(int val)
    {
        this->val = val;
    }
};

int size(TreeNode *root)
{
    return root == NULL ? 0 : size(root->left) + size(root->right) + 1;
}

int height(TreeNode *root)
{
    return root == NULL ? -1 : max(height(root->left), height(root->right)) + 1;
}

int maximun(TreeNode *root)
{
    return root == NULL ? -(int)1e9 : max(root->val, max(maximun(root->left), maximun(root->right)));
}

int minimun(TreeNode *root)
{
    return root == NULL ? (int)1e9 : min(root->val, min(minimun(root->left), minimun(root->right)));
}

// mirror the tree

void mirrorBinaryTree(TreeNode *root)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
        return;

    TreeNode <int> *temp = root->left;
    root->left = root->right;
    root->right = temp;
    //  delete temp;
    // free(temp);
    mirrorBinaryTree(root->left);
    mirrorBinaryTree(root->right);
}

// preorder tree

void preOrder(TreeNode<int> *root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

//postorder
void postOrder(TreeNode<int> *root)
{
    if (root == NULL)
        return;

    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void delete(TreeNode *root)
{
    if (root == NULL)
        return NULL;
    for (int i = 0; i < children.size(); i++)
    {
        delete (root->children[i]);
    }
    delete root;
}

// find
bool find(TreeNode *root, int data)
{
    if (root == NULL)
        return false;
    if (root->val == data)
        return true;

    return find(root->right, data) || find(root->left, data);
}

bool node_toRoot_path(TreeNode *root, int data, vector<TreeNode *> &ans)
{
    if (root == NULL)
        return false;
    if (root->val == data)
    {
        ans.push_back(root);
        return true;
    }
    bool res = node_toRoot_path(root->left, data, ans)||node_toRoot_path(root->right, data, ans);

    if (res)
        ans.push_back(root);
    return res;
}

vector<TreeNode *> node_toRoot_path2(TreeNode *root, int data)
{
    if (root == NULL)
        return {};

    if (root->val == data)
    {
        return {root};
    }

    vector<TreeNode *> left = node_toRoot_path2(root->left, data);
    if (left.size() != 0)
    {
        left.push_back(root);
        return left;
    }

    vector<TreeNode *> right = node_toRoot_path2(root->right, data);
    if (right.size() != 0)
    {
        right.push_back(root);
        return right;
    }

    return {};
}

void root_to_nodeleaf(TreeNode *root, vector<vector<int>> &ans, vector<int> &sans)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) //means ki wo leaf node he 
    {
        sans.push_back(root->val);
        ans.push_back(sans);
        sans.pop_back();
        return;
    }

    sans.push_back(root->val); //curr root ki val 
    root_to_nodeleaf(root->left, ans, sans);
    root_to_nodeleaf(root->right, ans, sans);
    sans.pop_back(); //removing last node while doing backtrack 
}

vector<vector<int>> root_alleaf_path(TreeNode *root)
{
    vector<vector<int>> ans;
    vector<int> sans;
    root_to_nodeleaf(root, ans, sans);
    return ans;
}

void exactlyOneChild_1(TreeNode *root, vector<int> &ans) //give vector of parents with exactly one child 
{
    if (root == NULL || root->left == NULL && root->right == NULL)
    {
        return;
    }
    if (root->left == NULL || root->right == NULL)
        ans.push_back(root->val);

    exactlyOneChild_1(root->left, ans);
    exactlyOneChild_1(root->right, ans);
}

vector<int> exactlyOneChild(TreeNode *root)
{
    vector<int> ans;
    exactlyOneChild_1(root, ans);
    return ans;
}
// leetcode 863

void kdown(TreeNode *root, int k, TreeNode *block, vector<int> &ans)
{
    if (root == NULL || k < 0 || root == block)
        return;

    if (k == 0)
    {
        ans.push_back(root->val);
    }
    kdown(root->left, k - 1, block, ans);
    kdown(root->right, k - 1, block, ans);
}

vector<int> distanceK01(TreeNode *root, TreeNode *target, int k)
{
    vector<TreeNode *> path;
    node_toRoot_path(root, target->val, path);

    vector<int> ans;
    TreeNode *block = NULL;
    for (int i = 0; i < path.size(); i++)
    {
        kdown(path[i], k - i, block, ans);
        block = path[i];
    }
    return ans;
}

int distancek02(TreeNode *root, TreeNode *target, int k, vector<int> &ans)
{
    if (root == NULL)
        return -1;

    if (root == target)
    {
        kdown(root, k, NULL, ans);
        return 1;
    }

    int ld = distancek02(root->left, target, k, ans); // ld is telling the left distance of node from root;
    if (ld != -1)
    {
        kdown(root, k - ld, root->left, ans);
        return ld + 1;
    }

    int rd = distancek02(root->right, target, k, ans);
    if (rd != -1)
    {
        kdown(root, k - rd, root->right, ans);
        return rd + 1;
    }
    return -1;
}

vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
{
    vector<int> ans;

    int nr = distancek02(root, target, k, ans);

    return ans;
}


//========================https://www.geeksforgeeks.org/burn-the-binary-tree-starting-from-the-target-node/
void burningtreenode(TreeNode *root, int time, TreeNode *block, vector<int> &ans)
{
    if (root == NULL || root == block)
        return ;

    if (time == ans.size())
    {
        ans.push_back({});              // adding empty vector to ans
        ans[time].push_back(root->val); // ans ke time val ke idx pe root ki value push karna
    }
    burningtreenode(root->left, time + 1, block, ans);
    burningtreenode(root->right, time + 1, block, ans);
}

int burningtree(TreeNode *root, int firenode, vector<int> &ans)
{
    if (root == NULL)
        return 1;

    if (root->val == firenode )
    {
        burningtreenode(root, 0, NULL, ans);
        return 1;
    }
    int lt = burningtree(root->left, firenode, ans);
    if (lt != -1)
    {
        burningtreenode(root, lt, root->left, ans);
        return lt + 1;
    }
    int rt = burningtree(root->right, firenode, ans);
    if (rt != -1)
    {
        burningtreenode(root, rt, root->right, ans);
        return rt + 1;
    }
    return -1;
}

///============burning tree node with water==============//
void burningTreeNodeWithWater(TreeNode *root, int time, TreeNode *blockNode, unordered_set<int> &waterSet, vector<vector<int>> &ans)
{
    if (root == nullptr || root == blockNode || waterSet.find(root->val) != waterSet.end())
        return;
    if (time == ans.size()) // if(time == ans.size()) ans.push_back({});
        ans.push_back({});
    ans[time].push_back(root->val);

    burningTreeNodeWithWater(root->left, time + 1, blockNode, waterSet, ans);
    burningTreeNodeWithWater(root->right, time + 1, blockNode, waterSet, ans);
}

int burningTreeWithWater(TreeNode *root, int fireNode, unordered_set<int> &waterSet, vector<vector<int>> &ans)
{
    if (root == nullptr)
        return -1;
    if (root->val == fireNode)
    {
        if (waterSet.find(root->val) == waterSet.end()) // equal ho gaya (if true huwa) matlb present nahi he end tak bhi nahi milla
        {                                               // for cpp : map.find(root->val) != map.end();
            burningTreeNodeWithWater(root, 0, nullptr, waterSet, ans);
            return 1;
        }
        return -2; // fire node is present but it have water.
    }

    int lt = burningTreeWithWater(root->left, fireNode, waterSet, ans);
    if (lt > 0)
    {
        if (waterSet.find(root->val) == waterSet.end())
        {
            burningTreeNodeWithWater(root, lt, root->left, waterSet, ans);
            return lt + 1;
        }
        return -2; // fire node is present but it have water.
    }

    if (lt == -2)
        return -2;

    int rt = burningTreeWithWater(root->right, fireNode, waterSet, ans);
    if (rt > 0)
    {
        if (waterSet.find(root->val) == waterSet.end())
        {
            burningTreeNodeWithWater(root, rt, root->right, waterSet, ans);
            return rt + 1;
        }
        return -2; // fire node is present but it have water.
    }
    if (rt == -2)
        return -2;

    return -1;
}

void burningTreeWithWater(TreeNode *root, int data)
{
    unordered_set<int > waterSet;
    vector<vector<int>> ans;
    waterSet.insert(8);
    waterSet.insert(2);

    burningTreeWithWater(root, data, waterSet, ans);
    for (vector<int> &ar : ans)
    {
        for (int ele : ar)
            cout << ele << " ";
        cout << endl;
    }
}

void *burnwithwater(TreeNode *root){
    burningTreeWithWater(root, 5);
}

// LCA leetcode tree
//brute force
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    vector<TreeNode *> list1, list2;
    node_toRoot_path(root, p->val, list1);
    node_toRoot_path(root, q->val, list2);

    int i = list1.size() - 1, j = list2.size() - 1;

    TreeNode *LCA = nullptr;
    while (i >= 0 && j >= 0)
    {
        if (list1[i] != list2[j])
            break;

        LCA = list1[i];
        i--;
        j--;
    }
    return LCA;
}

//optimized
TreeNode *LCANode = NULL;
bool LCA(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == NULL)
        return false;

    bool selfplaced = (root == p || root == q);

    bool leftplaced = LCA(root->left, p, q);
    bool rightplaced = LCA(root->right, p, q);

    if ((selfplaced && leftplaced) || (selfplaced && rightplaced) || (leftplaced && rightplaced))
        LCANode = root;

    return selfplaced || leftplaced || rightplaced;
}

TreeNode * lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    LCA(root, p, q);
    return LCANode;
}

int main()
{
}