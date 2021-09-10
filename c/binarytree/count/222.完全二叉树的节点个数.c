/*
 * @lc app=leetcode.cn id=222 lang=c
 *
 * [222] 完全二叉树的节点个数
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
int countNodes(struct TreeNode* root) {
  if (root == NULL) return 0;

  return countNodes(root->left) + countNodes(root->right) + 1;
}

// 迭代
#define MAXQUEUE 17000
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
int countNodes(struct TreeNode* root) {
  if (root == NULL) return 0;
  int count = 0;

  enQueue(root);
  while (!empty()) {
    int n = size;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      count++;
      if (node->left) enQueue(node->left);
      if (node->right) enQueue(node->right);
    }
  }
  return count;
}

// @lc code=end
