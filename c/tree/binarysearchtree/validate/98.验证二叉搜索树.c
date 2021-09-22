/*
 * @lc app=leetcode.cn id=98 lang=c
 *
 * [98] 验证二叉搜索树
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
bool isValidBST(struct TreeNode* root) {
  nodeSize = 0;
  traversal(root);

  for (int i = 0; i < nodeSize - 1; ++i) {
    if (node[i] >= node[i + 1]) {
      return false;
    }
  }

  return true;
}

// 递归，不用数组，只记录之前的值
int pre = INT_MIN;
bool isValidBST(struct TreeNode* root) {
  if (root == NULL) return true;

  bool left = isValidBST(root->left);
  if (pre < root->val)
    pre = root->val;
  else
    return false;
  bool right = isValidBST(root->right);

  return left && right;
}
// @lc code=end
