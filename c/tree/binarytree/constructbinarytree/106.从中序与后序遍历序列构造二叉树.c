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

// 递归
struct TreeNode* build(int* inorder, int inStart, int inEnd, int* postorder,
                       int postStart, int postEnd) {
  if (inEnd < inStart) {
    return NULL;
  }

  int rootVal = postorder[postEnd];
  int index = 0;
  for (int i = inStart; i <= inEnd; ++i) {
    if (inorder[i] == rootVal) {
      index = i;
      break;
    }
  }

  int leftSize = index - inStart;
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = rootVal;
  root->left = build(inorder, inStart, inStart + leftSize - 1, postorder,
                     postStart, postStart + leftSize - 1);
  root->right = build(inorder, inStart + leftSize + 1, inEnd, postorder,
                      postStart + leftSize, postEnd - 1);

  return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder,
                           int postorderSize) {
  return build(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);
}

// @lc code=end
