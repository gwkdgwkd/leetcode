/*
给定一个非空二叉树的根节点root,以数组的形式返回每一层节点的平均值。
与实际答案相差10^-5以内的答案可以被接受。

示例1：
输入：root = [3,9,20,null,null,15,7]
输出：[3.00000,14.50000,11.00000]
解释：第0层的平均值为3,第1层的平均值为14.5,第2层的平均值为11。
因此返回[3, 14.5, 11] 。

示例2:
输入：root = [3,9,20,15,7]
输出：[3.00000,14.50000,11.00000]

提示：
树中节点数量在[1, 10^4]范围内
-2^31 <= Node.val <= 2^31 - 1
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 迭代
#define MAXQUEUE 1000
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
double* averageOfLevels(struct TreeNode* root, int* returnSize) {
  double* result = (double*)malloc(sizeof(double) * 10000);
  *returnSize = 0;
  front = tail = size = 0;

  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    double sum = 0;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      sum += node->val;
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
    result[(*returnSize)++] = sum / n;
  }

  return result;
}

class Solution {
 public:
  vector<double> averageOfLevels(TreeNode* root) {
    vector<double> res;
    if (root == nullptr) {
      return res;
    }

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
      int n = q.size();
      double sum = 0;
      for (int i = 0; i < n; ++i) {
        TreeNode* cur = q.front();
        q.pop();
        sum += cur->val;
        if (cur->left) {
          q.push(cur->left);
        }

        if (cur->right) {
          q.push(cur->right);
        }
      }
      res.emplace_back(sum / n);
    }
    return res;
  }
};
