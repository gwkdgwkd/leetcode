/*
给定两个整数数组preorder和inorder，其中preorder是二叉树的先序遍历，
inorder是同一棵树的中序遍历，请构造二叉树并返回其根节点。

示例1：
输入：preorder = [3,9,20,15,7]，inorder = [9,3,15,20,7]
输出：[3,9,20,null,null,15,7]

示例2：
输入：preorder = [-1], inorder = [-1]
输出：[-1]

提示：
1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder和inorder均无重复元素
inorder均出现在preorder
preorder保证为二叉树的前序遍历序列
inorder保证为二叉树的中序遍历序列
*/

// 剑指Offer07重建二叉树

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* traversal(int* preorder, int preorderStart, int preorderSize,
                           int* inorder, int inorderStart, int inorderSize) {
  if (preorderStart == preorderSize) return NULL;

  int rootValue = preorder[preorderStart];
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = rootValue;
  if (preorderSize - preorderStart == 1) {
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

  root->left = traversal(preorder, preorderStart + 1,
                         preorderStart + delimiter - inorderStart + 1, inorder,
                         inorderStart, delimiter);
  root->right =
      traversal(preorder, preorderStart + 1 + delimiter - inorderStart,
                preorderSize, inorder, delimiter + 1, inorderSize);

  return root;
}
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder,
                           int inorderSize) {
  if (preorderSize == 0 || inorderSize == 0) {
    return NULL;
  }

  return traversal(preorder, 0, preorderSize, inorder, 0, inorderSize);
}

// 递归
struct TreeNode* build(int* preorder, int preStart, int preEnd, int* inorder,
                       int inStart, int inEnd) {
  if (preEnd < preStart) {
    return NULL;
  }

  int rootVal = preorder[preStart];
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

class Solution {
 public:
  TreeNode* buildTree(vector<int>& preorder, int pleft, int pright,
                      vector<int>& inorder, int ileft, int iright) {
    if (pleft > pright) {
      return nullptr;
    }
    int rootVal = preorder[pleft];
    int index = 0;
    for (int i = ileft; i <= iright; ++i) {
      if (inorder[i] == rootVal) {
        index = i;
        break;
      }
    }

    int leftlen = index - ileft;
    TreeNode* node = new TreeNode(rootVal);
    node->left = buildTree(preorder, pleft + 1, pleft + leftlen, inorder, ileft,
                           index - 1);
    node->right = buildTree(preorder, pleft + leftlen + 1, pright, inorder,
                            index + 1, iright);
    return node;
  }
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildTree(preorder, 0, preorder.size() - 1, inorder, 0,
                     inorder.size() - 1);
  }
};
