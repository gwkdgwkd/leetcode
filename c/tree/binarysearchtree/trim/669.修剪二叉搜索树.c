/*
给你二叉搜索树的根节点root，同时给定最小边界low和最大边界high。
通过修剪二叉搜索树，使得所有节点的值在[low, high]中。
修剪树不应该改变保留在树中的元素的相对结构。
可以证明，存在唯一的答案 。
所以结果应当返回修剪好的二叉搜索树的新的根节点。注意，根节点可能会根据给定的边界发生改变。

示例1：
输入：root = [1,0,2], low = 1, high = 2
输出：[1,null,2]

示例2：
输入：root = [3,0,4,null,2,null,null,1], low = 1, high = 3
输出：[3,2,null,1]

提示：
树中节点数在范围[1, 104]内
0 <= Node.val <= 104
树中每个节点的值都是唯一的
题目数据保证输入是一棵有效的二叉搜索树
0 <= low <= high <= 104
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* trimBST(struct TreeNode* root, int low, int high) {
  if (!root) return root;

  if (root->val < low) {
    return trimBST(root->right, low, high);
  } else if (root->val > high) {
    return trimBST(root->left, low, high);
  }

  root->left = trimBST(root->left, low, high);
  root->right = trimBST(root->right, low, high);

  return root;
}

// 迭代
struct TreeNode* trimBST(struct TreeNode* root, int low, int high) {
  if (!root) return root;

  // 处理头结点，让root移动到[low,high]范围内，注意是左闭右闭
  while (root && (root->val < low || root->val > high)) {
    if (root->val < low)
      root = root->right;
    else
      root = root->left;
  }

  // 此时root已经在[low,high]范围内，处理左孩⼦元素⼩于low的情况
  struct TreeNode* cur = root;
  while (cur) {
    while (cur->left && cur->left->val < low) {
      cur->left = cur->left->right;
    }
    cur = cur->left;
  }
  cur = root;
  // 此时root已经在[low,high]范围内，处理右孩⼦⼤于high的情况
  while (cur) {
    while (cur->right && cur->right->val > high) {
      cur->right = cur->right->left;
    }
    cur = cur->right;
  }

  return root;
}
