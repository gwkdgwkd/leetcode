/*
给你一棵二叉搜索树的root，请你按中序遍历将其重新排列为一棵递增顺序搜索树，
使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。

示例1：
输入：root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

示例2：
输入：root = [5,1,7]
输出：[1,null,5,null,7]

提示：
树中节点数的取值范围是 [1, 100]
0 <= Node.val <= 1000
*/

// 剑指OfferII052展平二叉搜索树

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct TreeNode* nodes[100];
int idx;
void inorder(struct TreeNode* root) {
  if (root == NULL) return;

  inorder(root->left);
  nodes[idx++] = root;
  inorder(root->right);
}
struct TreeNode* increasingBST(struct TreeNode* root) {
  memset(nodes, 0, sizeof(nodes));
  idx = 0;
  inorder(root);

  for (int i = 0; i < idx - 1; ++i) {
    nodes[i]->right = nodes[i + 1];
    nodes[i]->left = NULL;
  }
  nodes[idx - 1]->right = NULL;
  nodes[idx - 1]->left = NULL;

  return nodes[0];
}