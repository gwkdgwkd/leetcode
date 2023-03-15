/*
给一个二叉树的根节点root，树中每个节点都存放有一个0到9之间的数字。
每条从根节点到叶节点的路径都代表一个数字：
例如，从根节点到叶节点的路径1 -> 2 -> 3表示数字123。
计算从根节点到叶节点生成的所有数字之和，叶节点是指没有子节点的节点。

示例1：
输入：root = [1,2,3]
输出：25
解释：
从根到叶子节点路径1->2代表数字12
从根到叶子节点路径1->3代表数字13
因此，数字总和= 12 + 13 = 25

示例2：
输入：root = [4,9,0,5,1]
输出：1026
解释：
从根到叶子节点路径4->9->5代表数字495
从根到叶子节点路径4->9->1代表数字491
从根到叶子节点路径4->0代表数字40
因此，数字总和= 495 + 491 + 40 = 1026

提示：
树中节点的数目在范围[1, 1000]内
0 <= Node.val <= 9
树的深度不超过10
*/

// 剑指OfferII049从根节点到叶节点的路径数字之和

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 我写的
int res;
void dfs(struct TreeNode* root, int val) {
  if (root->left == NULL && root->right == NULL) {
    res += val * 10 + root->val;
  }
  if (root->left) dfs(root->left, val * 10 + root->val);
  if (root->right) dfs(root->right, val * 10 + root->val);
}
int sumNumbers(struct TreeNode* root) {
  res = 0;
  dfs(root, 0);
  return res;
}

// 官方题解
int dfs(struct TreeNode* root, int prevSum) {
  if (root == NULL) {
    return 0;
  }
  int sum = prevSum * 10 + root->val;
  if (root->left == NULL && root->right == NULL) {
    return sum;
  } else {
    return dfs(root->left, sum) + dfs(root->right, sum);
  }
}
int sumNumbers(struct TreeNode* root) { return dfs(root, 0); }

class Solution {
 public:
  int dfs(TreeNode* root, int prevSum) {
    if (root == nullptr) {
      return 0;
    }
    int sum = prevSum * 10 + root->val;
    if (root->left == nullptr && root->right == nullptr) {
      return sum;
    } else {
      return dfs(root->left, sum) + dfs(root->right, sum);
    }
  }
  int sumNumbers(TreeNode* root) { return dfs(root, 0); }
};