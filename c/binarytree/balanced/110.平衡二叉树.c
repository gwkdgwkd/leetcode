/*
 * @lc app=leetcode.cn id=110 lang=c
 *
 * [110] 平衡二叉树
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
int getDepth(struct TreeNode* root) {
  if (root == NULL) {
    return 0;
  }
  int left = getDepth(root->left);
  if (left == -1) return -1;
  int right = getDepth(root->right);
  if (right == -1) return -1;
  return abs(left - right) > 1 ? -1 : 1 + fmax(left, right);
}
bool isBalanced(struct TreeNode* root) {
  return getDepth(root) == -1 ? false : true;
}

// 迭代法，效率很低
// @lc code=end
