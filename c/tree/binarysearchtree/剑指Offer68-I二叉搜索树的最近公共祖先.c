/*
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：
“对于有根树T的两个结点p、q，最近公共祖先表示为一个结点x，
满足x是p、q的祖先且x的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉搜索树:root = [6,2,8,0,4,7,9,null,null,3,5]

示例1:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。

示例2:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点2和节点4的最近公共祖先是2, 因为根据定义最近公共祖先节点可以为节点本身。

说明:
所有节点的值都是唯一的。
p、q为不同节点且均存在于给定的二叉搜索树中。

注意：本题与235题相同
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  if (root->val < p->val && root->val < q->val) {
    return lowestCommonAncestor(root->right, p, q);
  } else if (root->val > p->val && root->val > q->val) {
    return lowestCommonAncestor(root->left, p, q);
  } else {
    return root;
  }
}
