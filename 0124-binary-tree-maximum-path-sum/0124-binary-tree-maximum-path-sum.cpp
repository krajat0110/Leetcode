/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
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
    int maxPathSum(TreeNode* root) {
        maxPathSum1(root);
        return NodeToNodeMaxPathSum;
    }
};