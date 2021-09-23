/*
 * @lc app=leetcode.cn id=669 lang=c
 *
 * [669] 修剪二叉搜索树
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
struct TreeNode* trimBST(struct TreeNode* root, int low, int high) {
  if (!root) return root;

  if (root->val < low) {
    return trimBST(root->right, low, high);
  } else if (root->val > high) {
    return trimBST(root->left, low, high);
  }

  root->left = trimBST(root->left, low, high);
  root->right = trimBST(root->right, low, high);
  ;

  return root;
}

// 迭代
struct TreeNode* trimBST(struct TreeNode* root, int low, int high) {
  if (!root) return root;

  // 处理头结点，让root移动到[low,high]范围内，注意是左闭右闭
  while (root && (root->val < low || root->val > high)) {
    if (root->val < low)
      root = root->right;
    else
      root = root->left;
  }

  // 此时root已经在[low,high]范围内，处理左孩⼦元素⼩于low的情况
  struct TreeNode* cur = root;
  while (cur) {
    while (cur->left && cur->left->val < low) {
      cur->left = cur->left->right;
    }
    cur = cur->left;
  }
  cur = root;
  // 此时root已经在[low,high]范围内，处理右孩⼦⼤于high的情况
  while (cur) {
    while (cur->right && cur->right->val > high) {
      cur->right = cur->right->left;
    }
    cur = cur->right;
  }

  return root;
}
// @lc code=end
