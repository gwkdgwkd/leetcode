/*
 * @lc app=leetcode.cn id=700 lang=c
 *
 * [700] 二叉搜索树中的搜索
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
struct TreeNode* searchBST(struct TreeNode* root, int val) {
  if (root == NULL) return root;

  if (root->val > val) {
    return searchBST(root->left, val);
  } else if (root->val < val) {
    return searchBST(root->right, val);
  }
  return root;
}

// 迭代
struct TreeNode* searchBST(struct TreeNode* root, int val) {
  while (root) {
    if (root->val > val)
      root = root->left;
    else if (root->val < val)
      root = root->right;
    else
      return root;
  }
  return NULL;
}

// @lc code=end
