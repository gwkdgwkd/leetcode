/*
给定一棵二叉树的根节点root，请找出该二叉树中每一层的最大值。

示例1：
输入: root = [1,3,2,5,3,null,9]
输出: [1,3,9]

示例2：
输入: root = [1,2,3]
输出: [1,3]

提示：
二叉树的节点个数的范围是 [0,10^4]
-2^31 <= Node.val <= 2^31 - 1
*/

// 剑指OfferII044二叉树每层的最大值

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 迭代，BFS
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

// DFS
int* res;
int getDepth(struct TreeNode* root) {
  if (root == NULL) return 0;
  return fmax(getDepth(root->left), getDepth(root->right)) + 1;
}
void dfs(struct TreeNode* root, int depth) {
  if (root == NULL) {
    return;
  }
  res[depth] = fmax(res[depth], root->val);
  dfs(root->left, depth + 1);
  dfs(root->right, depth + 1);
}
int* largestValues(struct TreeNode* root, int* returnSize) {
  if (!root) {
    *returnSize = 0;
    return NULL;
  }
  int depth = getDepth(root);
  res = (int*)malloc(sizeof(int) * depth);
  for (int i = 0; i < depth; ++i) {
    res[i] = INT_MIN;
  }
  dfs(root, 0);
  *returnSize = depth;

  return res;
}
