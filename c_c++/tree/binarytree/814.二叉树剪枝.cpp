/*
给你二叉树的根结点root，此外树的每个结点的值要么是0，要么是1。
返回移除了所有不包含1的子树的原二叉树。
节点node的子树为node本身加上所有node的后代。

示例1：
输入：root = [1,null,0,0,1]
输出：[1,null,0,null,1]
解释：只有红色节点满足条件所有不包含1的子树。

示例2：
输入：root = [1,0,1,0,0,0,1]
输出：[1,null,1,null,1]

示例3：
输入：root = [1,1,0,1,1,0,1,0]
输出：[1,1,0,1,1,null,1]

提示：
树中节点的数目在范围[1, 200]内
Node.val为0或1
*/

// 剑指OfferII047二叉树剪枝

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

bool dfs(struct TreeNode* root) {  // 判断是否包含1
  if (root == NULL) return false;
  int left = dfs(root->left);
  int right = dfs(root->right);

  if (!left) root->left = NULL;
  if (!right) root->right = NULL;

  return root->val == 1 || left || right;
}
struct TreeNode* pruneTree(struct TreeNode* root) {
  return dfs(root) ? root : NULL;
}

class Solution {
 public:
  bool dfs(TreeNode* root) {
    if (root == nullptr) return false;

    bool l = dfs(root->left);
    bool r = dfs(root->right);
    if (!l) root->left = nullptr;
    if (!r) root->right = nullptr;

    return root->val || l || r;
  }
  TreeNode* pruneTree(TreeNode* root) { return dfs(root) ? root : nullptr; }
};