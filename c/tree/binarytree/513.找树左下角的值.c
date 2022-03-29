/*
给定一个二叉树的根节点root，请找出该二叉树的最底层最左边节点的值。
假设二叉树中至少有一个节点。

示例1:
输入: root = [2,1,3]
输出: 1

示例2:
输入: [1,2,3,4,null,5,6,null,null,7]
输出: 7

提示:
二叉树的节点个数的范围是[1,104]
-231 <= Node.val <= 231 - 1 
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

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
