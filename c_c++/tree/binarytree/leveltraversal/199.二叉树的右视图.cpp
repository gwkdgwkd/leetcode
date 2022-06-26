/*
给定一个二叉树的根节点root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例1:
输入: [1,2,3,null,5,null,4]
输出: [1,3,4]

示例2:
输入: [1,null,3]
输出: [1,3]

示例3:
输入: []
输出: []

提示:
二叉树的节点个数的范围是[0,100]
-100 <= Node.val <= 100
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 迭代
#define MAXQUEUE 100
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
int* rightSideView(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  front = tail = size = 0;

  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      if (i == n - 1) {
        result[(*returnSize)++] = node->val;
      }
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
  }

  return result;
}

// 剑指OfferII046二叉树的右侧视图
#define MAX 100
int* rightSideView(struct TreeNode* root, int* returnSize) {
  *returnSize = 0;
  if (root == NULL) {
    return NULL;
  }

  int* res = (int*)malloc(sizeof(int) * MAX);

  struct TreeNode* queue[MAX] = {0};
  int front = 0;
  int tail = 0;

  queue[tail++] = root;
  while (front < tail) {
    int n = tail - front;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = queue[front++];
      if (i == n - 1) {
        res[(*returnSize)++] = node->val;
      }
      if (node->left) queue[tail++] = node->left;
      if (node->right) queue[tail++] = node->right;
    }
  }

  return res;
}

class Solution {
 public:
  vector<int> rightSideView(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) {
      return res;
    }

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
      int n = q.size();
      for (int i = 0; i < n; ++i) {
        TreeNode* cur = q.front();
        q.pop();
        if (i == n - 1) {
          res.emplace_back(cur->val);
        }
        if (cur->left) {
          q.push(cur->left);
        }

        if (cur->right) {
          q.push(cur->right);
        }
      }
    }
    return res;
  }
};