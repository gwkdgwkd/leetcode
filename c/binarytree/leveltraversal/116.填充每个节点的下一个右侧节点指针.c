/*
 * @lc app=leetcode.cn id=116 lang=c
 *
 * [116] 填充每个节点的下一个右侧节点指针
 */

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */
// 迭代
#define MAXQUEUE 5000
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
struct Node* connect(struct Node* root) {
  front = tail = size = 0;
  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    struct Node* pre;
    for (int i = 0; i < n; ++i) {
      struct Node* node = deQueue();
      if (i != 0) {
        pre->next = node;
      }
      pre = node;
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
  }

  return root;
}
// @lc code=end
