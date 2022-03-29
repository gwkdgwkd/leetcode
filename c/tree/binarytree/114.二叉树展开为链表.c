/*
给你二叉树的根结点root，请你将它展开为一个单链表：
展开后的单链表应该同样使用TreeNode，其中right子指针指向链表中下一个结点，而左子指针始终为null 。
展开后的单链表应该与二叉树先序遍历顺序相同。

示例1：
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]

示例2：
输入：root = []
输出：[]

示例3：
输入：root = [0]
输出：[0]

提示：
树中结点数在范围[0, 2000]内
-100 <= Node.val <= 100

进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
void flatten(struct TreeNode* root) {
  if (!root) return;

  flatten(root->left);
  flatten(root->right);

  // 后序遍历位置，左右子树已经被拉平成一条链表
  struct TreeNode* l = root->left;
  struct TreeNode* r = root->right;

  // 将左子树作为右子树
  root->left = NULL;
  root->right = l;

  // 将原先的右子树接到当前右子树的末端
  struct TreeNode* p = root;
  while (p->right) {
    p = p->right;
  }

  p->right = r;

  return;
}

// 递归，前序遍历保存树节点到数组
struct TreeNode* array[10000];
int i;
void put_array(struct TreeNode* r) {
  if (r == NULL) {
    return;
  }
  array[i++] = r;
  put_array(r->left);
  put_array(r->right);
}
void flatten(struct TreeNode* root) {
  memset(array, 0, sizeof(array));
  i = 0;
  put_array(root);
  int j = 0;
  while (array[j] != NULL) {
    array[j]->left = NULL;
    array[j]->right = array[j + 1];
    j++;
  }
  return array[0];
}