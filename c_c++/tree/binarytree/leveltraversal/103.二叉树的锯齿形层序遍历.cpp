/*
给你二叉树的根节点root，返回其节点值的 锯齿形层序遍历。
即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行。

示例1：
输入：root = [3,9,20,null,null,15,7]
输出：[[3],[20,9],[15,7]]

示例2：
输入：root = [1]
输出：[[1]]

示例3：
输入：root = []
输出：[]

提示：
树中节点数目在范围[0, 2000]内
-100 <= Node.val <= 100
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

#define MAXQUEUE 2000
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

void reverse(int* nums, int left, int right) {
  while (left < right) {
    int temp = nums[left];
    nums[left] = nums[right];
    nums[right] = temp;
    ++left;
    --right;
  }
}
int** zigzagLevelOrder(struct TreeNode* root, int* returnSize,
                       int** returnColumnSizes) {
  int** result = (int**)malloc(sizeof(int*) * MAXQUEUE);
  (*returnColumnSizes) = (int*)malloc(sizeof(int) * MAXQUEUE);
  (*returnSize) = 0;

  front = tail = size = 0;
  if (root != NULL) {
    enQueue(root);
  }

  while (!empty()) {
    int* arr = (int*)malloc(sizeof(int) * (size));
    result[*returnSize] = arr;
    (*returnColumnSizes)[*returnSize] = size;
    int n = size;
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

  // 奇数层反转，第一层是0，不翻转
  for (int i = 0; i < *returnSize; ++i) {
    if (i % 2) {
      reverse(result[i], 0, (*returnColumnSizes)[i] - 1);
    }
  }

  return result;
}

// 剑指Offer32-III从上到下打印二叉树III
// int** levelOrder(struct TreeNode* root, int* returnSize,
//                  int** returnColumnSizes)

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
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    bfs(root, 0, res);

    for (int i = 0; i < res.size(); ++i) {
      if (i % 2) {
        for (int left = 0, right = res[i].size() - 1; left < right;
             ++left, --right) {
          int temp = res[i][left];
          res[i][left] = res[i][right];
          res[i][right] = temp;
        }
      }
    }
    return res;
  }
};