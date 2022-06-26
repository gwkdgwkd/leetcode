/*
给定一棵二叉搜索树和其中的一个节点p，找到该节点在树中的中序后继。
如果节点没有中序后继，请返回null。
节点p的后继是值比p.val大的节点中键值最小的节点，即按中序遍历的顺序节点p的下一个节点。

示例1：
输入：root = [2,1,3], p = 1
输出：2
解释：这里1的中序后继是2。请注意p和返回值都应是TreeNode类型。

示例2：
输入：root = [5,3,6,2,4,null,null,1], p = 6
输出：null
解释：因为给出的节点没有中序后继，所以答案就返回null了。

提示：
树中节点的数目在范围[1, 10^4]内。
-10^5 <= Node.val <= 10^5
树中各节点的值均保证唯一。

注意：本题与285题相同
*/

// 面试题0406后继者

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p) {
  struct TreeNode* pre = NULL;

  while (root) {
    if (root->val > p->val) {
      pre = root;
      root = root->left;
    } else {
      root = root->right;
    }
  }

  return pre;
}

class Solution {
 public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* pre = nullptr;

    while (root) {
      if (root->val > p->val) {
        pre = root;
        root = root->left;
      } else {
        root = root->right;
      }
    }

    return pre;
  }
};