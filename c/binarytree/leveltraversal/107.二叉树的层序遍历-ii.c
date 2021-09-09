/*
 * @lc app=leetcode.cn id=107 lang=c
 *
 * [107] 二叉树的层序遍历 II
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
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
// @lc code=end
