/*
给定一个二叉搜索树root和一个目标结果k，
如果BST中存在两个元素且它们的和等于给定的目标结果，则返回true。

示例1：
输入: root = [5,3,6,2,4,null,7], k = 9
输出: true

示例2：
输入: root = [5,3,6,2,4,null,7], k = 28
输出: false

提示:
二叉树的节点个数的范围是[1,10^4]
-10^4 <= Node.val <= 10^4
root为二叉搜索树
-10^5 <= k <= 10^5
*/

// 剑指OfferII056二叉搜索树中两个节点之和

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int nodes[10000];
int idx;
void dfs(struct TreeNode* root) {
  if (root == NULL) return;
  dfs(root->left);
  nodes[idx++] = root->val;
  dfs(root->right);
}
bool findTarget(struct TreeNode* root, int k) {
  idx = 0;
  dfs(root);

  int left = 0;
  int right = idx - 1;
  while (left < right) {
    int sum = nodes[left] + nodes[right];
    if (sum < k) {
      ++left;
    } else if (sum > k) {
      --right;
    } else {
      return true;
    }
  }

  return false;
}
