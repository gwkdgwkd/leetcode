/*
给定两个整数数组inorder和postorder，其中inorder是二叉树的中序遍历，
postorder是同一棵树的后序遍历，请你构造并返回这颗二叉树。

示例1:
输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
输出：[3,9,20,null,null,15,7]

示例2:
输入：inorder = [-1], postorder = [-1]
输出：[-1]

提示:
1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder和postorder都由不同的值组成
postorder中每一个值都在inorder中
inorder保证是树的中序遍历
postorder保证是树的后序遍历
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* traversal(int* inorder, int inorderStart, int inorderSize,
                           int* postorder, int postorderStart,
                           int postorderSize) {
  if (postorderStart == postorderSize) return NULL;

  int rootValue = postorder[postorderSize - 1];
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = rootValue;
  if (postorderSize - postorderStart == 1) {
    root->left = NULL;
    root->right = NULL;
    return root;
  }

  int delimiter;
  for (delimiter = inorderStart; delimiter < inorderSize; ++delimiter) {
    if (inorder[delimiter] == rootValue) {
      break;
    }
  }

  root->left =
      traversal(inorder, inorderStart, delimiter, postorder, postorderStart,
                postorderStart + delimiter - inorderStart);
  root->right =
      traversal(inorder, delimiter + 1, inorderSize, postorder,
                postorderStart + delimiter - inorderStart, postorderSize - 1);

  return root;
}
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder,
                           int postorderSize) {
  if (inorderSize == 0 || postorderSize == 0) {
    return NULL;
  }

  return traversal(inorder, 0, inorderSize, postorder, 0, postorderSize);
}

// 递归
struct TreeNode* build(int* inorder, int inStart, int inEnd, int* postorder,
                       int postStart, int postEnd) {
  if (inEnd < inStart) {
    return NULL;
  }

  int rootVal = postorder[postEnd];
  int index = 0;
  for (int i = inStart; i <= inEnd; ++i) {
    if (inorder[i] == rootVal) {
      index = i;
      break;
    }
  }

  int leftSize = index - inStart;
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = rootVal;
  root->left = build(inorder, inStart, inStart + leftSize - 1, postorder,
                     postStart, postStart + leftSize - 1);
  root->right = build(inorder, inStart + leftSize + 1, inEnd, postorder,
                      postStart + leftSize, postEnd - 1);

  return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder,
                           int postorderSize) {
  return build(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);
}
