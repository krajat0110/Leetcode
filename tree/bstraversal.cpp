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

TreeNode *getrightmostnode(TreeNode *node, TreeNode *curr)
{ // left = node

    while (node->right != NULL && node->right != curr)
    {
        node = node->right;
    }
    return node;
}

vector<int> morrisInTraversal(TreeNode *root)
{
    vector<int> ans;
    TreeNode *curr = root;
    while (curr != nullptr)
    {
        TreeNode *leftNode = curr->left;
        if (leftNode == nullptr)
        {
            ans.push_back(curr->val);
            curr = curr->right;
        }
        else
        {
            TreeNode *rightmostnode = getrightmostnode(leftNode, curr);
            if (rightmostnode->right == NULL) // we need to create thread
            {
                rightmostnode->right = curr; // thread created here
                curr = curr->left;
            }
            else
            { // thread is already there we need to remove the thread buz it has already used (and we have created it )
                rightmostnode->right = NULL;
                ans.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    return ans;
}

vector<int> MorrispreOrderTraversal(TreeNode *root)
{
    vector<int> ans;
    TreeNode *curr = root;
    while (curr != NULL)
    {
        TreeNode *leftnode = curr->left;
        if (leftnode == NULL)
        {
            ans.push_back(curr->val);
            curr = curr->right;
        }
        else
        {
            TreeNode *rightmostnode = getrightmostnode(leftnode, curr);
            if (rightmostnode->right == NULL) // we need to create thread
            {
                ans.push_back(curr->val);
                rightmostnode->right = curr; // thread created here
                curr = curr->left;
            }
            else
            { // thread is already there we need to remove the thread buz it has already used (and we have created it )
                rightmostnode->right = NULL;
                curr = curr->right;
            }
        }
    }
    return ans;
}

//leetcode 98
bool isValidBST(TreeNode *root)
{
    TreeNode *curr = root;
    TreeNode *prev = nullptr;
    bool flag = true;
    while (curr != NULL)
    {
        TreeNode *leftnode = curr->left;
        if (leftnode == NULL)
        {

            if (prev != nullptr && prev->val >= curr->val)
            {
                flag = false;
            }
            prev = curr;

            curr = curr->right;
        }
        else
        {
            TreeNode *rightmostnode = getrightmostnode(leftnode, curr);
            if (rightmostnode->right == NULL)
            {
                rightmostnode->right = curr;
                curr = curr->left;
            }
            else
            {
                rightmostnode->right = NULL;

                if (prev != nullptr && prev->val >= curr->val)
                {
                    flag = false;
                }
                prev = curr;

                curr = curr->right;
            }
        }
    }
    return flag;
}


//isvalid using stack with extra space

void insertallLeft(TreeNode *root, list<TreeNode *> &st) {
    while(root != NULL ){
        st.push_front(root);
        root = root -> left;
    }
}

bool isValidBST(TreeNode *root){
    list<TreeNode *> st;
    insertallLeft(root , st);
    long prev = -(long)1e13;

    while(st.size() != 0){
        
        TreeNode *rnode = st.front(); // top element
        st.pop_front();

        if(prev >= rnode -> val) return false; //check bst condition

        insertallLeft(rnode -> right, st); //node ke right ke baad left wale saare stack me 

    }
    return true;
}

// 173. Binary Search Tree Iterator
class BSTIterator
{
private:
    list<TreeNode *> st;

public:
    BSTIterator(TreeNode *root)
    {
        insertAllLeaf(root);
    }

private:
    void insertAllLeaf(TreeNode *node)
    {
        while (node != nullptr)
        {
            st.push_front(node);
            node = node->left;
        }
    }

public:
    int next()
    {
        TreeNode *rnode = st.front();
        st.pop_front();
        insertAllLeaf(rnode->right);
        return rnode->val;
    }

    bool hasNext()
    {
        return (st.size() != 0);
    }
};


//with morris traversal function
class BSTIterator
{
private:
    TreeNode *curr = NULL;

public:
    BSTIterator(TreeNode *root)
    {
        curr = root;
    }

private:
    TreeNode *getrightmostnode(TreeNode *node, TreeNode *curr)
    {
        while (node->right != NULL && node->right != curr)
        {
            node = node->right;
        }
        return node;
    }

public:
    int next()
    {
        int rv = -1;
        while (curr != nullptr)
        {
            TreeNode *leftNode = curr->left;
            if (leftNode == nullptr)
            {
                rv = curr->val;
                curr = curr->right;
                break;
            }
            else
            {
                TreeNode *rightmostnode = getrightmostnode(leftNode, curr);
                if (rightmostnode->right == NULL)
                {
                    rightmostnode->right = curr;
                    curr = curr->left;
                }
                else
                {
                    rightmostnode->right = NULL;
                    rv = curr->val;
                    curr = curr->right;
                    break;
                }
            }
        }
        return rv;
    }

    bool hasNext()
    {
        return (curr != NULL);
    }
};


//bst to double ll using moris traversal

TreeNode *getrightmostnode(TreeNode *leftnode, TreeNode *curr)
{
    while (leftnode->right != NULL && leftnode->right != curr)
        leftnode = leftnode->right;

    return leftnode;
}

TreeNode *treeToDoublyList(TreeNode *root)
{
    TreeNode *dummy = new TreeNode(-1);
    TreeNode *prev = dummy, *curr = root;
    while (curr != nullptr)
    {
        TreeNode *leftNode = curr->left;
        if (leftNode == nullptr)
        {
            // create link
            prev->right = curr;
            curr->left = prev;
            prev = prev -> right;

            // move
            curr = curr->right;
        }
        else
        {
            TreeNode *rightmostnode = getrightmostnode(leftNode, curr);
            if (rightmostnode->right == NULL) // we need to create thread
            {
                rightmostnode->right = curr; // thread created here
                curr = curr->left;
            }
            else
            { // thread is already there we need to remove the thread buz it has already used (and we have created it )
                rightmostnode->right = NULL;
                // create link
                prev->right = curr;
                curr->left = prev;
                prev = curr;

                curr = curr->right;
            }
        }
    }
    TreeNode *head = dummy->right;
    dummy->right = head->left = NULL; //dummy ka right or head ka left alag alag ho jae 

   //for circular ll last wale node to first node se 
    prev->right = head;
    head->left = prev;

    return head;
}


/// ===============================  construction set ================================================================///


//construct bst from inorder

TreeNode *BSTcreatingfrominorder(vector<int> &in , int si , int ei){
    if(si > ei ) return NULL;

    int mid = (si+ei)/2;

    TreeNode *root = new TreeNode(in[mid]);

    root->left = BSTcreatingfrominorder(in , si , mid-1);
    root->right = BSTcreatingfrominorder(in, mid + 1, ei);

    return root;
}

    TreeNode *constructFromInOrder(vector<int> &in){
    return BSTcreatingfrominorder(in, 0, in.size() - 1);
}


Node *getmidnode(Node *head){
    
    if (head == nullptr || head -> right == nullptr)
      return head;
      
    Node *slow = head , *fast = head;

    while (fast->right != NULL && fast->right->right != NULL){
        slow = slow -> right;
        fast = fast -> right -> right;
    }

    return slow;
}

Node *SortedDLLToBST(Node* head)
{
   if(head == NULL || head -> right == NULL) return head;
   
   Node *mid = getmidnode(head);

    Node *forw = mid -> right , *prev = mid->left;

    mid->right = mid->left = forw->left = NULL;
    if (prev != NULL)
        prev->right = NULL;

    Node *root = mid , *lefthead = prev != NULL ? head : NULL , *righthead = forw;

    root->left = SortedDLLToBST(lefthead);
    root->right = SortedDLLToBST(righthead);

    return root;
}

//inorder successor in BST Tree

TreeNode *inorderSuccessor(TreeNode *root, TreeNode *x)
{
    TreeNode *curr = root, *prev = NULL, *succ = NULL;
    while (curr != nullptr)
    {
        TreeNode *leftNode = curr->left;
        if (leftNode == nullptr)
        {
            if (prev == x)
            {
                succ = curr;
            }
            prev = curr;
            curr = curr->right;
        }
        else
        {
            TreeNode *rightmostnode = getrightmostnode(leftNode, curr);
            if (rightmostnode->right == NULL) // we need to create thread
            {
                rightmostnode->right = curr; // thread created here
                curr = curr->left;
            }
            else
            { // thread is already there we need to remove the thread buz it has already used (and we have created it )
                rightmostnode->right = NULL;
                if (prev == x)
                {
                    succ = curr;
                }
                prev = curr;
                curr = curr->right;
            }
        }
    }
    return succ;
}

// Inorder Predecessor in BST
TreeNode *inorderPredecessor(TreeNode *root, TreeNode *x)
{
    TreeNode *curr = root, *prev = NULL;
    while (curr != nullptr)
    {
        TreeNode *leftNode = curr->left;
        if (leftNode == nullptr)
        {
            if (curr == x)
            {
                return prev;
            }
            prev = curr;
            curr = curr->right;
        }
        else
        {
            TreeNode *rightmostnode = getrightmostnode(leftNode, curr);
            if (rightmostnode->right == NULL) // we need to create thread
            {
                rightmostnode->right = curr; // thread created here
                curr = curr->left;
            }
            else
            { // thread is already there we need to remove the thread buz it has already used (and we have created it )
                rightmostnode->right = NULL;
                if (curr == x)
                {
                    return prev;
                }
                prev = curr;
                curr = curr->right;
            }
        }
    }
    return prev;
}


TreeNode *getrightmost(TreeNode *root){
    if(root == NULL){
       return NULL;
    }
    while(root -> right != NULL){
        root = root -> right;
    }
    return root;
}

TreeNode *getleftmost(TreeNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

void findPreSuc(TreeNode *root, TreeNode *&pre, TreeNode *&suc, int key){
    TreeNode *curr = root , *pred = NULL , *succ = NULL;

    while(curr != NULL){
        if(curr -> val = key){
            TreeNode *leftmost = getleftmost(curr -> right); //right ka leftmost hoga succesor
            succ = leftmost != NULL ? leftmost : succ;

            TreeNode *rightmost = getrightmost(curr->right); // left ka rightmost hoga predecessor
            pred = rightmost != NULL ? rightmost : pred;
            break;
            
        }else if(curr -> val < key){
            pred = curr;
            curr = curr -> right;
        }else{
            succ = curr;
            curr = curr->left;
        }
    }
    pre = pred;
    suc = succ;
}