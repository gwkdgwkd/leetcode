/*
给定一棵二叉搜索树，请找出其中第k大的节点的值。

示例1:
输入: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
输出: 4

示例2:
输入: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
输出: 4

限制：1 ≤ k ≤ 二叉搜索树元素个数
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int max;
int i;
void dfs(struct TreeNode* root, int k) {
  if (root == NULL) {
    return;
  }
  dfs(root->right, k);
  if (i++ == k) {
    max = root->val;
    return;
  }
  dfs(root->left, k);
}
int kthLargest(struct TreeNode* root, int k) {
  i = 1;
  max = INT_MIN;

  dfs(root, k);
  return max;
}