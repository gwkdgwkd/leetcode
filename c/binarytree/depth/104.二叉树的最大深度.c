/*
 * @lc app=leetcode.cn id=104 lang=c
 *
 * [104] 二叉树的最大深度
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
int maxDepth(struct TreeNode* root) {
  if (root == NULL) return 0;

  int left = maxDepth(root->left);
  int right = maxDepth(root->right);

  return fmax(left, right) + 1;
}

// 迭代
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

int maxDepth(struct TreeNode* root) {
  if (root == NULL) return 0;
  front = tail = size = 0;

  int max = 0;
  enQueue(root);
  while (!empty()) {
    int n = size;
    ++max;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      if (node->left) enQueue(node->left);
      if (node->right) enQueue(node->right);
    }
  }
  return max;
}
// @lc code=end
