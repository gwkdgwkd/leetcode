/*
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树T的两个结点p、q，
最近公共祖先表示为一个结点x，满足x是p、q的祖先且x的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉搜索树:root = [6,2,8,0,4,7,9,null,null,3,5]

示例1:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点2和节点8的最近公共祖先是6。

示例2:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点2和节点4的最近公共祖先是2, 因为根据定义最近公共祖先节点可以为节点本身。

说明:
所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉搜索树中。
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
// 普通⼆叉树求最近公共祖先需要使⽤回溯，从底向上来查找;
// ⼆叉搜索树就不⽤了，因为搜索树有序（相当于⾃带⽅向），那么只要从上向下遍历就可以了。
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  // 只要从上到下遍历的时候，root节点是数值在[p, q]区间中则说明该节点root就是最近公共祖先了。
  if (root->val < p->val && root->val < q->val)
    return lowestCommonAncestor(root->right, p, q);
  else if (root->val > p->val && root->val > q->val)
    return lowestCommonAncestor(root->left, p, q);
  else
    return root;
}

// 迭代
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  while (root) {
    if (root->val > q->val && root->val > p->val) {
      root = root->left;
    } else if (root->val < q->val && root->val < p->val) {
      root = root->right;
    } else {
      return root;
    }
  }
  return NULL;
}
