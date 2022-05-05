/*
检查子树。你有两棵非常大的二叉树：T1，有几万个节点；T2，有几万个节点。
设计一个算法，判断T2是否为T1的子树。
如果T1有这么一个节点n，其子树与T2一模一样，则T2为T1的子树，
也就是说，从节点n处把树砍断，得到的树与T2完全相同。
注意：此题相对书上原题略有改动。

示例1:
输入：t1 = [1, 2, 3], t2 = [2]
输出：true

示例2:
输入：t1 = [1, null, 2, 4], t2 = [3, 2]
输出：false

提示：树的节点数目范围为[0, 20000]。
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

bool checkSubTree(struct TreeNode* t1, struct TreeNode* t2) {
  if (t1 == NULL && t2 == NULL) return true;
  if (t2 == NULL) return true;
  if (t1 == NULL && t2) return false;

  if (t1->val == t2->val) {
    return checkSubTree(t1->left, t2->left) &&
           checkSubTree(t1->right, t2->right);
  } else {
    return checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
  }
}