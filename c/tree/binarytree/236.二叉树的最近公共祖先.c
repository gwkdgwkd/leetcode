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

// 递归
// 前序遍历可以理解为是从上往下，而后序遍历是从下往上，就好比从p和q出发往上走，第一次相交的节点就是最近公共祖先
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  // base case
  if (root == NULL) return NULL;
  if (root == p || root == q) return root;

  struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
  struct TreeNode* right = lowestCommonAncestor(root->right, p, q);
  // 情况1，如果p和q都在以root为根的树中，那么left和right一定分别是p和q（从base case看出来的）。
  if (left != NULL && right != NULL) {
    return root;
  }
  // 情况2，如果p和q都不在以root为根的树中，直接返回null。
  if (left == NULL && right == NULL) {
    return NULL;
  }
  // 情况3，如果p和q只有一个存在于root为根的树中，函数返回该节点。
  return left == NULL ? right : left;
}
// @lc code=end
