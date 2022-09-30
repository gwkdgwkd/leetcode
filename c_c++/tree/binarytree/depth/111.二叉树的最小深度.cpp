/*
给定一个二叉树，找出其最小深度。
最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
说明：叶子节点是指没有子节点的节点。

示例1：
输入：root = [3,9,20,null,null,15,7]
输出：2

示例2：
输入：root = [2,null,3,null,4,null,5,null,6]
输出：5

提示：
树中节点数的范围在[0, 10^5]内
-1000 <= Node.val <= 1000
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// BFS找到的路径一定是最短的，但代价就是空间复杂度比DFS大很多。
// DFS不能找最短路径吗？
// 其实也是可以的，但是时间复杂度相对高很多。
// 要把所有路径找到，然后再找出最小的。
// 一般来说在找最短路径的时候使用BFS，
// 其他时候还是DFS使用得多一些（主要是递归代码好写）。

// 递归，DFS
int minDepth(struct TreeNode* root) {
  if (root == NULL) return 0;

  int leftDepth = minDepth(root->left);
  int rightDepth = minDepth(root->right);

  // 当⼀个左⼦树为空，右不为空，这时并不是最低点：
  if (root->left == NULL && root->right != NULL) {
    return 1 + rightDepth;
  }
  // 当⼀个右⼦树为空，左不为空，这时并不是最低点：
  if (root->left != NULL && root->right == NULL) {
    return 1 + leftDepth;
  }

  return 1 + fmin(leftDepth, rightDepth);
}

int minDepth(struct TreeNode* root) {
  if (root == NULL) return 0;
  if (root->left == NULL && root->right == NULL) return 1;

  int l = minDepth(root->left);
  int r = minDepth(root->right);

  if (root->left == NULL) return r + 1;
  if (root->right == NULL) return l + 1;

  return fmin(l, r) + 1;
}

// 迭代，BFS
// BFS都用队列这种数据结构，每次将一个节点周围的所有节点加入队列：
#define MAXQUEUE 400
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

int minDepth(struct TreeNode* root) {
  if (root == NULL) return 0;
  front = tail = size = 0;

  int min = 0;
  enQueue(root);
  while (!empty()) {
    int n = size;
    ++min;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      if (node->left) enQueue(node->left);
      if (node->right) enQueue(node->right);
      if (node->left == NULL && node->right == NULL) return min;
    }
  }
  return min;
}

class Solution {
 public:
  int minDepth(TreeNode* root) {
    int res = 0;
    if (root == nullptr) {
      return res;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      int n = q.size();
      res++;
      for (int i = 0; i < n; ++i) {
        TreeNode* cur = q.front();
        q.pop();

        if (cur->left == nullptr && cur->right == nullptr) {
          return res;
        }
        if (cur->left) {
          q.push(cur->left);
        }

        if (cur->right) {
          q.push(cur->right);
        }
      }
    }
    return res;
  }
};
