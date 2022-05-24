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
