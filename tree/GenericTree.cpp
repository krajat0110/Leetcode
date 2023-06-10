#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <bits/stdc++.h>
using namespace std;

class TreeNode
{
public:
    int val = 0;
    vector<TreeNode *> children;

    TreeNode(int val)
    {
        this->val = val;
    }
};

int height(TreeNode *node)
{
    int maxheight = -1;

    for (TreeNode *child : node->children)
    {
        maxheight = max(maxheight, height(child));
    }
    return maxheight + 1;
}

int size(TreeNode *node)
{
    int s = 0;
    for (TreeNode *child : node->children)
    {
        s += size(child);
    }
    return s + 1;
}

int maximumEle(TreeNode *node)
{
    int gmax = -1e9;

    for (TreeNode *child : node->children)
    {
        int cmax = maximumEle(child);
        gmax = max(gmax, cmax);
    }
    gmax = max(gmax, node->val);
    return gmax;
}

bool findData(TreeNode *node, int data)
{
    if (node->val == data)
        return true;

    bool res = false;
    for (TreeNode *child : node->children)
        res = res || findData(child, data);
    return res;
}

bool rootToNodePath(TreeNode *root, int data, vector<TreeNode *> ans)
{

    if (root->val == data)
    {
        ans.push_back(root);
        return true;
    }

    bool res = false;
    for (TreeNode *child : root->children)
    {
        res = res || rootToNodePath(child, data, ans);
    }

    if (res)
    {
        ans.push_back(root);
        return res;
    }
}

vector<int> diameter_(TreeNode *node)
{
    int h1 = -1, h2 = -1, d = 0;
    for (TreeNode *child : node->children)
    {
        vector<int> ans = diameter_(child);
        if (ans[1] > h1)
        {
            h2 = h1;
            h1 = ans[1];
        }
        else if (ans[1] > h2)
            h2 = ans[1];

        d = max(ans[0], d);
    }

    return {max(h1 + h2 + 2, d), max(h1, h2) + 1};
}

int d = -1e9;
int diameter_02(TreeNode *node)
{
    int h1 = -1, h2 = -1;
    for (auto child : node->children)
    {
        int h = diameter_02(child);
        if (h >= h1)
        {
            h2 = h1;
            h1 = h;
        }
        else if (h >= h2)
            h2 = h;
    }
    d = max(d, h1 + h2 + 2);

    return max(h1, h2) + 1;
}

int diameter(TreeNode *root)
{
    diameter_02(root);
    return d;
}

// Encodes a tree to a single string.
void serializeTree(TreeNode *root, string sb)
{
    sb += root->val + " ";
    for (auto child : root->children)
    {
        serializeTree(child, sb);
    }
    sb += "NULL ";
}

string serialize(TreeNode *root)
{
    if (root == NULL)
        return "";

    string sb = "";
    serializeTree(root, sb);
    return sb;
}

// Decodes your encoded data to tree.
TreeNode *deserialize(string s)
{
    if (s.size() == 0)
        return NULL;
    string temp = "";
    vector<string> ans;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            ans.push_back(temp);
            temp = "";
        }
        temp += s[i];
    }

    list<TreeNode *> st;
    for (int i = 0; i < ans.size() - 1; i++)
    {
        string v = ans[i];

        if (v != "NULL")
        {
            // st.push_front(stoi(v));
        }
        else
        {
            TreeNode *node = st.front();
            st.pop_front();
        }
    }
    return st.front();
}

// LCA of genric tree

// bfs

void bfs(TreeNode *root)
{
    queue<TreeNode *> q;

    q.push(root);
    int level = 0;
    while (q.size() != 0)
    {
        int size = q.size();
        cout << "level" << level << "->";

        while (size-- > 0)
        {
            TreeNode *ele = q.front();
            q.pop();

            cout << ele->val;

            for (TreeNode *child : root->children)
            {
                q.push(child);
            }
        }
        cout << endl;
        level++;
    }
}

// zigzag generic Tree travel
vector<vector<int>> levelOderZigZag(TreeNode *node)
{
    if (node == NULL)
        return {};

    list<TreeNode *> que; // push_back , pop_front
    list<TreeNode *> st;  // push_front , pop_front
    vector<vector<int>> ans;

    que.push_back(node);
    int level = 0;

    while (que.size() != 0)
    {    
        vector<int>sans;
        TreeNode *ele = que.front();
        que.pop_front();
        sans.push_back(ele -> val);
        if (level % 2 == 0)
        {
            for (int i = 0; i < ele->children.size(); i++)
                st.push_front(ele->children[i]);
        }
        else
        {
            for (int i = ele->children.size() - 1; i >= 0; i--)
                st.push_front(ele->children[i]);
        }
        if (que.size() == 0)
        {
            swap(que, st);
            cout << endl;
            level++;
        } 
        ans.push_back(sans);
    }
    return ans;
}

// pep portal
void levelOderZigZag1(TreeNode *node)
{
    if (node == NULL || node->children.size() == 0)
        return;
    stack<TreeNode *> st, st1;
    st.push(node);
    int count = 1;
    while(!st.empty())
    {
        TreeNode *nd = st.top();
        st.pop();
        cout << nd->val << " ";
        if ((count % 2) == 1)
        {
            for (TreeNode *child : nd->children)
                st1.push(child);
        }
      else{
         for (int i = nd->children.size() - 1; i >= 0; i--)
                st1.push(nd->children[i]);
        }
        if (st.size() == 0)
        {
            swap(st, st1);
            cout << endl;
            count++;
        }
    }
}

//linearize  a generic Tree in linear list

TreeNode *linearize(TreeNode *root){
     if(root -> children.size() == 0) return root;

     TreeNode *Gtail = linearize(root -> children.back());
     for(int i = root -> children.size() - 2; i > 0 ; i--){

        TreeNode *child = root -> children[i];  
        TreeNode *tail = linearize(child);
        tail -> children.push_back(root -> children[i - 1]);
        root -> children.pop_back();
     }
     return Gtail;
}

//is mirror only structure wise 

bool isMirror(TreeNode *root1 , TreeNode *root2){
    if(root1 -> children.size() != root2 -> children.size()){
        return false;
    }

    int size = root2 -> children.size();
    for(int i = 0 , j = size - 1 ; i < size , j > 0 ; i++ , j--){
       
       TreeNode *child1 = root1 -> children[i];
       TreeNode *child2 = root2 -> children[j];

       if(!isMirror(child1 , child2))
        return false;
    }
    return true;
}


//is mirror with structure and value wise 

bool isMirrorTree(TreeNode *root1  , TreeNode *root2){
    if(root1 -> children.size() != root2 -> children.size() && root1 -> val != root2 -> val) return false;

    int size = root2 -> children.size();
    for(int i = 0 , j = size - 1 ; i < size , j > 0 ; i++ , j--){
        TreeNode *child1 = root1 -> children[i];
        TreeNode *child2 = root2 -> children[j];

        if(!isMirrorTree(child1, child2)) return false;
    }
    return true;
}

//isIsomorphic means both tree are same not mirror image exactly same (duplicate )
bool isIsomorphic(TreeNode *root1, TreeNode *root2)
{
    if (root1->children.size() != root2->children.size())
    {
        return false;
    }

    int size = root2->children.size();
    for (int i = 0, j = 0; i<size, j< size; i++, j++)
    {

        TreeNode *child1 = root1->children[i];
        TreeNode *child2 = root2->children[j];

        if (!isIsomorphic(child1, child2))
            return false;
    }
    return true;
}

