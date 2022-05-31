/*
给定一棵二叉树，设计一个算法，创建含有某一深度上所有节点的链表。
比如，若一棵树的深度为D，则会创建出D个链表。
返回一个包含所有深度的链表的数组。

示例：
输入：[1,2,3,4,5,null,7,8]
        1
       /  \ 
      2    3
     / \    \ 
    4   5    7
   /
  8
输出：[[1],[2,3],[4,5,7],[8]]
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct ListNode {
  int val;
  struct ListNode* next;
};

int getHeight(struct TreeNode* root) {
  if (root == NULL) return 0;
  return fmax(getHeight(root->left), getHeight(root->right)) + 1;
}

struct ListNode** listOfDepth(struct TreeNode* tree, int* returnSize) {
  int height = getHeight(tree);

  struct ListNode** res =
      (struct ListNode**)malloc(sizeof(struct ListNode*) * height);
  *returnSize = 0;

  struct TreeNode* queue[10000];
  int front = 0;
  int tail = 0;

  queue[tail++] = tree;

  while (tail > front) {
    int n = tail - front;
    struct ListNode* pre = NULL;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = queue[front++];
      struct ListNode* n = (struct ListNode*)malloc(sizeof(struct ListNode));
      n->val = node->val;
      n->next = NULL;
      if (pre == NULL) {
        res[(*returnSize)++] = n;
        pre = n;
      } else {
        pre->next = n;
        pre = pre->next;
      }
      if (node->left) queue[tail++] = node->left;
      if (node->right) queue[tail++] = node->right;
    }
  }

  return res;
}