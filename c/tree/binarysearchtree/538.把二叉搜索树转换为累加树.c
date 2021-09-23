/*
 * @lc app=leetcode.cn id=538 lang=c
 *
 * [538] 把二叉搜索树转换为累加树
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
int sum;
void traversal(struct TreeNode* root) {
  if (!root) return;
  // 从树中可以看出累加的顺序是右中左，所以需要反中序遍历这个⼆叉树，然后顺序累加就可以了。
  traversal(root->right);
  root->val += sum;
  sum = root->val;
  traversal(root->left);
}
struct TreeNode* convertBST(struct TreeNode* root) {
  sum = 0;
  traversal(root);
  return root;
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
int sum;
void traversal(struct TreeNode* root) {
  struct TreeNode* cur = root;
  while (cur || !empty()) {
    if (cur) {
      push(cur);
      cur = cur->right;
    } else {
      cur = top();
      pop();
      cur->val += sum;
      sum = cur->val;
      cur = cur->left;
    }
  }
}
struct TreeNode* convertBST(struct TreeNode* root) {
  sum = 0;
  idx = 0;
  traversal(root);
  return root;
}
// @lc code=end
