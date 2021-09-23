/*
 * @lc app=leetcode.cn id=236 lang=c
 *
 * [236] 二叉树的最近公共祖先
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
// 递归
// 1. 求最⼩公共祖先，需要从底向上遍历，那么⼆叉树，只能通过后序遍历（即：回溯）实现从低向上的遍历⽅式。
// 2. 在回溯的过程中，必然要遍历整颗⼆叉树，即使已经找到结果了，依然要把其他节点遍历完，因为要使⽤递归函数的返回值（也就是代码中的left和right）做逻辑判断。
// 3. 要理解如果返回值left为空，right不为空为什么要返回right，为什么可以⽤返回right传给上⼀层结果。
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  if (root == p || root == q || root == NULL) return root;
  struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
  struct TreeNode* right = lowestCommonAncestor(root->right, p, q);

  if (left && right) return root;
  if (left) return left;  // (left && !right)
  return right;           // (!left && right)
}
// @lc code=end
