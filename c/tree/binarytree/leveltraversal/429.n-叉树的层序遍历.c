/*
 * @lc app=leetcode.cn id=429 lang=c
 *
 * [429] N 叉树的层序遍历
 */

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 迭代
#define MAXQUEUE 10000
struct Node* queue[MAXQUEUE];
int front, tail, size;
int enQueue(struct Node* data) {
  if ((tail + 1) % MAXQUEUE == front) {
    printf("full\n");
    return tail;
  }
  queue[tail % MAXQUEUE] = data;
  tail++;
  size++;
  return tail;
}
struct Node* deQueue() {
  if (front == tail % MAXQUEUE) {
    printf("empty\n");
    return NULL;
  }
  struct Node* ret = queue[front];
  front = (front + 1) % MAXQUEUE;
  size--;
  return ret;
}
int empty() { return size == 0; }
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
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
      struct Node* node = deQueue();
      result[*returnSize][i] = node->val;
      for (int j = 0; j < node->numChildren; ++j) {
        if (node->children[j]) {
          enQueue(node->children[j]);
        }
      }
    }
    (*returnSize)++;
  }

  return result;
}
// @lc code=end
