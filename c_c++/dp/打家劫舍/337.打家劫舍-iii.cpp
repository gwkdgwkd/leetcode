/*
小偷又发现了一个新的可行窃的地区，这个地区只有一个入口，我们称之为root。
除了root之外，每栋房子有且只有一个父房子与之相连。
一番侦察之后，聪明的小偷意识到这个地方的所有房屋的排列类似于一棵二叉树。
如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。
给定二叉树的root，返回在不触动警报的情况下，小偷能够盗取的最高金额。

示例1：
输入：root = [3,2,3,null,3,null,1]
输出：7
解释：小偷一晚能够盗取的最高金额3 + 3 + 1 = 7

示例2：
输入：root = [3,4,5,1,3,null,1]
输出：9
解释：小偷一晚能够盗取的最高金额4 + 5 = 9

提示：
树的节点数在[1, 10^4]范围内
0 <= Node.val <= 10^4
*/

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

// 官方题解
struct SubtreeStatus {
  int selected;
  int notSelected;
};
struct SubtreeStatus dfs(struct TreeNode *node) {
  if (!node) {
    return (struct SubtreeStatus){0, 0};
  }
  struct SubtreeStatus l = dfs(node->left);
  struct SubtreeStatus r = dfs(node->right);
  int selected = node->val + l.notSelected + r.notSelected;
  int notSelected =
      fmax(l.selected, l.notSelected) + fmax(r.selected, r.notSelected);
  return (struct SubtreeStatus){selected, notSelected};
}
// 时间复杂度：O(n)每个节点只遍历了⼀次
// 空间复杂度：O(logn)算上递推系统栈的空间
int rob(struct TreeNode *root) {
  struct SubtreeStatus rootStatus = dfs(root);
  return fmax(rootStatus.selected, rootStatus.notSelected);
}
