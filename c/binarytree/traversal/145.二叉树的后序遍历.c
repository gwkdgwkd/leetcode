/*
 * @lc app=leetcode.cn id=145 lang=c
 *
 * [145] 二叉树的后序遍历
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 递归
void traversal(struct TreeNode* root, int* returnSize, int* result) {
  if (root == NULL) {
    return;
  }
  traversal(root->left, returnSize, result);
  traversal(root->right, returnSize, result);
  result[(*returnSize)++] = root->val;

  return;
}
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  traversal(root, returnSize, result);

  return result;
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
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
  memset(stack, 0, sizeof(stack));
  idx = 0;
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;

  if (root == NULL) {
    return result;
  }
  push(root);
  while (!empty()) {
    struct TreeNode* node = top();
    pop();
    result[(*returnSize)++] = node->val;
    // 相对于前序遍历，这更改⼀下⼊栈顺序
    if (node->left) {
      push(node->left);
    }
    if (node->right) {
      push(node->right);
    }
  }

  // 将结果反转之后就是左右中的顺序了
  for (int i = 0, j = *returnSize - 1; i < j; ++i, --j) {
    int temp = result[i];
    result[i] = result[j];
    result[j] = temp;
  }

  return result;
}

// 前中后，统一格式
int idx;
struct TreeNode* stack[100];
void push(struct TreeNode* node) { stack[idx++] = node; }
struct TreeNode* top() {
  return stack[idx - 1];
}
void pop() { --idx; }
int empty() { return idx == 0 ? 1 : 0; }
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
  memset(stack, 0, sizeof(stack));
  idx = 0;
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;

  if (root != NULL) {
    push(root);
  }

  while (!empty()) {
    struct TreeNode* node = top();
    if (node) {
      pop();       // 将该节点弹出，避免重复操作，下⾯再将右中左节点添加到栈中
      push(node);  // 添加中节点
      push(NULL);  // 中节点访问过，但是还没有处理，加⼊空节点做为标记。
      if (node->right) {  // 添加右节点（空节点不⼊栈）
        push(node->right);
      }
      if (node->left) {  // 添加左节点（空节点不⼊栈）
        push(node->left);
      }
    } else {  // 只有遇到空节点的时候，才将下⼀个节点放进结果集
      pop();         // 将空节点弹出
      node = top();  // 新取出栈中元素
      pop();
      result[(*returnSize)++] = node->val;  // 加⼊到结果集
    }
  }

  return result;
}
// @lc code=end
