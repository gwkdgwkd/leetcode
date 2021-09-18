/*
 * @lc app=leetcode.cn id=112 lang=c
 *
 * [112] 路径总和
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

// 递归1
bool traversal(struct TreeNode* cur, int count) {
  printf("%d\n", count);
  if (cur == NULL) return false;
  if (cur->left == NULL && cur->right == NULL) {
    if (cur->val == count) {
      return true;
    } else {
      return false;
    }
  }

  bool left = false, right = false;
  if (cur->left) left = traversal(cur->left, count - cur->val);
  if (cur->right) right = traversal(cur->right, count - cur->val);

  return left || right;
}

// 递归2
bool traversal(struct TreeNode* cur, int count) {
  if (cur == NULL) return false;
  if (!cur->left && !cur->right && cur->val == count) {
    return true;
  }
  return traversal(cur->left, count - cur->val) ||
         traversal(cur->right, count - cur->val);
}

bool hasPathSum(struct TreeNode* root, int targetSum) {
  return traversal(root, targetSum);
}

// @lc code=end
