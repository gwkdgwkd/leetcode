/*
给定一个二叉树的根节点root，和一个整数targetSum，
求该二叉树里节点值之和等于targetSum的路径的数目。
路径不需要从根节点开始，也不需要在叶子节点结束，
但是路径方向必须是向下的（只能从父节点到子节点）。

示例1：
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于8的路径有3条。

示例2：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3

提示:
二叉树的节点个数的范围是[0,1000]
-10^9 <= Node.val <= 10^9
-1000 <= targetSum <= 1000
*/

// 剑指OfferII050向下的路径节点之和

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// DFS
int dfs(struct TreeNode* root, long sum) {
  if (NULL == root) {
    return 0;
  }

  return (0 == sum - root->val ? 1 : 0) + dfs(root->left, sum - root->val) +
         dfs(root->right, sum - root->val);
}
int pathSum(struct TreeNode* root, int sum) {
  if (NULL == root) {
    return 0;
  }

  return dfs(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}

// 前缀和
#define NODE_NUM 1001
int g_cnt = 0;
void dfs(struct TreeNode* root, long* presum, int index, int targetSum) {
  if (root == NULL) return;
  presum[index + 1] = presum[index] + root->val;
  for (int i = 0; i <= index; i++) {
    if (presum[index + 1] - presum[i] == targetSum) {
      g_cnt++;
    }
  }

  dfs(root->left, presum, index + 1, targetSum);
  dfs(root->right, presum, index + 1, targetSum);
}
int pathSum(struct TreeNode* root, int targetSum) {
  long presum[NODE_NUM] = {0};
  int index = 0;
  g_cnt = 0;

  dfs(root, presum, index, targetSum);
  return g_cnt;
}