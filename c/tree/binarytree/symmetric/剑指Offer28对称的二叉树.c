/*
请实现一个函数，用来判断一棵二叉树是不是对称的。
如果一棵二叉树和它的镜像一样，那么它是对称的。
例如，二叉树[1,2,2,3,4,4,3]是对称的。
    1
   / \
  2   2
 / \ / \
3  4 4  3
但是下面这个[1,2,2,null,3,null,3]则不是镜像对称的:
    1
   / \
  2   2
   \   \
   3    3

示例1：
输入：root = [1,2,2,3,4,4,3]
输出：true

示例2：
输入：root = [1,2,2,null,3,null,3]
输出：false

限制：0 <= 节点个数 <= 1000

注意：本题与101题相同
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

bool dfs(struct TreeNode* left, struct TreeNode* right) {
  if (left == NULL && right == NULL) return true;
  if (left == NULL && right) return false;
  if (right == NULL && left) return false;
  if (left && right && left->val != right->val) return false;
  return dfs(left->left, right->right) && dfs(left->right, right->left);
}
bool isSymmetric(struct TreeNode* root) {
  if (root == NULL) return true;
  return dfs(root->left, root->right);
}