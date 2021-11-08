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
// 如果是一个普通二叉树，显然只要向下面这样遍历一边即可，时间复杂度O(N)：
int countNodes(struct TreeNode* root) {
  if (root == NULL) return 0;
  return countNodes(root->left) + countNodes(root->right) + 1;
}
// 如果是一棵满二叉树，节点总数就和树的高度呈指数关系，时间复杂度O(logN)：
int countNodes(struct TreeNode* root) {
  int h = 0;
  // 计算树的高度
  while (root != NULL) {
    root = root->left;
    h++;
  }
  // 节点总数就是2^h - 1
  return (int)pow(2, h) - 1;
}
// 完全二叉树比普通二叉树特殊，但又没有满二叉树那么特殊，计算它的节点总数，可以说是普通二叉树和完全二叉树的结合版
// 时间复杂度是:O(logN*logN)
int countNodes(struct TreeNode* root) {
  struct TreeNode *l = root, *r = root;
  // 记录左、右子树的高度
  int hl = 0, hr = 0;
  while (l != NULL) {
    l = l->left;
    hl++;
  }
  while (r != NULL) {
    r = r->right;
    hr++;
  }
  // 如果左右子树的高度相同，则是一棵满二叉树
  if (hl == hr) {
    return (int)pow(2, hl) - 1;
  }
  // 如果左右高度不同，则按照普通二叉树的逻辑计算
  return 1 + countNodes(root->left) + countNodes(root->right);
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
