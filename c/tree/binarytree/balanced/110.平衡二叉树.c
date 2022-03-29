/*
给定一个二叉树，判断它是否是高度平衡的二叉树。
本题中，一棵高度平衡二叉树定义为：
一个二叉树每个节点的左右两个子树的高度差的绝对值不超过1 。

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
树中的节点数在范围[0, 5000]内
-104 <= Node.val <= 104
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
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

// 迭代法，效率很低
