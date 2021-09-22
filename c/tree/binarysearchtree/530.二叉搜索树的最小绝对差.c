/*
 * @lc app=leetcode.cn id=530 lang=c
 *
 * [530] 二叉搜索树的最小绝对差
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
int node[10000];
int nodeSize;
void traversal(struct TreeNode* root) {
  if (root == NULL) return;
  traversal(root->left);
  node[nodeSize++] = root->val;
  traversal(root->right);
  return;
}
int getMinimumDifference(struct TreeNode* root) {
  nodeSize = 0;
  traversal(root);

  int min = INT_MAX;
  for (int i = 1; i < nodeSize; ++i) {
    min = fmin(min, node[i] - node[i - 1]);
  }

  return min;
}
// @lc code=end
