/*
给你一棵二叉树的根节点root，返回其节点值的后序遍历 。

示例1：
输入：root = [1,null,2,3]
输出：[3,2,1]

示例2：
输入：root = []
输出：[]

示例3：
输入：root = [1]
输出：[1]

提示：
树中节点的数目在范围[0, 100]内
-100 <= Node.val <= 100

进阶：递归算法很简单，你可以通过迭代算法完成吗？
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
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
  *returnSize = 0;
  if (root == NULL) return NULL;
  int* ans = (int*)malloc(sizeof(int) * 100);

  struct TreeNode* stack[100];
  int top = 0;

  stack[top++] = root;
  while (top > 0) {  // 中右左
    struct TreeNode* cur = stack[--top];
    ans[(*returnSize)++] = cur->val;
    if (cur->left) stack[top++] = cur->left;
    if (cur->right) stack[top++] = cur->right;
  }

  // 逆序：左右中
  int left = 0;
  int right = *returnSize - 1;
  while (left < right) {
    int tmp = ans[left];
    ans[left] = ans[right];
    ans[right] = tmp;
    ++left;
    --right;
  }

  return ans;
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
      pop();  // 将该节点弹出，避免重复操作，下⾯再将右中左节点添加到栈中
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

// 递归
class Solution {
 public:
  void traversal(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
      return;
    }

    traversal(root->left, res);
    traversal(root->right, res);
    res.emplace_back(root->val);
  }
  vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    traversal(root, res);
    return res;
  }
};

// 迭代
class Solution {
 public:
  vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) {
      return res;
    }

    stack<TreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
      TreeNode* cur = stk.top();
      stk.pop();
      res.emplace_back(cur->val);
      if (cur->left) {
        stk.push(cur->left);
      }
      if (cur->right) {
        stk.push(cur->right);
      }
    }

    for (int left = 0, right = res.size() - 1; left < right; ++left, --right) {
      int temp = res[left];
      res[left] = res[right];
      res[right] = temp;
    }

    return res;
  }
};