/*
给你两棵二叉树root和subRoot。
检验root中是否包含和subRoot具有相同结构和节点值的子树。
如果存在，返回true；否则，返回false。
二叉树tree的一棵子树包括tree的某个节点和这个节点的所有后代节点。
tree也可以看做它自身的一棵子树。

示例1：
输入：root = [3,4,5,1,2], subRoot = [4,1,2]
输出：true

示例2：
输入：root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
输出：false

提示：
root树上的节点数量范围是[1, 2000]
subRoot树上的节点数量范围是[1, 1000]
-10^4 <= root.val <= 10^4
-10^4 <= subRoot.val <= 10^4
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
bool compare(struct TreeNode* root, struct TreeNode* subRoot) {
  if (!root && !subRoot) return true;
  if ((!root && subRoot) || (root && !subRoot) ||
      (root && subRoot && root->val != subRoot->val))
    return false;

  return compare(root->left, subRoot->left) &&
         compare(root->right, subRoot->right);
}
bool dfs(struct TreeNode* root, struct TreeNode* subRoot) {
  if (!root) return false;

  return compare(root, subRoot) || dfs(root->left, subRoot) ||
         dfs(root->right, subRoot);
}
bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
  return dfs(root, subRoot);
}

// 面试题0410检查子树
// 检查子树。你有两棵非常大的二叉树：T1，有几万个节点；T2，有几万个节点。
// 设计一个算法，判断T2是否为T1的子树。
// 如果T1有这么一个节点n，其子树与T2一模一样，则T2为T1的子树，
// 也就是说，从节点n处把树砍断，得到的树与T2完全相同。
// 注意：此题相对书上原题略有改动

// 572的解法面试题可以通过，但是下面的写法572不能通过
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
