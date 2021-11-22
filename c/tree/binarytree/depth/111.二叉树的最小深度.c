/*
 * @lc app=leetcode.cn id=111 lang=c
 *
 * [111] 二叉树的最小深度
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

// BFS找到的路径一定是最短的，但代价就是空间复杂度比DFS大很多。
// DFS不能找最短路径吗？其实也是可以的，但是时间复杂度相对高很多。要把所有路径找到，然后再找出最小的。
// 一般来说在找最短路径的时候使用BFS，其他时候还是DFS使用得多一些（主要是递归代码好写）。

// 递归，DFS
int minDepth(struct TreeNode* root) {
  if (root == NULL) return 0;

  int leftDepth = minDepth(root->left);
  int rightDepth = minDepth(root->right);

  // 当⼀个左⼦树为空，右不为空，这时并不是最低点
  if (root->left == NULL && root->right != NULL) {
    return 1 + rightDepth;
  }
  // 当⼀个右⼦树为空，左不为空，这时并不是最低点
  if (root->left != NULL && root->right == NULL) {
    return 1 + leftDepth;
  }

  return 1 + fmin(leftDepth, rightDepth);
}

// 迭代，BFS
// BFS算法都是用「队列」这种数据结构，每次将一个节点周围的所有节点加入队列。
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
// @lc code=end
