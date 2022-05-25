/*
给出二叉搜索树的根节点，该树的节点值各不相同，
请你将其转换为累加树（Greater Sum Tree），
使每个节点node的新值等于原树中大于或等于node.val的值之和。
提醒一下，二叉搜索树满足下列约束条件：
节点的左子树仅包含键小于节点键的节点。
节点的右子树仅包含键大于节点键的节点。
左右子树也必须是二叉搜索树。

示例1：
输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

示例2：
输入：root = [0,null,1]
输出：[1,null,1]

示例3：
输入：root = [1,0,2]
输出：[3,3,2]

示例4：
输入：root = [3,2,4,1]
输出：[7,9,4,10]

提示：
树中的节点数介于0和10^4之间。
每个节点的值介于-10^4和10^4之间。
树中的所有值互不相同。
给定的树为二叉搜索树。
*/

// 注意：和1038相同
// 剑指OfferII054所有大于等于节点的值之和

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
int sum;
void traversal(struct TreeNode* root) {
  if (!root) return;
  // 从树中可以看出累加的顺序是右中左，所以需要反中序遍历这个⼆叉树，然后顺序累加就可以了。
  traversal(root->right);  // 中序遍历是升序，中序遍历调换左右子树是降序
  sum += root->val;
  root->val = sum;
  traversal(root->left);
}
struct TreeNode* convertBST(struct TreeNode* root) {
  sum = 0;
  traversal(root);
  return root;
}

// 迭代
int idx;
struct TreeNode* stack[100];
void push(struct TreeNode* node) { stack[idx++] = node; }
struct TreeNode* top() {
  return stack[idx - 1];
}
void pop() { --idx; }
int empty() { return idx == 0 ? 1 : 0; }
int sum;
void traversal(struct TreeNode* root) {
  struct TreeNode* cur = root;
  while (cur || !empty()) {
    if (cur) {
      push(cur);
      cur = cur->right;  // 中序遍历时，使用left
    } else {
      cur = top();
      pop();
      cur->val += sum;
      sum = cur->val;
      cur = cur->left;
    }
  }
}
struct TreeNode* convertBST(struct TreeNode* root) {
  sum = 0;
  idx = 0;
  traversal(root);
  return root;
}
