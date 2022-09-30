/*
输入两棵二叉树A和B，判断B是不是A的子结构。
约定空树不是任意一个树的子结构。
B是A的子结构，即A中有出现和B相同的结构和节点值。
例如：
给定的树A：
     3
    / \
   4   5
  / \
 1   2
给定的树B：
   4
  /
 1
返回true，因为B与A的一个子树拥有相同的结构和节点值。

示例1：
输入：A = [1,2,3], B = [3,1]
输出：false

示例2：
输入：A = [3,4,5,1,2], B = [4,1]
输出：true

限制：0 <= 节点个数 <= 10000
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

bool compare(struct TreeNode* A, struct TreeNode* B) {
  if (!B) {  // 从compare调用，才可能有这种情况
    return true;
  }
  if (!A || A->val != B->val) {
    return false;
  }
  return compare(A->left, B->left) && compare(A->right, B->right);
}
bool isSubStructure(struct TreeNode* A, struct TreeNode* B) {
  if (!A || !B) return false;
  return compare(A, B) || isSubStructure(A->left, B) ||
         isSubStructure(A->right, B);
}

class Solution {
 public:
  bool isSameTree(TreeNode* p, TreeNode* q) {
    if (q == nullptr) return true;
    if (p == nullptr || p->val != q->val) {
      return false;
    }

    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
  }

  bool isSubStructure(TreeNode* A, TreeNode* B) {
    if (B == nullptr || A == nullptr) return false;

    return isSameTree(A, B) || isSubStructure(A->left, B) ||
           isSubStructure(A->right, B);
  }
};