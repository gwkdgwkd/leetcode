/*
输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

示例1:
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

示例2:
Input: preorder = [-1], inorder = [-1]
Output: [-1]

限制：0 <= 节点个数 <= 5000

注意：本题与105题重复
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};
struct TreeNode* build(int* preorder, int preStart, int preEnd, int* inorder,
                       int inStart, int inEnd) {
  if (preStart > preEnd) {
    return NULL;
  }
  int rootval = preorder[preStart];
  int index = 0;
  for (int i = inStart; i <= inEnd; ++i) {
    if (inorder[i] == rootval) {
      index = i;
      break;
    }
  }

  int leftSize = index - inStart;
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = rootval;
  root->left = build(preorder, preStart + 1, preStart + leftSize, inorder,
                     inStart, index - 1);
  root->right = build(preorder, preStart + leftSize + 1, preEnd, inorder,
                      index + 1, inEnd);
  return root;
}
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder,
                           int inorderSize) {
  return build(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1);
}
