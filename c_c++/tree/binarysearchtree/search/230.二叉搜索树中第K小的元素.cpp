/*
给定一个二叉搜索树的根节点root，和一个整数k，
请你设计一个算法查找其中第k个最小元素（从1开始计数）。

示例1：
输入：root = [3,1,4,null,2], k = 1
输出：1

示例2：
输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3

提示：
树中的节点数为n。
1 <= k <= n <= 10^4
0 <= Node.val <= 10^4

进阶：如果二叉搜索树经常被修改，插入/删除操作，
     并且你需要频繁地查找第k小的值，你将如何优化算法？
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int i;
int ret;
void find(struct TreeNode* root, int k) {
  if (!root) return;

  find(root->left, k);
  if (i++ == k) {
    ret = root->val;
  }
  find(root->right, k);

  return;
}
int kthSmallest(struct TreeNode* root, int k) {
  i = 1;
  find(root, k);
  return ret;
}

class Solution {
 public:
  int max;
  int i;
  void dfs(TreeNode* root, int k) {
    if (root == nullptr) return;

    dfs(root->left, k);
    if (i++ == k) {
      max = root->val;
      return;
    }
    dfs(root->right, k);
  }
  int kthSmallest(TreeNode* root, int k) {
    max = INT_MIN;
    i = 1;
    dfs(root, k);
    return max;
  }
};

/*
剑指Offer54二叉搜索树的第k大节点
给定一棵二叉搜索树，请找出其中第k大的节点的值。

示例1:
输入: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
输出: 4

示例2:
输入: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
输出: 4

限制：1 ≤ k ≤ 二叉搜索树元素个数
*/

int max;
int i;
void dfs(struct TreeNode* root, int k) {
  if (root == NULL) {
    return;
  }
  dfs(root->right, k);
  if (i++ == k) {
    max = root->val;
    return;
  }
  dfs(root->left, k);
}
int kthLargest(struct TreeNode* root, int k) {
  i = 1;
  max = INT_MIN;

  dfs(root, k);
  return max;
}
