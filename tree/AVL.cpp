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

    int bal = 0; // balance factor (left height - right height)
    int height = 0;
    TreeNode(int val)
    {
        this->val = val;
    }
};


void updateheight_balance(TreeNode *root)
{
    int rh = root->right == NULL ? -1 : root->right->height;
    int lh = root->left == NULL ? -1 : root->left->height;
    int bal = lh - rh;

    int height = max(lh, rh) + 1;
    root->bal = bal;
}

TreeNode *rightrotation(TreeNode *A)
{
    TreeNode *B = A->left;
    TreeNode *Bkaright = B->right;

    B->right = A;
    A->left = Bkaright;

    updateheight_balance(A);
    updateheight_balance(B);
    return B;
}

TreeNode *leftrotation(TreeNode *A)
{

    TreeNode *B = A->right;
    TreeNode *Bkaleft = B->left;

    B->left = A;
    A->right = Bkaleft;

    updateheight_balance(A);
    updateheight_balance(B);
    return B;
}

TreeNode *getRotation(TreeNode *root)
{
    updateheight_balance(root);
    if (root->bal == 2)
    { // LL LR
        if (root->left->bal == 1)
        { // LL
            return rightrotation(root);
        }
        else // LR
        {
            root->left = leftrotation(root->left);
            return rightrotation(root);
        }
    }
    else if (root->bal == -2)
    { // RR RL
        if (root->left->bal == -1)
        { // RR
            return leftrotation(root);
        }
        else // RL
        {
            root->right = rightrotation(root->right);
            return leftrotation(root);
        }
    }
    return root;
}

TreeNode *addData(TreeNode *root, int data)
{
    if (root == NULL)
        return new TreeNode(data);

    if (root->val < data)
    {
        root->right = addData(root->right, data);
    }
    else
    {
        root->left = addData(root->left, data);
    }
    return getRotation(root);
}

int getMin(TreeNode *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root->val;
}

TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;
    if (root->val < key)
        root->right = deleteNode(root->right, key);
    else if (root->val > key)
        root->left = deleteNode(root->left, key);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            TreeNode *rNode = root->left != NULL ? root->left : root->right;
            delete root;
            return rNode;
        }
        int minnode = getMin(root->right);
        root->val = minnode;
        root->right = deleteNode(root->right, minnode);
    }
   return getRotation(root);
}


// 1382
vector<int> height;

void updateheight(TreeNode *root)
{
    int lh = root->left != NULL ? height[root->left->val] : -1;
    int rh = root->right != NULL ? height[root->right->val] : -1;

    height[root->val] = max(lh, rh) + 1;
}

int getbal(TreeNode *root)
{
    int lh = root->left != NULL ? height[root->left->val] : -1;
    int rh = root->right != NULL ? height[root->right->val] : -1;

    return lh - rh;
}

TreeNode *rightrotation(TreeNode *A)
{
    TreeNode *B = A->left;
    TreeNode *Bkaright = B->right;

    B->right = A;
    A->left = Bkaright;

    B->right = getrotation1(A);
    return getrotation1(B);
}

TreeNode *leftrotation(TreeNode *A)
{

    TreeNode *B = A->right;
    TreeNode *Bkaleft = B->left;

    B->left = A;
    A->right = Bkaleft;

    B->left = getrotation1(A);
    return getrotation1(B);
}
TreeNode *getrotation1(TreeNode *root)
{
    updateheight(root);
    if (getbal(root) >= 2)
    {
        if (getbal(root->left) >= 1){ // ll
            return rightrotation(root);
        } else{ // lr
            root->left = leftrotation(root->left);
            return rightrotation(root);
        }
    }
    else if (getbal(root) <= -2)
    {
        if (getbal(root->right) <= -1){ // rr
            return leftrotation(root);
        }else{ // rl
            root->right = rightrotation(root->right);
            return leftrotation(root);
        }
    }
    return root;
}

TreeNode *reconstructTree(TreeNode *root)
{
    if (root == NULL)
        return NULL;

    root->left = reconstructTree(root->left);
    root->right = reconstructTree(root->right);

    return getrotation1(root);
}

TreeNode *balanceBST(TreeNode *root)
{
    height.resize((int)1e5 + 1, -1);
    return reconstructTree(root);
}

int main(){

}