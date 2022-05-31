/*
给定二叉树的根节点root，返回所有左叶子之和。

示例1：
输入: root = [3,9,20,null,null,15,7]
输出: 24
解释: 在这个二叉树中，有两个左叶子，分别是9和15，所以返回24

示例2:
输入: root = [1]
输出: 0

提示:
节点数在[1, 1000]范围内
-1000 <= Node.val <= 1000
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

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
