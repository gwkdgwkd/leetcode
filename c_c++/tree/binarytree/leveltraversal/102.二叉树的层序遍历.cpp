/*
给二叉树的根节点root，返回其节点值的层序遍历，即逐层从左到右访问所有节点。

示例1：
输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]

示例2：
输入：root = [1]
输出：[[1]]

示例3：
输入：root = []
输出：[]

提示：
树中节点数目在范围[0, 2000]内
-1000 <= Node.val <= 1000
*/

// 剑指Offer32-II从上到下打印二叉树II

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 迭代
#define MAXSIZE 1500
int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes) {
  int** result = (int**)malloc(sizeof(int*) * MAXSIZE);
  for (int i = 0; i < MAXSIZE; ++i) {
    result[i] = (int*)malloc(sizeof(int) * MAXSIZE);
  }
  *returnColumnSizes = (int*)calloc(sizeof(int), MAXSIZE);
  *returnSize = 0;

  struct TreeNode* queue[MAXSIZE];
  int front = 0;
  int tail = 0;

  if (root) queue[tail++] = root;
  while (tail > front) {
    int n = tail - front;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = queue[front++];
      result[*returnSize][(*returnColumnSizes)[*returnSize]++] = node->val;
      if (node->left) queue[tail++] = node->left;
      if (node->right) queue[tail++] = node->right;
    }
    (*returnSize)++;
  }

  return result;
}

// 迭代
#define MAXQUEUE 200
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
int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes) {
  int** result = (int**)malloc(sizeof(int*) * 10000);
  *returnSize = 0;
  *returnColumnSizes = (int*)malloc(sizeof(int) * 10000);
  front = tail = size = 0;

  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    (*returnColumnSizes)[*returnSize] = n;
    result[*returnSize] = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      result[*returnSize][i] = node->val;
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
    (*returnSize)++;
  }

  return result;
}

// 递归
#define MAXSIZE 1000
int** result;
int resultSize;
void bfs(struct TreeNode* node, int level, int** returnColumnSizes) {
  if (node == NULL) {
    return;
  }

  result[level][(*returnColumnSizes)[level]++] = node->val;
  if (level + 1 > resultSize) {
    resultSize = level + 1;
  }
  bfs(node->left, level + 1, returnColumnSizes);
  bfs(node->right, level + 1, returnColumnSizes);
}
int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes) {
  result = (int**)malloc(sizeof(int*) * MAXSIZE);
  for (int i = 0; i < MAXSIZE; ++i) {
    result[i] = (int*)malloc(sizeof(int) * MAXSIZE);
  }
  resultSize = 0;
  *returnColumnSizes = (int*)calloc(sizeof(int), MAXSIZE);
  bfs(root, 0, returnColumnSizes);
  *returnSize = resultSize;

  return result;
}

// 递归
class Solution {
 public:
  void bfs(TreeNode* root, int level, vector<vector<int>>& res) {
    if (root == nullptr) {
      return;
    }

    if (level + 1 > res.size()) {
      res.emplace_back(vector<int>());
    }
    res[level].emplace_back(root->val);
    bfs(root->left, level + 1, res);
    bfs(root->right, level + 1, res);
  }
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    bfs(root, 0, res);
    return res;
  }
};

// 迭代
class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (root == nullptr) {
      return res;
    }

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
      int n = q.size();
      vector<int> v(n);
      for (int i = 0; i < n; ++i) {
        TreeNode* cur = q.front();
        q.pop();
        v[i] = cur->val;
        if (cur->left) {
          q.push(cur->left);
        }

        if (cur->right) {
          q.push(cur->right);
        }
      }
      res.emplace_back(v);
    }
    return res;
  }
};
