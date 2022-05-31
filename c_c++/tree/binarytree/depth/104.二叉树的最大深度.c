/*
给定一个二叉树，找出其最大深度。
二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树[3,9,20,null,null,15,7]，
    3
   / \
  9  20
    /  \
   15   7
返回它的最大深度3。
*/

// 剑指Offer55-I二叉树的深度

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

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
