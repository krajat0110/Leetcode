#include <iostream>
#include <vector>
#include <list>
using namespace std;

class TreeNode
{
public:
    int val = 0;
    TreeNode *left = NULL;
    TreeNode *right = NULL;

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

// https://leetcode.com/problems/diameter-of-binary-tree/submissions/
    int diameterTree(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int rd = diameterTree(root->right);
    int ld = diameterTree(root->left);

    int rh = height(root -> right);
    int lh = height(root -> left);

    return max(max(rd , ld) , rh + lh + 2);
}

vector<int> diameterTree02(TreeNode *root)
{
    if (root == NULL)
        return {0, -1};

    vector<int> rd = diameterTree02(root->right);
    vector<int> ld = diameterTree02(root->left);

    vector<int> res(2); //{diameter , height};

    res[0] = max(max(ld[0], rd[0]), rd[1] + ld[1] + 2);
    res[1] = max(ld[1], rd[1]) + 1;

    return res;
}

int diameterOfBinaryTree(TreeNode *root)
{
    vector<int> ans = diameterTree02(root);
    return ans[0];
}

// https://leetcode.com/problems/path-sum-ii/

void pathsum_(TreeNode *root, int targetSum, vector<int> &sans, vector<vector<int>> &ans)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        if (root->val - targetSum == 0)
        {
            sans.push_back(root->val);
            ans.push_back(sans);
            sans.pop_back();
        }
        return;
    }
    sans.push_back(root->val);
    pathsum_(root->left, targetSum - root->val, sans, ans);
    pathsum_(root->right, targetSum - root->val, sans, ans);
    sans.pop_back();
}

vector<vector<int>> pathSum(TreeNode *root, int targetSum)
{
    vector<int> sans;
    vector<vector<int>> ans;
    pathsum_(root, targetSum, sans, ans);
    return ans;
}

//method 1:

//{leaf2leaf , nodetoleaf}
vector<int>maxPathSum_01(TreeNode *root){
    if(root == NULL) return {(int)-1e9,(int)-1e9};

    if(root -> left == NULL && root -> right == NULL){
        return {(int)-1e9, root -> val};
    }
    vector<int> ls = maxPathSum_01(root-> left);
    vector<int>rs = maxPathSum_01(root-> right);

    vector<int>myres(2);
    myres[0] = max(ls[0] , rs[0]);
    if(root -> left != NULL && root -> right != NULL){
        myres[0] = max(myres[0] , (ls[1] + rs[1] + root -> val));
    }
    myres[1] = max(ls[1],rs[1]) + root -> val;
    return myres;
}

int maxPathSum(TreeNode *root){
    vector<int>ans = maxPathSum_01(root);
    return ans[0];
}


//method 2
int LeafToLeafMaxPathSum = -(int)1e9;
int maxPathSum_02(TreeNode *root)
{
    if (root == NULL)
        return (int)-1e9;

    if (root->left == NULL && root->right == NULL)
    {
        return root->val;
    }
    int lnl = maxPathSum_02(root->left); //left node to leaf
    int rnl = maxPathSum_02(root->right); //right node to leaf


    if (root->left != NULL && root->right != NULL)
    {
        LeafToLeafMaxPathSum = max(LeafToLeafMaxPathSum , lnl + rnl + root -> val);
    }
    return max(lnl , rnl) + root -> val;
}

int maxPathSum(TreeNode *root)
{
    maxPathSum_02(root);
    return LeafToLeafMaxPathSum;
}

int NodeToNodeMaxPathSum = -(int)1e9;
int maxPathSum1(TreeNode *root){
    if(root == NULL)
    return 0;

    int ltn = maxPathSum1(root->left); // left root To Node
    int rtn = maxPathSum1(root->right); // right root To Node

    int rootToNodeMaxPathSum = max(ltn , rtn) + root -> val;
    NodeToNodeMaxPathSum = max(NodeToNodeMaxPathSum, max(root -> val , max(rootToNodeMaxPathSum , ltn + rtn + root -> val)));

    return max(rootToNodeMaxPathSum , root -> val);
}

// Maximum Path Sum Of Binary Tree
public
static int max(int... arr)
{
    int max = arr[0];
    for (int ele : arr)
        max = Math.max(max, ele);

    return max;
}

static int NodeToNodeMaxPathSum = -(int)1e9;

public
static int maxPathSum_(TreeNode root)
{
    if (root == null)
        return 0;

    int lrtn = maxPathSum_(root.left);  // left root To Node
    int rrtn = maxPathSum_(root.right); // right root To Node

    int rootToNode = Math.max(lrtn, rrtn) + root.val;
    NodeToNodeMaxPathSum = max(NodeToNodeMaxPathSum, rootToNode, root.val, lrtn + root.val + rrtn);

    return max(rootToNode, root.val);
}

public
static int maxPathSum(TreeNode root)
{
    maxPathSum_(root);
    return NodeToNodeMaxPathSum;
}

// Maximum Path Sum In Between Two Leaves Of Binary Tree

int LeafToLeafMaxPathSum = -(int)1e9;
int maxPathSum_02(TreeNode *root)
{
    if (root == NULL)
        return (int)-1e9;

    if (root->left == NULL && root->right == NULL)
    {
        return root->val;
    }
    int lnl = maxPathSum_02(root->left);  // left node to leaf
    int rnl = maxPathSum_02(root->right); // right node to leaf

    if (root->left != NULL && root->right != NULL)
    {
        LeafToLeafMaxPathSum = max(LeafToLeafMaxPathSum, lnl + rnl + root->val);
    }
    return max(lnl, rnl) + root->val;
}

int maxPathSum(TreeNode *root)
{
    maxPathSum_02(root);
    return LeafToLeafMaxPathSum;
}

// https://leetcode.com/problems/recover-binary-search-tree/

TreeNode *getRightMostNode(TreeNode *node, TreeNode *curr)
{
    while (node->right != NULL && node->right != curr)
    {
        node = node->right;
    }
    return node;
}

void recoverTree(TreeNode *root)
{
    TreeNode *curr = root;
    TreeNode *prev = nullptr, *a = NULL, *b = NULL;
    while (curr != nullptr)
    {
        TreeNode *left = curr->left;
        if (left == nullptr)
        {
            if (prev != nullptr && prev->val > curr->val)
            {
                if (a == NULL)
                    a = prev;
                b = curr;
            }
            prev = curr;
            curr = curr->right;
        }
        else
        {
            TreeNode *rightMostNode = getRightMostNode(left, curr);
            if (rightMostNode->right == nullptr)
            {                                // thread creation block
                rightMostNode->right = curr; // thread is created

                curr = curr->left;
            }
            else
            {                                   // thread destroy block
                rightMostNode->right = nullptr; // thread is cut down
                if (prev != nullptr && prev->val > curr->val)
                {
                    if (a == NULL)
                        a = prev;
                    b = curr;
                }
                prev = curr;
                curr = curr->right;
            }
        }
    }
    if (a != NULL)
    {
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
}

int main(){

}