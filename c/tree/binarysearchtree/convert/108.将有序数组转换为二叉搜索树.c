/*
 * @lc app=leetcode.cn id=108 lang=c
 *
 * [108] 将有序数组转换为二叉搜索树
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
struct TreeNode* convert(int* nums, int left, int right) {
  if (left > right) return NULL;
  struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  // 这么写其实有⼀个问题，就是数值越界，例如left和right都是最⼤int，这么操作就越界了，在⼆分法中尤其需要注意！
  // int mid = (left + right) / 2;
  int mid = left + (right - left) / 2;
  node->val = nums[mid];
  node->left = convert(nums, left, mid - 1);
  node->right = convert(nums, mid + 1, right);
  return node;
}
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
  return convert(nums, 0, numsSize - 1);
}

// 迭代法可以通过三个队列来模拟，⼀个队列放遍历的节点，⼀个队列放左区间下表，⼀个队列放右区间下表。
// @lc code=end
