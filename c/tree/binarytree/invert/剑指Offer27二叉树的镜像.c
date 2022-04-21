/*
请完成一个函数，输入一个二叉树，该函数输出它的镜像。
例如输入：
     4
   /   \
  2     7
 / \   / \
1   3 6   9
镜像输出：
     4
   /   \
  7     2
 / \   / \
9   6 3   1

示例1：
输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]

限制：0 <= 节点个数 <= 1000

注意：本题与226题相同
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct TreeNode* mirrorTree(struct TreeNode* root) {
  if (root == NULL) return root;

  mirrorTree(root->left);
  mirrorTree(root->right);

  struct TreeNode* tmp = root->left;
  root->left = root->right;
  root->right = tmp;

  return root;
}
