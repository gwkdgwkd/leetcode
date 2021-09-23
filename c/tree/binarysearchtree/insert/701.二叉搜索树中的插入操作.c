/*
 * @lc app=leetcode.cn id=701 lang=c
 *
 * [701] 二叉搜索树中的插入操作
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
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
  if (!root) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
  }
  if (root->val > val) {
    root->left = insertIntoBST(root->left, val);
  } else if (root->val < val) {
    root->right = insertIntoBST(root->right, val);
  }
  return root;
}

// 迭代
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
  if (root == NULL) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
  }
  struct TreeNode* cur = root;
  struct TreeNode* pre = root;
  while (cur) {
    if (cur->val > val) {
      pre = cur;
      cur = cur->left;
    } else if (cur->val < val) {
      pre = cur;
      cur = cur->right;
    }
  }

  struct TreeNode* node1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  node1->val = val;
  node1->left = node1->right = NULL;
  if (pre->val > val)
    pre->left = node1;
  else
    pre->right = node1;

  return root;
}

// @lc code=end
