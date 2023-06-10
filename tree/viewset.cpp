#include <iostream>
#include <vector>
#include <list>
#include<queue>
using namespace std;

class TreeNode
{
public:
    int data = 0;
    TreeNode *left = NULL;
    TreeNode *right = NULL;

    TreeNode(int data)
    {
        this->data = data;
    }
};

void levelorderwise(TreeNode *root)
{

    list<TreeNode *> que;
    que.push_back(root);
    int level = 0;

    while (que.size() != 0)
    {
        int size = que.size();
        cout << "Level :" << level << " :";
        while (size-- > 0)
        {

            TreeNode *rnode = que.front();
            cout << rnode;
            que.pop_front();

            if (rnode->left != NULL)
            {
                que.push_back(rnode->left);
            }
            if (rnode->right != NULL)
            {
                que.push_back(rnode->right);
            }
        }
        cout << endl;
        level++;
    }
}

void leftviewofBST(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    list<TreeNode *> que;
    que.push_back(root);
    int level = 0;

    vector<int> ans;
    while (que.size() != 0)
    {
        int size = que.size();
        ans.push_back(que.front()->data);
        while (size-- > 0)
        {
            TreeNode *rnode = que.front();
            que.pop_front();
            if (rnode->left != NULL)
            {
                que.push_back(rnode->left);
            }
            if (rnode->right != NULL)
            {
                que.push_back(rnode->right);
            }
        }
        level++;
    }
}

void rightviewofBST(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    list<TreeNode *> que;
    que.push_back(root);
    int level = 0;

    vector<int> ans;
    while (que.size() != 0)
    {
        int size = que.size();
        ans.push_back(que.front()->data);
        while (size-- > 0)
        {
            TreeNode *rnode = que.front();
            que.pop_front();

            if (rnode->right != NULL)
            {
                que.push_back(rnode->right);
            }
            if (rnode->left != NULL)
            {
                que.push_back(rnode->left);
            }
        }
        level++;
    }
}

class vpair
{
public:
    TreeNode *node = NULL;
    int vl = 0;

    vpair(TreeNode *node, int vl)
    {
        this->node = node;
        this->vl = vl;
    }
};

void widthoftree(TreeNode *root, int vl, vector<int> &MinMax)
{
    if (root == NULL)
        return;

    MinMax[0] = min(MinMax[0], vl);
    MinMax[1] = max(MinMax[1], vl);

    widthoftree(root->left, vl - 1, MinMax);
    widthoftree(root->right, vl + 1, MinMax);
}

vector<vector<int>> verticalTraversal(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> MinMax(2, 0);
    widthoftree(root, 0, MinMax);
    int width = (MinMax[1] - MinMax[0] + 1);

    vector<vector<int>> ans(width);

    list<vpair> que;
    que.push_back(vpair(root, abs(MinMax[0])));

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            vpair ele = que.front();
            que.pop_front();
            TreeNode *node = ele.node;
            int vl = ele.vl;

            ans[vl].push_back(node->data);

            if (node->left != NULL)
            {
                que.push_back(vpair(node->left, vl - 1));
            }
            if (node->right != NULL)
            {
                que.push_back(vpair(node->right, vl + 1));
            }
        }
    }
    return ans;
}

vector<int> bottomview(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> MinMax(2, 0);
    widthoftree(root, 0, MinMax);
    int width = (MinMax[1] - MinMax[0] + 1);

    vector<int> ans(width);
    list<vpair> que;

    que.push_back(vpair(root, abs(MinMax[0])));

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            vpair ele = que.front();
            que.pop_front();
            TreeNode *node = ele.node;
            int vl = ele.vl;

            ans[vl] = node->data;

            if (node->left != NULL)
            {
                que.push_back(vpair(node->left, vl - 1));
            }
            if (node->right != NULL)
            {
                que.push_back(vpair(node->right, vl + 1));
            }
        }
    }
    return ans;
}

//every ele in the bottom will the stored whith the help of horizontal level  table 

vector<vector<int>> bottomOrder_dataue(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> minMax(2, 0);
    widthoftree(root, 0, minMax);
    int width = minMax[1] - minMax[0] + 1;
    vector<vector<int>> ans(width);
    vector<int> hlevel(width, -1);

    list<vpair> que;
    que.push_back(vpair(root, abs(minMax[0])));

    int level = 0;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            vpair p = que.front();
            que.pop_front();
            TreeNode *node = p.node;
            int vl = p.vl;

            if (level > hlevel[vl]) //jese he higher lvl ka ele aaega old wala dlt and new push 
            {
                ans[vl].clear();
                hlevel[vl] = level; //lvl mentaion hoga yaha 
            }
            ans[vl].push_back(node->data);

            if (node->left != NULL)
                que.push_back(vpair(node->left, vl - 1));
            if (node->right != NULL)
                que.push_back(vpair(node->right, vl + 1));
        }
        level++;
    }

    return ans;
}

vector<int> TopView(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> MinMax(2, 0);
    widthoftree(root, 0, MinMax);
    int width = (MinMax[1] - MinMax[0] + 1);

    vector<int> ans(width);

    list<vpair> que;
    que.push_back(vpair(root, abs(MinMax[0])));

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            vpair ele = que.front();
            que.pop_front();
            TreeNode *node = ele.node;
            int vl = ele.vl;

            if (ans[vl] == NULL)
                ans[vl] = node->data;

            if (node->left != NULL)
            {
                que.push_back(vpair(node->left, vl - 1));
            }
            if (node->right != NULL)
            {
                que.push_back(vpair(node->right, vl + 1));
            }
        }
    }
    return ans;
}

vector<int> verticalSum(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> MinMax(2, 0);
    widthoftree(root, 0, MinMax);
    int width = (MinMax[1] - MinMax[0] + 1);

    vector<int> ans(width ,0);
    list<vpair> que;

    que.push_back(vpair(root, abs(MinMax[0])));

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            vpair ele = que.front();
            que.pop_front();
            TreeNode *node = ele.node;
            int vl = ele.vl;

            ans[vl] += node->data;

            if (node->left != NULL)
            {
                que.push_back(vpair(node->left, vl - 1));
            }
            if (node->right != NULL)
            {
                que.push_back(vpair(node->right, vl + 1));
            }
        }
    }
    return ans;
}

vector<vector<int>> diagonalOrder(TreeNode *root)
{
    queue<TreeNode *> que;
    que.push(root);
    vector<vector<int>> ans;
    while (que.size() != 0)
    {
        int size = que.size();
        vector<int> smallAns;
        while (size-- > 0)
        {
            TreeNode *node = que.front();
            que.pop();

            while (node != nullptr)
            {
                smallAns.push_back(node->data);
                if (node->left != nullptr)
                { // add in que for next diagonal process.
                    que.push(node->left);
                }
                node = node->right; // move forward in respective diagonal.
            }
        }
        ans.push_back(smallAns);
    }

    return ans;
}

//diagonal in 1d return type GFG
vector<int> diagonal(TreeNode *root)
{
    vector<int> v;
    queue<TreeNode *> q;
    q.push(root);
    while (q.empty() == false)
    {
        TreeNode *curr = q.front();
        q.pop();

        while (curr)
        {
            v.push_back(curr->data);
            if (curr->left)
                q.push(curr->left);
            curr = curr->right;
        }
    }
    return v;
}

vector<vector<int>> diagonalSum(TreeNode *root)
{
    queue<TreeNode *> que;
    que.push(root);
    vector<vector<int>> ans;
    while (que.size() != 0)
    {
        int size = que.size();
        int sum = 0;
        while (size-- > 0)
        {
            TreeNode *node = que.front();
            que.pop();

            while (node != nullptr)
            {
                sum += root -> data;
                if (node->left != nullptr)
                { // add in que for next diagonal process.
                    que.push(node->left);
                }
                node = node->right; // move forward in respective diagonal.
            }
        }
        ans.push_back(sum);
    }
    return ans;
}

class verticalPair2
{
public:
    TreeNode *node = nullptr;
    int x = 0; // horizontal Level
    int y = 0; // vertical Level

    verticalPair2(TreeNode *node, int x, int y)
    {
        this->node = node;
        this->x = x;
        this->y = y;
    }
};

struct comp
{
public:
    bool operator()(const verticalPair2 a, const verticalPair2 b) const
    {
        if (a.y != b.y)
            return a.y > b.y; // this - other, '-' replace with '>';
        else
            return a.node->data > b.node->data;
    }
};

vector<vector<int>> verticalOrderTraversal(TreeNode *root)
{
    priority_queue<verticalPair2, vector<verticalPair2>, comp> que;
    vector<int> minMax(2, 0);
    widthoftree(root, 0, minMax);
    int len = minMax[1] - minMax[0] + 1;
    vector<vector<int>> res(len);

    que.push(verticalPair2(root, -minMax[0], 0));

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            verticalPair2 rp = que.top();
            que.pop();

            res[rp.x].push_back(rp.node->data);

            if (rp.node->left != nullptr)
                que.push(verticalPair2(rp.node->left, rp.x - 1, rp.y + 1));
            if (rp.node->right != nullptr)
                que.push(verticalPair2(rp.node->right, rp.x + 1, rp.y + 1));
        }
    }

    return res;
}