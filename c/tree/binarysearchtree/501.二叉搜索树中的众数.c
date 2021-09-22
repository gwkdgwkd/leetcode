/*
 * @lc app=leetcode.cn id=501 lang=c
 *
 * [501] 二叉搜索树中的众数
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 递归
int* result;
int resultSize;
int count;
int maxCount;
struct TreeNode* pre;
void traversal(struct TreeNode* root) {
  if (root == NULL) return;

  traversal(root->left);
  if (pre == NULL) {  // 第一个节点
    count = 1;
  } else if (root->val == pre->val) {  // 与当前值一样
    count++;
  } else {  // 与当前值不一样
    count = 1;
  }
  pre = root;
  if (count == maxCount) {  // 有多个众数
    result[resultSize++] = root->val;
  }
  if (count > maxCount) {
    maxCount = count;
    resultSize = 0;
    result[resultSize++] = root->val;
  }
  traversal(root->right);
  return;
}
int* findMode(struct TreeNode* root, int* returnSize) {
  result = (int*)malloc(sizeof(int) * 10000);
  count = maxCount = resultSize = 0;
  pre == NULL;
  traversal(root);
  *returnSize = resultSize;
  return result;
}
// @lc code=end
