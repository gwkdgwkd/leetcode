/*
 * @lc app=leetcode.cn id=572 lang=c
 *
 * [572] 另一棵树的子树
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// 递归
bool compare(struct TreeNode* root, struct TreeNode* subRoot) {
  if (!root && !subRoot) return true;
  if ((!root && subRoot) || (root && !subRoot) ||
      (root && subRoot && root->val != subRoot->val))
    return false;

  return compare(root->left, subRoot->left) &&
         compare(root->right, subRoot->right);
}
bool dfs(struct TreeNode* root, struct TreeNode* subRoot) {
  if (!root) return false;

  return compare(root, subRoot) || dfs(root->left, subRoot) ||
         dfs(root->right, subRoot);
}
bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
  return dfs(root, subRoot);
}

// @lc code=end
