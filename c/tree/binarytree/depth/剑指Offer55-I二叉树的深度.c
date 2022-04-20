/*
输入一棵二叉树的根节点，求该树的深度。
从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

例如：
给定二叉树[3,9,20,null,null,15,7]，
    3
   / \
  9  20
    /  \
   15   7
返回它的最大深度3。

提示：节点总数 <= 10000

注意：本题与主站104题相同
*/

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

int maxDepth(struct TreeNode *root) {
  if (root == NULL) {
    return 0;
  }
  int left = maxDepth(root->left);
  int right = maxDepth(root->right);
  return fmax(left, right) + 1;
}