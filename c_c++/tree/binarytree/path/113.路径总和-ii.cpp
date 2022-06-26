/*
给你二叉树的根节点root和一个整数目标和targetSum，
找出所有从根节点到叶子节点路径总和等于给定目标和的路径。
叶子节点是指没有子节点的节点。

示例1：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：[[5,4,11,2],[5,8,4,5]]

示例2：
输入：root = [1,2,3], targetSum = 5
输出：[]

示例3：
输入：root = [1,2], targetSum = 0
输出：[]

提示：
树中节点总数在范围[0, 5000]内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
*/

// 剑指Offer34二叉树中和为某一值的路径

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

// 迭代
int **result;
int resultSize;
int *path;
int pathSize;
int *colSize;
// 如果需要搜索整颗⼆叉树，那么递归函数就不要返回值;
// 如果要搜索其中⼀条符合条件的路径，递归函数就需要返回值，
// 因为遇到符合条件的路径了就要及时返回，比如112。
void traversal(struct TreeNode *node, int targetSum) {
  if (!node) return;
  path[pathSize++] = node->val;
  targetSum -= node->val;
  if (!node->left && !node->right && targetSum == 0) {
    result[resultSize] = (int *)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize], path, sizeof(int) * pathSize);
    colSize[resultSize++] = pathSize;
    // pathSize--;
    // return;
  }

  traversal(node->left, targetSum);
  traversal(node->right, targetSum);
  pathSize--;

  return;
}
int **pathSum(struct TreeNode *root, int targetSum, int *returnSize,
              int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 2001);
  path = (int *)malloc(sizeof(int) * 2001);
  pathSize = resultSize = 0;
  colSize = (int *)malloc(sizeof(int) * 2001);
  traversal(root, targetSum);
  *returnSize = resultSize;
  *returnColumnSizes = colSize;
  return result;
}

class Solution {
 public:
  void traversal(TreeNode *node, int target, vector<vector<int>> &res,
                 vector<int> &path) {
    if (node == nullptr) {
      return;
    }

    path.emplace_back(node->val);
    target -= node->val;
    if (node->left == nullptr && node->right == nullptr && target == 0) {
      res.emplace_back(path);
      path.pop_back();
      return;
    }

    traversal(node->left, target, res, path);
    traversal(node->right, target, res, path);
    path.pop_back();
  }
  vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
    vector<vector<int>> res;
    if (root == nullptr) {
      return res;
    }

    vector<int> path;
    traversal(root, targetSum, res, path);
    return res;
  }
};
