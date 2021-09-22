/*
 * @lc app=leetcode.cn id=101 lang=c
 *
 * [101] 对称二叉树
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
bool compare(struct TreeNode* left, struct TreeNode* right) {
  if (left == NULL && right != NULL) return false;
  if (left != NULL && right == NULL) return false;
  if (left == NULL && right == NULL) return true;

  if (left->val != right->val) return false;

  bool outside = compare(left->left, right->right);
  bool inside = compare(left->right, right->left);

  return outside && inside;
}

bool isSymmetric(struct TreeNode* root) {
  if (root == NULL) return true;
  return compare(root->left, root->right);
}

// 迭代
这个迭代法，其实是把左右两个⼦树要⽐较的元素顺序放进⼀个容器，然后成对成对的取出来进⾏⽐较，那么其实使⽤栈也是可以的。只要把队列原封不动的改成栈就可以了
#define MAXQUEUE 30
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

bool isSymmetric(struct TreeNode* root) {
  if (root == NULL) return true;

  front = tail = size = 0;

  enQueue(root->left);
  enQueue(root->right);
  while (!empty()) {
    struct TreeNode* left = deQueue();
    struct TreeNode* right = deQueue();
    // 左节点为空、右节点为空，此时说明是对称的
    if (left == NULL && right == NULL) continue;
    // 左右⼀个节点不为空，或者都不为空但数值不相同，返回false
    if (!left || !right || (left->val != right->val)) return false;
    enQueue(left->left);
    enQueue(right->right);
    enQueue(left->right);
    enQueue(right->left);
  }

  return true;
}
// @lc code=end
