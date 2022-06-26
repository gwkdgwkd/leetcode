/*
给你二叉树的根节点root，返回其节点值自底向上的层序遍历。
即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历。

示例1：
输入：root = [3,9,20,null,null,15,7]
输出：[[15,7],[9,20],[3]]

示例2：
输入：root = [1]
输出：[[1]]

示例3：
输入：root = []
输出：[]

提示：
树中节点数目在范围[0, 2000]内
-1000 <= Node.val <= 1000
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 迭代
#define MAXQUEUE 200
struct TreeNode* queue[MAXQUEUE];
int front, tail, size;
int enQueue(struct TreeNode* data) {
  if ((tail + 1) % MAXQUEUE == front) {
    printf("full\n");
    return tail;
  }
  queue[tail % MAXQUEUE] = data;
  tail++;
  size++;
  return tail;
}
struct TreeNode* deQueue() {
  if (front == tail % MAXQUEUE) {
    printf("empty\n");
    return NULL;
  }
  struct TreeNode* ret = queue[front];
  front = (front + 1) % MAXQUEUE;
  size--;
  return ret;
}
int empty() { return size == 0; }
int** levelOrderBottom(struct TreeNode* root, int* returnSize,
                       int** returnColumnSizes) {
  int** result = (int**)malloc(sizeof(int*) * 10000);
  *returnSize = 0;
  *returnColumnSizes = (int*)malloc(sizeof(int) * 10000);
  front = tail = size = 0;

  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    (*returnColumnSizes)[*returnSize] = n;
    result[*returnSize] = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      result[*returnSize][i] = node->val;
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
    (*returnSize)++;
  }

  // 在102的基础上反转
  for (int i = 0, j = *returnSize - 1; i < j; ++i, --j) {
    int temp = (*returnColumnSizes)[i];
    (*returnColumnSizes)[i] = (*returnColumnSizes)[j];
    (*returnColumnSizes)[j] = temp;

    int* tempPtr = result[i];
    result[i] = result[j];
    result[j] = tempPtr;
  }

  return result;
}

class Solution {
 public:
  vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> res;
    if (root == nullptr) {
      return res;
    }

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
      int n = q.size();
      vector<int> v(n);
      for (int i = 0; i < n; ++i) {
        TreeNode* cur = q.front();
        q.pop();
        v[i] = cur->val;
        if (cur->left) {
          q.push(cur->left);
        }

        if (cur->right) {
          q.push(cur->right);
        }
      }
      res.emplace_back(v);
    }

    for (int left = 0, right = res.size() - 1; left < right; ++left, --right) {
      res[left].swap(res[right]);
    }
    return res;
  }
};
