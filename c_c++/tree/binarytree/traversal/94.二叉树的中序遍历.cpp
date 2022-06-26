/*
给定一个二叉树的根节点root，返回它的中序遍历。

示例1：
输入：root = [1,null,2,3]
输出：[1,3,2]

示例2：
输入：root = []
输出：[]

示例3：
输入：root = [1]
输出：[1]

提示：
树中节点数目在范围[0, 100]内
-100 <= Node.val <= 100

进阶: 递归算法很简单，你可以通过迭代算法完成吗？
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
  traversal(root->left, returnSize, result);
  result[(*returnSize)++] = root->val;
  traversal(root->right, returnSize, result);

  return;
}
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  traversal(root, returnSize, result);

  return result;
}

// 迭代
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
  int* ans = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  struct TreeNode* stack[100];
  int top = 0;

  struct TreeNode* cur = root;
  while (cur || top > 0) {
    if (cur) {
      stack[top++] = cur;
      cur = cur->left;
    } else {
      cur = stack[--top];
      ans[(*returnSize)++] = cur->val;
      cur = cur->right;
    }
  }

  return ans;
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
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
  *returnSize = 0;

  if (root == NULL) {
    return root;
  }
  memset(stack, 0, sizeof(stack));
  int* result = (int*)malloc(sizeof(int) * 100);

  struct TreeNode* cur = root;
  while (cur || !empty()) {
    if (cur) {
      push(cur);
      cur = cur->left;
    } else {
      cur = top();
      pop();
      result[(*returnSize)++] = cur->val;
      cur = cur->right;
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
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
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
      push(node);  // 添加中节点
      push(NULL);  // 中节点访问过，但是还没有处理，加⼊空节点做为标记。
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

// 遍历
class Solution {
 public:
  void traversal(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
      return;
    }

    traversal(root->left, res);
    res.emplace_back(root->val);
    traversal(root->right, res);
  }
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    traversal(root, res);
    return res;
  }
};

// 递归
class Solution {
 public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) {
      return res;
    }

    stack<TreeNode*> stk;
    TreeNode* cur = root;
    while (cur || !stk.empty()) {
      if (cur) {
        stk.push(cur);
        cur = cur->left;
      } else {
        cur = stk.top();
        stk.pop();
        res.emplace_back(cur->val);
        cur = cur->right;
      }
    }

    return res;
  }
};