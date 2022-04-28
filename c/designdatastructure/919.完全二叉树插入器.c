/*
完全二叉树是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，
并且所有的节点都尽可能地集中在左侧。
设计一种算法，将一个新节点插入到一个完整的二叉树中，并在插入后保持其完整。
实现CBTInserter类:
CBTInserter(TreeNode root) 使用头节点为root的给定树初始化该数据结构；
CBTInserter.insert(int v) 向树中插入一个值为Node.val == val的新节点TreeNode。
使树保持完全二叉树的状态，并返回插入节点TreeNode的父节点的值；
CBTInserter.get_root() 将返回树的头节点。

示例1：
输入
["CBTInserter", "insert", "insert", "get_root"]
[[[1, 2]], [3], [4], []]
输出
[null, 1, 2, [1, 2, 3, 4]]
解释
CBTInserter cBTInserter = new CBTInserter([1, 2]);
cBTInserter.insert(3);  // 返回 1
cBTInserter.insert(4);  // 返回 2
cBTInserter.get_root(); // 返回 [1, 2, 3, 4]

提示：
树中节点数量范围为 [1, 1000]
0 <= Node.val <= 5000
root 是完全二叉树
0 <= val <= 5000
每个测试用例最多调用insert和get_root操作10^4次
*/

// 剑指OfferII043往完全二叉树添加节点

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct {
  struct TreeNode *queue[12000];  // 指针数组存节点的指针。根节点从下标1开始。
  int cnt;
} CBTInserter;
void traval(struct TreeNode *root, int idx, CBTInserter *obj) {
  if (root == NULL) {
    return;
  }
  obj->queue[idx] = root;
  obj->cnt++;
  traval(root->left, 2 * idx, obj);
  traval(root->right, 2 * idx + 1, obj);
}
CBTInserter *cBTInserterCreate(struct TreeNode *root) {
  CBTInserter *obj = (CBTInserter *)malloc(sizeof(CBTInserter));
  memset(obj, 0, sizeof(CBTInserter));
  obj->cnt = 0;
  traval(root, 1, obj);
  return obj;
}
int cBTInserterInsert(CBTInserter *obj, int v) {
  struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
  node->left = NULL;
  node->right = NULL;
  node->val = v;
  obj->queue[++obj->cnt] = node;
  int idx = obj->cnt / 2;
  if (obj->cnt % 2) {
    obj->queue[idx]->right = node;
  } else {
    obj->queue[idx]->left = node;
  }
  return obj->queue[idx]->val;
}
struct TreeNode *cBTInserterGet_root(CBTInserter *obj) {
  return obj->queue[1];
}
void cBTInserterFree(CBTInserter *obj) { free(obj); }