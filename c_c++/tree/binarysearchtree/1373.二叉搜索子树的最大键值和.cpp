/*
给你一棵以root为根的二叉树，请你返回任意二叉搜索子树的最大键值和。
二叉搜索树的定义如下：
1.任意节点的左子树中的键值都小于此节点的键值；
2.任意节点的右子树中的键值都大于此节点的键值；
3.任意节点的左子树和右子树都是二叉搜索树。

示例1：
输入：root = [1，4，3，2，4，2，5，null，null，
             null，null，null，null，4，6]
输出：20
解释：键值为3的子树是和最大的二叉搜索树。

示例2：
输入：root = [4，3，null，1，2]
输出：2
解释：键值为2的单节点子树是和最大的二叉搜索树。

示例3：
输入：root = [-4，-2，-5]
输出：0
解释：所有节点键值都为负数，和最大的二叉搜索树为空。

示例4：
输入：root = [2，1，3]
输出：6

示例5：
输入：root = [5，4，8，3，null，6，3]
输出：7

提示：
每棵树有1到40000个节点。
每个节点的键值在[-4*10^4，4*10^4]之间。
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int maxSum;
int* traverse(struct TreeNode* root) {
  int* res = (int*)malloc(sizeof(int) * 4);
  if (!root) {
    res[0] = 1;
    res[1] = INT_MAX;
    res[2] = INT_MIN;
    res[3] = 0;
    return res;
  }

  // 后序遍历，减小时间复杂度

  // 递归计算左右子树
  int* left = traverse(root->left);
  int* right = traverse(root->right);

  // 这个if在判断以root为根的二叉树是不是BST：
  if (left[0] == 1 && right[0] == 1 && root->val > left[2] &&
      root->val < right[1]) {
    // 以root为根的二叉树是BST：
    res[0] = 1;
    // 计算以root为根的这棵BST的最小值：
    res[1] = fmin(left[1], root->val);
    // 计算以root为根的这棵BST的最大值：
    res[2] = fmax(right[2], root->val);
    // 计算以root为根的这棵BST所有节点之和：
    res[3] = left[3] + right[3] + root->val;
    // 更新全局变量：
    maxSum = fmax(maxSum, res[3]);
  } else {
    // 以root为根的二叉树不是BST：
    res[0] = 0;
    // 其他的值都没必要计算了，因为用不到
  }

  return res;
}
int maxSumBST(struct TreeNode* root) {
  maxSum = 0;
  traverse(root);
  return maxSum;
}

// 时间比上面的快
#define MAX_VALUE 40001
int Max(int a, int b) { return a > b ? a : b; }
int Min(int a, int b) { return a < b ? a : b; }
int g_maxSum;
bool CalculateMaxSumBST(struct TreeNode* root, int* sum, int* max, int* min) {
  int leftSum = 0;
  int rightSum = 0;
  int leftMaxValue = -MAX_VALUE;
  int leftMinValue = MAX_VALUE;
  int rightMaxValue = -MAX_VALUE;
  int rightMinValue = MAX_VALUE;
  bool leftIsBSTTree = false;
  bool rightIsBSTTree = false;
  if (root == NULL) {
    return true;
  }

  leftIsBSTTree =
      CalculateMaxSumBST(root->left, &leftSum, &leftMaxValue, &leftMinValue);
  rightIsBSTTree = CalculateMaxSumBST(root->right, &rightSum, &rightMaxValue,
                                      &rightMinValue);
  if (leftIsBSTTree && rightIsBSTTree) {
    if (root->left != NULL) {
      if (root->val <= root->left->val) {
        return false;
      }
      if (root->val <= leftMaxValue) {
        return false;
      }
      *sum += leftSum;
    }
    *min = Min(root->val, leftMinValue);
    if (root->right != NULL) {
      if (root->val >= root->right->val) {
        return false;
      }
      if (root->val >= rightMinValue) {
        return false;
      }
      *sum += rightSum;
    }
    *max = Max(root->val, rightMaxValue);
    *sum += root->val;
    g_maxSum = Max(g_maxSum, *sum);
    return true;
  }
  return false;
}
int maxSumBST(struct TreeNode* root) {
  int sum = 0;
  int maxValue = -MAX_VALUE;
  int minValue = MAX_VALUE;
  g_maxSum = 0;
  CalculateMaxSumBST(root, &sum, &maxValue, &minValue);
  return g_maxSum;
}

class Solution {
 public:
  int res = INT_MIN;
  int maxSumBST(TreeNode* root) {
    dfs(root);
    return (res > 0 ? res : 0);
  }

  // 返回值: {min, max, sum, isBiSearchTree}
  vector<int> dfs(TreeNode* node) {
    if (!node) return {INT_MAX, INT_MIN, 0, true};
    auto leftVec = dfs(node->left);
    auto rightVec = dfs(node->right);
    // 更新当前子树的和
    int sum = leftVec[2] + rightVec[2] + node->val;
    bool isBi = false;
    // 大于左子树最大值，说明比左子树所有元素都大
    // 小于右子树最小值，说明比右子树所有元素都小
    if (node->val > leftVec[1] && node->val < rightVec[0]) {
      // 左子树和右子树是二叉搜索树
      if (leftVec[3] && rightVec[3]) {
        isBi = true;
      }
    }
    if (isBi) res = max(res, sum);
    // 更新当前子树的最大值和最小值
    int maxVal = max(max(leftVec[1], rightVec[1]), node->val);
    int minVal = min(min(leftVec[0], rightVec[0]), node->val);
    return {minVal, maxVal, sum, isBi};
  }
};