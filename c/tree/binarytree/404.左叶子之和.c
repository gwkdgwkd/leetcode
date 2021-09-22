/*
 * @lc app=leetcode.cn id=404 lang=c
 *
 * [404] 左叶子之和
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
int sumOfLeftLeaves(struct TreeNode* root) {
  if (root == NULL) return 0;

  int t = 0;
  if (root->left != NULL && root->left->left == NULL &&
      root->left->right == NULL) {
    t = root->left->val;
  }

  return t + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}

// 迭代
int idx;
struct TreeNode* stack[100];
void push(struct TreeNode* node) { stack[idx++] = node; }
struct TreeNode* top() {
  return stack[idx - 1];
}
void pop() { --idx; }
int empty() { return idx == 0 ? 1 : 0; }
int sumOfLeftLeaves(struct TreeNode* root) {
  int ret = 0;
  if (root == NULL) return ret;
  memset(stack, 0, sizeof(stack));
  idx = 0;
  push(root);
  while (!empty()) {
    struct TreeNode* node = top();
    pop();
    if (node->left != NULL && node->left->left == NULL &&
        node->left->right == NULL) {
      ret += node->left->val;
    }
    if (node->left) push(node->left);
    if (node->right) push(node->right);
  }

  return ret;
}

// @lc code=end
