/*
 * @lc app=leetcode.cn id=654 lang=c
 *
 * [654] 最大二叉树
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

struct TreeNode* traversal(int* nums, int start, int end) {
  if (start == end) return NULL;

  int delimiter;
  int max = INT_MIN;
  for (int i = start; i < end; ++i) {
    if (nums[i] > max) {
      max = nums[i];
      delimiter = i;
    }
  }
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = max;
  if (start + 1 == end) {
    root->left = NULL;
    root->right = NULL;
    return root;
  }

  root->left = traversal(nums, start, delimiter);
  root->right = traversal(nums, delimiter + 1, end);

  return root;
}
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
  if (numsSize == 0) return NULL;

  return traversal(nums, 0, numsSize);
}

struct TreeNode* build(int* nums, int lo, int hi) {
  if (lo > hi) {
    return NULL;
  }

  int index = -1, maxVal = INT_MIN;
  for (int i = lo; i <= hi; ++i) {
    if (maxVal < nums[i]) {
      maxVal = nums[i];
      index = i;
    }
  }

  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = maxVal;
  root->left = build(nums, lo, index - 1);
  root->right = build(nums, index + 1, hi);

  return root;
}
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
  return build(nums, 0, numsSize - 1);
}
// @lc code=end
