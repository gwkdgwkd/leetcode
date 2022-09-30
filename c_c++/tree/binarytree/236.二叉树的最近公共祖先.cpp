/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：
对于有根树T的两个节点p、q，最近公共祖先表示为一个节点x，
满足x是p、q的祖先且x的深度尽可能大（一个节点也可以是它自己的祖先）。

示例1：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点5和节点1的最近公共祖先是节点3。

示例2：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点5和节点4的最近公共祖先是节点5。
     因为根据定义最近公共祖先节点可以为节点本身。

示例3：
输入：root = [1,2], p = 1, q = 2
输出：1

提示：
树中节点数目在范围[2, 10^5]内。
-10^9 <= Node.val <= 10^9
所有Node.val互不相同。
p != q
p和q均存在于给定的二叉树中。
*/

// 剑指Offer68-II二叉树的最近公共祖先
// 面试题0408首个共同祖先

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
// 1.求最⼩公共祖先，需要从底向上遍历，那么⼆叉树，
//   只能通过后序遍历（即：回溯）实现从低向上的遍历⽅式。
// 2.在回溯的过程中，必然要遍历整颗⼆叉树，即使已经找到结果了，
//   依然要把其他节点遍历完，因为要使⽤递归函数的返回值，
//   也就是代码中的left和right，做逻辑判断。
// 3.要理解如果返回值left为空，right不为空为什么要返回right，
//   为什么可以⽤返回right传给上⼀层结果。
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  if (root == p || root == q || root == NULL) return root;
  struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
  struct TreeNode* right = lowestCommonAncestor(root->right, p, q);

  if (left && right) return root;
  if (left) return left;  // (left && !right)
  return right;           // (!left && right)
}

// 递归
// 前序遍历可以理解为是从上往下，而后序遍历是从下往上，
// 就好比从p和q出发往上走，第一次相交的节点就是最近公共祖先
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p,
                                      struct TreeNode* q) {
  // base case
  if (root == NULL) return NULL;
  if (root == p || root == q) return root;

  struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
  struct TreeNode* right = lowestCommonAncestor(root->right, p, q);
  // 情况1，如果p和q都在以root为根的树中，
  // 那么left和right一定分别是p和q，从basecase看出来的。
  if (left != NULL && right != NULL) {
    return root;
  }
  // 情况2，如果p和q都不在以root为根的树中，直接返回null。
  if (left == NULL && right == NULL) {
    return NULL;
  }
  // 情况3，如果p和q只有一个存在于root为根的树中，函数返回该节点。
  return left == NULL ? right : left;
}

class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) return root;

    TreeNode* l = lowestCommonAncestor(root->left, p, q);
    TreeNode* r = lowestCommonAncestor(root->right, p, q);

    if (l && r) return root;
    if (l == nullptr && r == nullptr) return nullptr;

    return l == nullptr ? r : l;
  }
};
