/*
 * @lc app=leetcode.cn id=515 lang=c
 *
 * [515] 在每个树行中找最大值
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
int* largestValues(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 10000);
  *returnSize = 0;
  front = tail = size = 0;

  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    int max = INT_MIN;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      max = fmax(max, node->val);
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
    result[(*returnSize)++] = max;
  }

  return result;
}
// @lc code=end
