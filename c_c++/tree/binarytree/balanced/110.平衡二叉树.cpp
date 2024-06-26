/*
给定一个二叉树，判断它是否是高度平衡的二叉树。
本题中，一棵高度平衡二叉树定义为：
一个二叉树每个节点的左右两个子树的高度差的绝对值不超过1。

示例1：
输入：root = [3,9,20,null,null,15,7]
输出：true

示例2：
输入：root = [1,2,2,3,3,null,null,4,4]
输出：false

示例3：
输入：root = []
输出：true

提示：
树中的节点数在范围[0,5000]内
-10^4 <= Node.val <= 10^4
*/

// 剑指Offer55-II平衡二叉树
// 面试题0404检查平衡性

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 用递归实现，迭代效率很低
int getDepth(struct TreeNode* root) {
  if (root == NULL) {
    return 0;
  }
  int left = getDepth(root->left);
  if (left == -1) return -1;
  int right = getDepth(root->right);
  if (right == -1) return -1;
  return abs(left - right) > 1 ? -1 : 1 + fmax(left, right);
}
bool isBalanced(struct TreeNode* root) {
  return getDepth(root) == -1 ? false : true;
}

class Solution {
 public:
  int getDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    int left = getDepth(root->left);
    if (left == -1) return -1;
    int right = getDepth(root->right);
    if (right == -1) return -1;

    return abs(left - right) > 1 ? -1 : max(left, right) + 1;
  }
  bool isBalanced(TreeNode* root) {
    return getDepth(root) == -1 ? false : true;
  }
};