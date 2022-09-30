/*
从左向右遍历一个数组，
通过不断将其中的元素插入树中可以逐步地生成一棵二叉搜索树。
给定一个由不同节点组成的二叉搜索树root，
输出所有可能生成此树的数组。

示例1：
输入：root = [2,1,3]
输出：[[2,1,3],[2,3,1]]
解释：数组[2,1,3]、[2,3,1]均可以，
       2
      / \
     1   3

示例2：
输入：root = [4,1,null,null,3,2]
输出：[[4,1,3,2]

提示：
二叉搜索树中的节点数在[0, 1000]的范围内
1 <= 节点值 <= 10^6
用例保证符合要求的数组数量不超过5000
*/

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

#define MAX 1000000
int **res;
int *col;
int rescnt;
void Process(struct TreeNode **nodes, int *visited, int size, int *prev,
             int psize) {
  int cnt = 0;
  int new = false;
  for (int i = 0; i < size; i++) {
    if (visited[i] == 0) {
      new = true;
      visited[i] = 1;
      prev[psize] = nodes[i]->val;
      if (nodes[i]->left != NULL) {
        nodes[size + cnt] = nodes[i]->left;
        cnt++;
      }
      if (nodes[i]->right != NULL) {
        nodes[size + cnt] = nodes[i]->right;
        cnt++;
      }
      Process(nodes, visited, size + cnt, prev, psize + 1);
      visited[i] = 0;
      cnt = 0;
    }
  }

  if (new == false) {
    res[rescnt] = malloc(sizeof(int) * size);
    col[rescnt] = size;
    memcpy(res[rescnt++], prev, sizeof(int) * size);
  }
}
int **BSTSequences(struct TreeNode *root, int *returnSize,
                   int **returnColumnSizes) {
  struct TreeNode **nodes = malloc(sizeof(struct TreeNode *) * MAX);
  memset(nodes, 0, sizeof(struct TreeNode *) * MAX);

  int *visited = malloc(sizeof(int) * MAX);
  memset(visited, 0, sizeof(int) * MAX);
  int *prev = malloc(sizeof(int) * MAX);
  memset(prev, 0, sizeof(int) * MAX);
  col = malloc(sizeof(int) * MAX);
  memset(col, 0, sizeof(int) * MAX);
  res = malloc(sizeof(int *) * MAX);
  memset(res, 0, sizeof(int *) * MAX);

  rescnt = 0;
  nodes[0] = root;
  if (root != NULL) {
    Process(nodes, visited, 1, prev, 0);
  } else {
    rescnt = 1;
  }
  *returnColumnSizes = col;
  *returnSize = rescnt;
  return res;
}

class Solution {
 private:
  vector<vector<int>> res;
  vector<int> tmp;

 public:
  void dfs(deque<TreeNode *> dq) {
    if (dq.empty()) {
      res.push_back(tmp);
      return;
    }

    int size = dq.size();
    while (size--) {
      TreeNode *node = dq.front();
      dq.pop_front();

      tmp.push_back(node->val);

      if (node->left) dq.push_back(node->left);
      if (node->right) dq.push_back(node->right);

      dfs(dq);

      if (node->right) dq.pop_back();
      if (node->left) dq.pop_back();

      dq.push_back(node);
      tmp.pop_back();
    }
  }

  vector<vector<int>> BSTSequences(TreeNode *root) {
    if (root == nullptr) return {{}};

    deque<TreeNode *> dq;
    dq.push_back(root);
    dfs(dq);

    return res;
  }
};