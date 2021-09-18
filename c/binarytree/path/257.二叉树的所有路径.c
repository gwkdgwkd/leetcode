/*
 * @lc app=leetcode.cn id=257 lang=c
 *
 * [257] 二叉树的所有路径
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
char** result;
int resultSize;
int* path;
int pathSize;
void traversal(struct TreeNode* root) {
  path[pathSize++] = root->val;
  if (root->left == NULL && root->right == NULL) {
    int len = 100;
    result[resultSize] = (char*)malloc(sizeof(char) * (len));
    memset(result[resultSize], 0, len);
    for (int i = 0; i < pathSize; ++i) {
      if (i > 0) {
        sprintf(result[resultSize] + strlen(result[resultSize]), "->%d",
                path[i]);
      } else {
        sprintf(result[resultSize] + strlen(result[resultSize]), "%d", path[i]);
      }
    }
    result[resultSize++][len - 1] = 0;
    return;
  }

  if (root->left) {
    traversal(root->left);
    pathSize--;  // 回溯
  }

  if (root->right) {
    traversal(root->right);
    pathSize--;  // 回溯
  }

  return;
}
char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
  result = (char**)malloc(sizeof(char*) * 500);
  path = (int*)malloc(sizeof(int) * 100);
  resultSize = pathSize = 0;
  if (root == NULL) {
    return result;
  }
  traversal(root);
  *returnSize = resultSize;

  return result;
}
// @lc code=end
