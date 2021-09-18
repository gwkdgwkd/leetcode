/*
 * @lc app=leetcode.cn id=513 lang=c
 *
 * [513] 找树左下角的值
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

// 使⽤层序遍历再合适不过了，⽐递归要好理解的多！只需要记录最后⼀⾏第⼀个节点的数值就可以了。

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
int findBottomLeftValue(struct TreeNode* root) {
  if (root == NULL) {
    return 0;
  }
  front = tail = size = 0;
  enQueue(root);
  int ret = 0;
  while (!empty()) {
    int n = size;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      if (i == 0) {
        ret = node->val;
      }
      if (node->left) enQueue(node->left);
      if (node->right) enQueue(node->right);
    }
  }

  return ret;
}

// 递归
int maxDepth;
int leftValue;
void traversal(struct TreeNode* node, int level) {
  if (node->left == NULL && node->right == NULL) {
    if (level > maxDepth) {
      maxDepth = level;
      leftValue = node->val;
    }
    return;
  }

  if (node->left) {
    level++;
    traversal(node->left, level);
    level--;
  }
  if (node->right) {
    level++;
    traversal(node->right, level);
    level--;
  }
  return;
}
int findBottomLeftValue(struct TreeNode* root) {
  maxDepth = INT_MIN;
  traversal(root, 0);
  return leftValue;
}
// @lc code=end
