/*
路径被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。
同一个节点在一条路径序列中至多出现一次，该路径至少包含一个节点，且不一定经过根节点。
路径和是路径中各节点值的总和，给一个二叉树的根节点root，返回其最大路径和。

示例1：
输入：root = [1,2,3]
输出：6
解释：最优路径是2 -> 1 -> 3，路径和为2 + 1 + 3 = 6

示例2：
输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是15 -> 20 -> 7，路径和为15 + 20 + 7 = 42

提示：
树中节点数目范围是[1, 3 * 10^4]
-1000 <= Node.val <= 1000
*/

// 剑指OfferII051节点之和最大的路径

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int max;
int dfs(struct TreeNode* root) {
  if (root == NULL) {
    return 0;
  }

  int left = dfs(root->left);
  int right = dfs(root->right);

  // temp表示以当前节点为根的子树，能提供的最大路径和，为三者的最大值：
  // 1.只用根节点，走到当前节点不走了；
  // 2.根节点+左子树，继续走到左子树；
  // 3.根节点+右子树，继续走到右子树。
  int temp = fmax(fmax(left, right) + root->val, root->val);
  // 一个子树内部的最大路径和=左子树提供的最大路径和+根节点值+右子树提供的最大路径和
  // max为三者的最大值：max | temp | 左子树+根节点+右节点
  max = fmax(max, fmax(temp, left + right + root->val));

  return temp;
}
int maxPathSum(struct TreeNode* root) {
  max = INT_MIN;
  dfs(root);
  return max;
}

class Solution {
 public:
  int maxPathSum(TreeNode* root) {
    cal_max(root);
    return ans;
  }

  int cal_max(TreeNode* root) {
    // 如果为空节点，则它的贡献度为0：
    if (root == nullptr) return 0;
    // 递归求左右节点的贡献度：
    int left_val = max(0, cal_max(root->left));
    int right_val = max(0, cal_max(root->right));
    // 求当前节点的最大路径和：
    int temp = root->val + left_val + right_val;
    // 更新答案：
    ans = max(ans, temp);
    // 返回当前节点的最大贡献度(因为要左根或者右根加上根的父节点)：
    return root->val + max(left_val, right_val);
  }

 private:
  int ans = INT_MIN;
};
