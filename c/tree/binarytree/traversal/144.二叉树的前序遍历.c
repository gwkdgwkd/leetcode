/*
给你二叉树的根节点root，返回它节点值的前序遍历。

示例1：
输入：root = [1,null,2,3]
输出：[1,2,3]

示例2：
输入：root = []
输出：[]

示例3：
输入：root = [1]
输出：[1]

示例4：
输入：root = [1,2]
输出：[1,2]

示例5：
输入：root = [1,null,2]
输出：[1,2]

提示：
树中节点数目在范围[0, 100]内
-100 <= Node.val <= 100
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
void traversal(struct TreeNode* root, int* returnSize, int* result) {
  if (root == NULL) {
    return;
  }
  result[(*returnSize)++] = root->val;
  traversal(root->left, returnSize, result);
  traversal(root->right, returnSize, result);

  return;
}
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  traversal(root, returnSize, result);

  return result;
}

// 迭代
int idx = 0;
struct TreeNode* stack[100];
void push(struct TreeNode* node) { stack[idx++] = node; }
struct TreeNode* top() {
  return stack[idx - 1];
}
void pop() { --idx; }
int empty() { return idx == 0 ? 1 : 0; }
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
  *returnSize = 0;
  if (root == NULL) {
    return root;
  }
  memset(stack, 0, sizeof(stack));
  int* result = (int*)malloc(sizeof(int) * 100);

  push(root);
  while (!empty()) {
    struct TreeNode* node = top();
    pop();
    result[(*returnSize)++] = node->val;
    // 为什么要先加⼊右孩⼦，再加⼊左孩⼦呢？因为这样出栈的时候才是中左右的顺序。
    if (node->right) {
      push(node->right);
    }
    if (node->left) {
      push(node->left);
    }
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
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
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
      pop();  // 将该节点弹出，避免重复操作，下⾯再将右中左节点添加到栈中
      if (node->right) {  // 添加右节点（空节点不⼊栈）
        push(node->right);
      }
      if (node->left) {  // 添加左节点（空节点不⼊栈）
        push(node->left);
      }
      push(node);  // 添加中节点
      push(NULL);  // 中节点访问过，但是还没有处理，加⼊空节点做为标记。
    } else {  // 只有遇到空节点的时候，才将下⼀个节点放进结果集
      pop();         // 将空节点弹出
      node = top();  // 新取出栈中元素
      pop();
      result[(*returnSize)++] = node->val;  // 加⼊到结果集
    }
  }

  return result;
}
