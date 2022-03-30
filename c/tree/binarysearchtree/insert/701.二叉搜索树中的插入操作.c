/*
给定二叉搜索树（BST）的根节点root和要插入树中的值value，将值插入二叉搜索树。
返回插入后二叉搜索树的根节点。输入数据保证，新值和原始二叉搜索树中的任意节点值都不同。
注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。你可以返回任意有效的结果。

示例1：
输入：root = [4,2,7,1,3], val = 5
输出：[4,2,7,1,3,5]
解释：另一个满足题目要求可以通过的树是：

示例2：
输入：root = [40,20,60,10,30,50,70], val = 25
输出：[40,20,60,10,30,50,70,null,null,25]

示例3：
输入：root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
输出：[4,2,7,1,3,5]

提示：
树中的节点数将在[0, 104]的范围内。
-108 <= Node.val <= 108
所有值Node.val是独一无二 的。
-108 <= val <= 108
保证val在原始BST中不存在。
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
  if (!root) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
  }
  if (root->val > val) {
    root->left = insertIntoBST(root->left, val);
  } else if (root->val < val) {
    root->right = insertIntoBST(root->right, val);
  }
  return root;
}

// 迭代
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
  if (root == NULL) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
  }
  struct TreeNode* cur = root;
  struct TreeNode* pre = root;
  while (cur) {
    if (cur->val > val) {
      pre = cur;
      cur = cur->left;
    } else if (cur->val < val) {
      pre = cur;
      cur = cur->right;
    }
  }

  struct TreeNode* node1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  node1->val = val;
  node1->left = node1->right = NULL;
  if (pre->val > val)
    pre->left = node1;
  else
    pre->right = node1;

  return root;
}
