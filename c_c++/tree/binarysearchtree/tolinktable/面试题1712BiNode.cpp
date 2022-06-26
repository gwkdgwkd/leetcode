/*
二叉树数据结构TreeNode可用来表示单向链表（其中left置空，right为下一个链表节点）。
实现一个方法，把二叉搜索树转换为单向链表，要求依然符合二叉搜索树的性质，
转换操作应是原址的，也就是在原始的二叉搜索树上直接修改。
返回转换后的单向链表的头节点。
注意：本题相对原题稍作改动

示例：
输入： [4,2,5,1,3,null,6,0]
输出： [0,null,1,null,2,null,3,null,4,null,5,null,6]

提示：节点数量不会超过100000。
*/

struct TreeNode* pre;
void inorder(struct TreeNode* root, struct TreeNode** r) {
  if (!root) return;
  inorder(root->right, r);
  root->right = pre;
  if (pre) pre->left = 0;
  pre = root;
  *r = root;
  inorder(root->left, r);
}
struct TreeNode* convertBiNode(struct TreeNode* root) {
  pre = 0;
  inorder(root, &root);
  return root;
}

// 迭代
struct TreeNode* convertBiNode(struct TreeNode* root) {
  struct TreeNode* stack[100];
  int top = 0;
  // stack[top++]=root;

  struct TreeNode* head = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  head->left = NULL;
  head->right = NULL;
  struct TreeNode* pre = head;

  struct TreeNode* p = root;
  while (top > 0 || p != NULL) {
    if (p) {
      stack[top++] = p;  // push
      p = p->left;
    } else if (top > 0) {
      p = stack[--top];  // pop
      // 中序
      pre->right = p;
      p->left = NULL;
      pre = pre->right;  // 指针

      p = p->right;  // 右子树
    }
  }
  return head->right;
}

struct TreeNode* head;
struct TreeNode* pointer;
void convert_recursion(struct TreeNode* root) {
  if (root != NULL) {
    convert_recursion(root->left);
    if (pointer == NULL) {  // 递归初始化头结点
      pointer = root;
      head = root;
    } else {
      pointer->right = root;  // visit
      root->left = NULL;
      pointer = pointer->right;
    }
    convert_recursion(root->right);
    pointer->right = NULL;
  }
}
struct TreeNode* convertBiNode(struct TreeNode* root) {
  head = NULL;
  pointer = NULL;
  convert_recursion(root);  // 递归
  return head;
}

class Solution {
 public:
  TreeNode* pre;  // 默认初始化就是nullptr么？
  TreeNode* convertBiNode(TreeNode* root) {
    if (root == nullptr) {
      return root;
    }

    convertBiNode(root->right);
    root->right = pre;
    pre = root;
    convertBiNode(root->left);
    root->left = nullptr;

    return pre;
  }
};