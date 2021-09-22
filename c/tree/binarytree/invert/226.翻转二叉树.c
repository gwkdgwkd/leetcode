/*
 * @lc app=leetcode.cn id=226 lang=c
 *
 * [226] 翻转二叉树
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

// 只要把每⼀个节点的左右孩⼦翻转⼀下，就可以达到整体翻转的效果
// 使⽤前序遍历和后序遍历都可以，唯独中序遍历不⾏，因为中序遍历会把某些节点的左右孩⼦翻转了两次！
// 那么层序遍历可以不可以呢？依然可以的！只要把每⼀个节点的左右孩⼦翻转⼀下的遍历⽅式都是可以的！

// 递归
struct TreeNode* invertTree(struct TreeNode* root) {
  if (root == NULL) {
    return NULL;
  }

  struct TreeNode* temp = root->left;
  root->left = root->right;
  root->right = temp;

  invertTree(root->left);
  invertTree(root->right);

  return root;
}

// 迭代，前序遍历
int idx;
struct TreeNode* stack[50];
void push(struct TreeNode* node) { stack[idx++] = node; }
struct TreeNode* top() {
  return stack[idx - 1];
}
void pop() { --idx; }
int empty() { return idx == 0 ? 1 : 0; }
struct TreeNode* invertTree(struct TreeNode* root) {
  if (root == NULL) {
    return NULL;
  }
  push(root);

  while (!empty()) {
    struct TreeNode* node = top();
    pop();
    struct TreeNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
    if (node->right) {
      push(node->right);
    }
    if (node->left) {
      push(node->left);
    }
  }

  return root;
}

// 迭代，⼴度优先遍历
#define MAXQUEUE 50
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
struct TreeNode* invertTree(struct TreeNode* root) {
  front = tail = size = 0;
  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      struct TreeNode* temp = node->left;
      node->left = node->right;
      node->right = temp;
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
