/*
给一个二叉搜索树的根节点root，返回树中任意两不同节点值之间的最小差值。
差值是一个正数，其数值等于两值之差的绝对值。

示例1：
输入：root = [4,2,6,1,3]
输出：1

示例2：
输入：root = [1,0,48,null,null,12,49]
输出：1

提示：
树中节点的数目范围是[2, 10^4]
0 <= Node.val <= 10^5
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
int node[10000];
int nodeSize;
void traversal(struct TreeNode* root) {
  if (root == NULL) return;
  traversal(root->left);
  node[nodeSize++] = root->val;
  traversal(root->right);
  return;
}
int getMinimumDifference(struct TreeNode* root) {
  nodeSize = 0;
  traversal(root);

  int min = INT_MAX;
  for (int i = 1; i < nodeSize; ++i) {
    min = fmin(min, node[i] - node[i - 1]);
  }

  return min;
}

class Solution {
 public:
  vector<int> nodes;
  void dfs(TreeNode* root) {
    if (root == nullptr) return;
    dfs(root->left);
    nodes.emplace_back(root->val);
    dfs(root->right);
  }
  int getMinimumDifference(TreeNode* root) {
    dfs(root);

    int res = INT_MAX;
    for (int i = 1; i < nodes.size(); ++i) {
      res = fmin(res, nodes[i] - nodes[i - 1]);
    }
    return res;
  }
};
