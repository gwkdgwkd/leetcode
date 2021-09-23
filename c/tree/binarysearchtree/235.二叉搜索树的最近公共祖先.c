/*
 * @lc app=leetcode.cn id=235 lang=c
 *
 * [235] 二叉搜索树的最近公共祖先
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
// 普通⼆叉树求最近公共祖先需要使⽤回溯，从底向上来查找;
// ⼆叉搜索树就不⽤了，因为搜索树有序（相当于⾃带⽅向），那么只要从上向下遍历就可以了。
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  // 只要从上到下遍历的时候，root节点是数值在[p, q]区间中则说明该节点root就是最近公共祖先了。
  if (root->val < p->val && root->val < q->val)
    return lowestCommonAncestor(root->right, p, q);
  else if (root->val > p->val && root->val > q->val)
    return lowestCommonAncestor(root->left, p, q);
  else
    return root;
}

// 迭代
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  while (root) {
    if (root->val > q->val && root->val > p->val) {
      root = root->left;
    } else if (root->val < q->val && root->val < p->val) {
      root = root->right;
    } else {
      return root;
    }
  }
  return NULL;
}
// @lc code=end
