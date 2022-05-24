/*
给你两棵二叉树：root1和root2。
想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。
你需要将这两棵树合并成一棵新二叉树。
合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；
否则，不为null的节点将直接作为新二叉树的节点。
返回合并后的二叉树。

注意: 合并过程必须从两个树的根节点开始。

示例1：
输入：root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
输出：[3,4,5,5,4,null,7]

示例2：
输入：root1 = [1], root2 = [1,2]
输出：[2,2]

提示：
两棵树中的节点数目在范围[0, 2000]内
-10^4 <= Node.val <= 10^4
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
  if (root1 == NULL) return root2;
  if (root2 == NULL) return root1;

  root1->val += root2->val;  // 前序遍历
  root1->left = mergeTrees(root1->left, root2->left);
  // root1->val += root2->val;  // 中序遍历也可以
  root1->right = mergeTrees(root1->right, root2->right);
  // root1->val += root2->val;  // 后序遍历也可以

  return root1;
}

// 迭代也可以，把两个树的节点同时加⼊队列进⾏⽐较
