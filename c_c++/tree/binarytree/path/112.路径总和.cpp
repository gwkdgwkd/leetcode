/*
给你二叉树的根节点root和一个表示目标和的整数targetSum。
判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和targetSum。
如果存在，返回true；否则，返回false。
叶子节点是指没有子节点的节点。

示例1：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
解释：等于目标和的根节点到叶节点路径如上图所示。

示例2：
输入：root = [1,2,3], targetSum = 5
输出：false
解释：树中存在两条根节点到叶子节点的路径：
(1 --> 2): 和为3
(1 --> 3): 和为4
不存在sum = 5的根节点到叶子节点的路径。

示例3：
输入：root = [], targetSum = 0
输出：false
解释：由于树是空的，所以不存在根节点到叶子节点的路径。

提示：
树中节点的数目在范围[0, 5000]内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
bool traversal(struct TreeNode* cur, int count) {
  if (cur == NULL) return false;
  if (cur->left == NULL && cur->right == NULL) {
    if (cur->val == count) {
      return true;
    } else {
      return false;
    }
  }

  bool left = false, right = false;
  if (cur->left) left = traversal(cur->left, count - cur->val);
  if (cur->right) right = traversal(cur->right, count - cur->val);

  return left || right;
}

// 递归
bool hasPathSum(struct TreeNode* root, int targetSum) {
  if (root == NULL) return false;

  if (!root->left && !root->right && root->val == targetSum) {
    return true;
  }

  return hasPathSum(root->left, targetSum - root->val) ||
         hasPathSum(root->right, targetSum - root->val);
}

class Solution {
 public:
  bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) {
      return false;
    }
    if (root->left == nullptr && root->right == nullptr &&
        root->val == targetSum) {
      return true;
    }

    return hasPathSum(root->left, targetSum - root->val) ||
           hasPathSum(root->right, targetSum - root->val);
  }
};
