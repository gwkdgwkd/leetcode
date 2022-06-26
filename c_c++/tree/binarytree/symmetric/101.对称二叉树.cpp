/*
给你一个二叉树的根节点root，检查它是否轴对称。

示例1：
输入：root = [1,2,2,3,4,4,3]
输出：true

示例2：
输入：root = [1,2,2,null,3,null,3]
输出：false

提示：
树中节点数目在范围[1, 1000]内
-100 <= Node.val <= 100

进阶：你可以运用递归和迭代两种方法解决这个问题吗？
*/

// 剑指Offer28对称的二叉树

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
bool compare(struct TreeNode* left, struct TreeNode* right) {
  if (left == NULL && right != NULL) return false;
  if (left != NULL && right == NULL) return false;
  if (left == NULL && right == NULL) return true;

  if (left->val != right->val) return false;

  bool outside = compare(left->left, right->right);
  bool inside = compare(left->right, right->left);

  return outside && inside;
}

bool isSymmetric(struct TreeNode* root) {
  if (root == NULL) return true;
  return compare(root->left, root->right);
}

// 迭代
// 这个迭代法，其实是把左右两个⼦树要⽐较的元素顺序放进⼀个容器，
// 然后成对成对的取出来进⾏⽐较，那么其实使⽤栈也是可以的。
// 只要把队列原封不动的改成栈就可以了
#define MAXQUEUE 30
struct TreeNode* queue[MAXQUEUE];
int front, tail, size;
int enQueue(struct TreeNode* data) {
  if ((tail + 1) % MAXQUEUE == front) {
    printf("full\n");
    return tail;
  }
  queue[tail % MAXQUEUE] = data;
  tail++;
  size++;
  return tail;
}
struct TreeNode* deQueue() {
  if (front == tail % MAXQUEUE) {
    printf("empty\n");
    return NULL;
  }
  struct TreeNode* ret = queue[front];
  front = (front + 1) % MAXQUEUE;
  size--;
  return ret;
}
int empty() { return size == 0; }

bool isSymmetric(struct TreeNode* root) {
  if (root == NULL) return true;

  front = tail = size = 0;

  enQueue(root->left);
  enQueue(root->right);
  while (!empty()) {
    struct TreeNode* left = deQueue();
    struct TreeNode* right = deQueue();
    // 左节点为空、右节点为空，此时说明是对称的
    if (left == NULL && right == NULL) continue;
    // 左右⼀个节点不为空，或者都不为空但数值不相同，返回false
    if (!left || !right || (left->val != right->val)) return false;
    enQueue(left->left);
    enQueue(right->right);
    enQueue(left->right);
    enQueue(right->left);
  }

  return true;
}

class Solution {
 public:
  bool isSymmetric(TreeNode* l, TreeNode* r) {
    if (l == nullptr && r == nullptr) return true;
    if ((l == nullptr && r != nullptr) || (l != nullptr && r == nullptr) ||
        (l->val != r->val)) {
      return false;
    }

    return isSymmetric(l->left, r->right) && isSymmetric(l->right, r->left);
  }
  bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    return isSymmetric(root->left, root->right);
  }
};
