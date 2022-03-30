/*
给定一个二叉搜索树的根节点root，和一个整数k，请你设计一个算法查找其中第k个最小元素（从1开始计数）

示例1：
输入：root = [3,1,4,null,2], k = 1
输出：1

示例2：
输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3

提示：
树中的节点数为n。
1 <= k <= n <= 104
0 <= Node.val <= 104

进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第k小的值，你将如何优化算法？
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int i;
int ret;
void find(struct TreeNode* root, int k) {
  if (!root) return;

  find(root->left, k);
  if (i++ == k) {
    ret = root->val;
  }
  find(root->right, k);

  return;
}
int kthSmallest(struct TreeNode* root, int k) {
  i = 1;
  find(root, k);
  return ret;
}