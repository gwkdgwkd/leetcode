/*
给定二叉搜索树（BST）的根节点root和一个整数值val。
你需要在 BST 中找到节点值等于val的节点。返回以该节点为根的子树。如果节点不存在，则返回null。

示例1:
输入：root = [4,2,7,1,3], val = 2
输出：[2,1,3]

Example2:
输入：root = [4,2,7,1,3], val = 5
输出：[]

提示：
数中节点数在[1, 5000]范围内
1 <= Node.val <= 107
root是二叉搜索树
1 <= val <= 107
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* searchBST(struct TreeNode* root, int val) {
  if (root == NULL) return root;

  if (root->val > val) {
    return searchBST(root->left, val);
  } else if (root->val < val) {
    return searchBST(root->right, val);
  }
  return root;
}

// 递归
struct TreeNode* searchBST(struct TreeNode* root, int val) {
  if (!root) return root;

  if (root->val == val) return root;
  if (root->left && root->val > val) return searchBST(root->left, val);
  if (root->right && root->val < val) return searchBST(root->right, val);

  return NULL;
}

// 迭代
struct TreeNode* searchBST(struct TreeNode* root, int val) {
  while (root) {
    if (root->val > val)
      root = root->left;
    else if (root->val < val)
      root = root->right;
    else
      return root;
  }
  return NULL;
}
