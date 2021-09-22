/*
 * @lc app=leetcode.cn id=106 lang=c
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
struct TreeNode* traversal(int* inorder, int inorderStart, int inorderSize,
                           int* postorder, int postorderStart,
                           int postorderSize) {
  if (postorderStart == postorderSize) return NULL;

  int rootValue = postorder[postorderSize - 1];
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = rootValue;
  if (postorderSize - postorderStart == 1) {
    root->left = NULL;
    root->right = NULL;
    return root;
  }

  int delimiter;
  for (delimiter = inorderStart; delimiter < inorderSize; ++delimiter) {
    if (inorder[delimiter] == rootValue) {
      break;
    }
  }

  root->left =
      traversal(inorder, inorderStart, delimiter, postorder, postorderStart,
                postorderStart + delimiter - inorderStart);
  root->right =
      traversal(inorder, delimiter + 1, inorderSize, postorder,
                postorderStart + delimiter - inorderStart, postorderSize - 1);

  return root;
}
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder,
                           int postorderSize) {
  if (inorderSize == 0 || postorderSize == 0) {
    return NULL;
  }

  return traversal(inorder, 0, inorderSize, postorder, 0, postorderSize);
}

// @lc code=end
