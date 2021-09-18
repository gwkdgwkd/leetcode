/*
 * @lc app=leetcode.cn id=113 lang=c
 *
 * [113] 路径总和 II
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 迭代
int **result;
int resultSize;
int *path;
int pathSize;
int *colSize;
// 如果需要搜索整颗⼆叉树，那么递归函数就不要返回值;
// 如果要搜索其中⼀条符合条件的路径，递归函数就需要返回值，因为遇到符合条件的路径了就要及时返回。比如112。
void traversal(struct TreeNode *node, int targetSum) {
  if (!node) return;
  path[pathSize++] = node->val;
  targetSum -= node->val;
  if (!node->left && !node->right && targetSum == 0) {
    result[resultSize] = (int *)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize], path, sizeof(int) * pathSize);
    colSize[resultSize++] = pathSize;
    // pathSize--;
    // return;
  }

  traversal(node->left, targetSum);
  traversal(node->right, targetSum);
  pathSize--;

  return;
}
int **pathSum(struct TreeNode *root, int targetSum, int *returnSize,
              int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 2001);
  path = (int *)malloc(sizeof(int) * 2001);
  pathSize = resultSize = 0;
  colSize = (int *)malloc(sizeof(int) * 2001);
  traversal(root, targetSum);
  *returnSize = resultSize;
  *returnColumnSizes = colSize;
  return result;
}
// @lc code=end
