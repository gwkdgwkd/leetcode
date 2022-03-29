/*
给你两棵二叉树的根节点p和q，编写一个函数来检验这两棵树是否相同。
如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

示例1：
输入：p = [1,2,3], q = [1,2,3]
输出：true

示例2：
输入：p = [1,2], q = [1,null,2]
输出：false

示例3：
输入：p = [1,2,1], q = [1,1,2]
输出：false

提示：
两棵树上的节点数目都在范围[0, 100]内
-104 <= Node.val <= 104
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
  if (p == NULL && q == NULL) return true;
  if ((p == NULL && q != NULL) || (p != NULL && q == NULL) ||
      (p != NULL && q != NULL && p->val != q->val))
    return false;

  return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
