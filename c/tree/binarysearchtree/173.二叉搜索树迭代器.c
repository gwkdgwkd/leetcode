/*
实现一个二叉搜索树迭代器类BSTIterator，表示一个按中序遍历二叉搜索树（BST）的迭代器：
BSTIterator(TreeNode root) 初始化BSTIterator类的一个对象。
BST的根节点root会作为构造函数的一部分给出。
指针应初始化为一个不存在于BST中的数字，且该数字小于BST中的任何元素。
boolean hasNext() 如果向指针右侧遍历存在数字，则返回true；否则返回false。
int next()将指针向右移动，然后返回指针处的数字。

注意，指针初始化为一个不存在于BST中的数字，所以对next()的首次调用将返回BST中的最小元素。
你可以假设next()调用总是有效的，也就是说，当调用next()时，BST的中序遍历中至少存在一个下一个数字。

示例：
输入
["BSTIterator", "next", "next", "hasNext", "next", 
 "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
输出
[null, 3, 7, true, 9, true, 15, true, 20, false]
解释
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // 返回3
bSTIterator.next();    // 返回7
bSTIterator.hasNext(); // 返回True
bSTIterator.next();    // 返回9
bSTIterator.hasNext(); // 返回True
bSTIterator.next();    // 返回15
bSTIterator.hasNext(); // 返回True
bSTIterator.next();    // 返回20
bSTIterator.hasNext(); // 返回False

提示：
树中节点的数目在范围[1, 10^5]内
0 <= Node.val <= 10^6
最多调用10^5次hasNext和next操作

进阶：你可以设计一个满足下述条件的解决方案吗？
next()和hasNext()操作均摊时间复杂度为O(1)，并使用O(h)内存。
其中h是树的高度。
*/

// 剑指OfferII055二叉搜索树迭代器

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 扁平化
typedef struct {
  struct TreeNode* nodes[10000];
  int size;
  int idx;
} BSTIterator;
void dfs(BSTIterator* obj, struct TreeNode* root) {
  if (root == NULL) return;

  dfs(obj, root->left);
  obj->nodes[obj->size++] = root->val;
  dfs(obj, root->right);
}
BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
  BSTIterator* obj = (BSTIterator*)malloc(sizeof(BSTIterator));
  obj->size = 0;
  obj->idx = -1;
  dfs(obj, root);
  return obj;
}
int bSTIteratorNext(BSTIterator* obj) { return obj->nodes[++obj->idx]; }
bool bSTIteratorHasNext(BSTIterator* obj) {
  return obj->size > 0 && obj->idx < obj->size - 1;
}
void bSTIteratorFree(BSTIterator* obj) { free(obj); }

// 迭代
typedef struct {
  struct TreeNode* cur;
  struct StackTreeNode* stk[128];
  int stkSize;
} BSTIterator;
BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
  BSTIterator* ret = malloc(sizeof(BSTIterator));
  ret->cur = root;
  ret->stkSize = 0;
  return ret;
}
int bSTIteratorNext(BSTIterator* obj) {
  while (obj->cur != NULL) {
    obj->stk[(obj->stkSize)++] = obj->cur;
    obj->cur = obj->cur->left;
  }
  obj->cur = obj->stk[--(obj->stkSize)];
  int ret = obj->cur->val;
  obj->cur = obj->cur->right;
  return ret;
}
bool bSTIteratorHasNext(BSTIterator* obj) {
  return obj->cur != NULL || obj->stkSize;
}
void bSTIteratorFree(BSTIterator* obj) { free(obj); }