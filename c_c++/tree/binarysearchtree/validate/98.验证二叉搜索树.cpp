/*
给你一个二叉树的根节点root，判断其是否是一个有效的二叉搜索树。
有效二叉搜索树定义如下：
1.节点的左子树只包含小于当前节点的数；
2.节点的右子树只包含大于当前节点的数；
3.所有左子树和右子树自身必须也是二叉搜索树。

示例1：
输入：root = [2,1,3]
输出：true

示例2：
输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是5，但是右子节点的值是4。

提示：
树中节点数目范围在[1, 10^4]内
-2^31 <= Node.val <= 2^31 - 1
*/

// 面试题0405合法二叉搜索树

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
int node[10000];
int nodeSize;
void traversal(struct TreeNode* root) {
  if (root == NULL) return;

  traversal(root->left);
  node[nodeSize++] = root->val;
  traversal(root->right);

  return;
}
bool isValidBST(struct TreeNode* root) {
  nodeSize = 0;
  traversal(root);

  for (int i = 0; i < nodeSize - 1; ++i) {
    if (node[i] >= node[i + 1]) {
      return false;
    }
  }

  return true;
}

// 递归，不用数组，只记录之前的值
int pre = INT_MIN;
bool isValidBST(struct TreeNode* root) {
  if (root == NULL) return true;

  bool left = isValidBST(root->left);
  if (pre < root->val)
    pre = root->val;
  else
    return false;
  bool right = isValidBST(root->right);

  return left && right;
}

// 递归
bool isValid(struct TreeNode* root, struct TreeNode* min,
             struct TreeNode* max) {
  if (root == NULL) return true;
  if (min && root->val <= min->val) return false;
  if (max && root->val >= max->val) return false;

  return isValid(root->left, min, root) && isValid(root->right, root, max);
}
bool isValidBST(struct TreeNode* root) { return isValid(root, NULL, NULL); }

class Solution {
 public:
  bool isValid(TreeNode* root, TreeNode* min, TreeNode* max) {
    if (root == nullptr) return true;

    if (min && min->val >= root->val) return false;
    if (max && root->val >= max->val) return false;

    return isValid(root->left, min, root) && isValid(root->right, root, max);
  }
  bool isValidBST(TreeNode* root) { return isValid(root, nullptr, nullptr); }
};