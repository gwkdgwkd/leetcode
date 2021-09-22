/*
 * @lc app=leetcode.cn id=617 lang=c
 *
 * [617] 合并二叉树
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
struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
  if (root1 == NULL) return root2;
  if (root2 == NULL) return root1;

  root1->val += root2->val;  // 前序遍历
  root1->left = mergeTrees(root1->left, root2->left);
  // root1->val += root2->val;  // 中序遍历也可以
  root1->right = mergeTrees(root1->right, root2->right);
  // root1->val += root2->val;  // 后序遍历也可以

  return root1;
}

// 迭代也可以，把两个树的节点同时加⼊队列进⾏⽐较

// @lc code=end
