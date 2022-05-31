/*
给你一个二叉树的根节点root，按任意顺序，返回所有从根节点到叶子节点的路径。
叶子节点是指没有子节点的节点。

示例1：
输入：root = [1,2,3,null,5]
输出：["1->2->5","1->3"]

示例2：
输入：root = [1]
输出：["1"]

提示：
树中节点的数目在范围[1, 100]内
-100 <= Node.val <= 100
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

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
