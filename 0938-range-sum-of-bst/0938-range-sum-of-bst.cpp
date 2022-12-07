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
    int rangeSumBST(TreeNode* root, int L, int H) {
         if(!root) return 0;
        int ans = root -> val >= L && root -> val <= H ? root -> val : 0;
        if(root -> val > L) ans += rangeSumBST(root -> left, L, H);
        if(root -> val < H) ans += rangeSumBST(root -> right, L, H);
        return ans;
    }
};