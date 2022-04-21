/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：
“对于有根树T的两个结点p、q，最近公共祖先表示为一个结点x，
满足x是p、q的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉树:root = [3,5,1,6,2,0,8,null,null,7,4]

示例1:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点5和节点1的最近公共祖先是节点3。

示例2:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点5和节点4的最近公共祖先是节点5。因为根据定义最近公共祖先节点可以为节点本身。

说明:
所有节点的值都是唯一的。
p、q为不同节点且均存在于给定的二叉树中。

注意：本题与236题相同
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  if (root == NULL || root == p || root == q) return root;

  struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
  struct TreeNode* right = lowestCommonAncestor(root->right, p, q);

  if (left && right) return root;
  if (left == NULL && right == NULL) return NULL;
  if (left == NULL) return right;  // left == NULL && right != NULL
  return left;                     // right == NULL && left != NULL
}