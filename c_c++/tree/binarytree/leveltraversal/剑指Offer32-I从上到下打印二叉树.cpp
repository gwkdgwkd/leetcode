/*
从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

例如：
给定二叉树：[3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
返回：[3,9,20,15,7]

提示：节点总数 <= 1000
*/

// 与[102.二叉树的层序遍历]的区别是，本题的结果保存到一维数组中

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

#define MAXQUEUE 1000
struct TreeNode* queue[MAXQUEUE];
int tail, front, size;
int enQueue(struct TreeNode* node) {
  if ((tail + 1) % MAXQUEUE == front) {
    printf("full\n");
    return tail;
  }
  queue[tail % MAXQUEUE] = node;
  ++tail;
  ++size;
  return tail;
}
struct TreeNode* deQueue() {
  if (tail % MAXQUEUE == front) {
    printf("empty\n");
    return NULL;
  }
  struct TreeNode* ret = queue[front];
  front = (front + 1) % MAXQUEUE;
  --size;
  return ret;
}
bool empty() { return size == 0; }
int* levelOrder(struct TreeNode* root, int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * 1000);
  *returnSize = 0;
  tail = front = size = 0;
  if (root) {
    enQueue(root);
  }

  while (!empty()) {
    int n = size;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      res[(*returnSize)++] = node->val;
      if (node->left) enQueue(node->left);
      if (node->right) enQueue(node->right);
    }
  }

  return res;
}

class Solution {
 public:
  vector<int> levelOrder(TreeNode* root) {
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
        res.emplace_back(cur->val);
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