/*
 * @lc app=leetcode.cn id=337 lang=c
 *
 * [337] 打家劫舍 III
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

// 官方题解
struct SubtreeStatus {
  int selected;
  int notSelected;
};
struct SubtreeStatus dfs(struct TreeNode *node) {
  if (!node) {
    return (struct SubtreeStatus){0, 0};
  }
  struct SubtreeStatus l = dfs(node->left);
  struct SubtreeStatus r = dfs(node->right);
  int selected = node->val + l.notSelected + r.notSelected;
  int notSelected =
      fmax(l.selected, l.notSelected) + fmax(r.selected, r.notSelected);
  return (struct SubtreeStatus){selected, notSelected};
}
int rob(struct TreeNode *root) {
  struct SubtreeStatus rootStatus = dfs(root);
  return fmax(rootStatus.selected, rootStatus.notSelected);
}

// @lc code=end
