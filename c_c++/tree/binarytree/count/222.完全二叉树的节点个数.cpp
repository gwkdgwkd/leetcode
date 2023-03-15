/*
给一棵完全二叉树的根节点root，求出该树的节点个数。

完全二叉树的定义如下：
在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，
并且最下面一层的节点都集中在该层最左边的若干位置，最底层h包含1~2h个节点。

示例1：
输入：root = [1,2,3,4,5,6]
输出：6

示例2：
输入：root = []
输出：0

示例3：
输入：root = [1]
输出：1

提示：
树中节点的数目范围是[0, 5 * 10^4]
0 <= Node.val <= 5 * 10^4
题目数据保证输入的树是完全二叉树
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 如果是一个普通二叉树，显然只要向下面这样遍历一边即可，时间复杂度O(N)：
int countNodes(struct TreeNode* root) {
  if (root == NULL) return 0;
  return countNodes(root->left) + countNodes(root->right) + 1;
}

// 如果是一棵满二叉树，节点总数就和树的高度呈指数关系，时间复杂度O(logN)：
int countNodes(struct TreeNode* root) {
  int h = 0;
  // 计算树的高度
  while (root != NULL) {
    root = root->left;
    h++;
  }
  // 节点总数就是2^h - 1
  return (int)pow(2, h) - 1;
}

// 完全二叉树比普通二叉树特殊，但又没有满二叉树那么特殊，
// 计算它的节点总数，可以说是普通二叉树和完全二叉树的结合版：
// 时间复杂度是：O(logN*logN)
int countNodes(struct TreeNode* root) {
  struct TreeNode *l = root, *r = root;
  // 记录左、右子树的高度
  int hl = 0, hr = 0;
  while (l != NULL) {
    l = l->left;
    hl++;
  }
  while (r != NULL) {
    r = r->right;
    hr++;
  }
  // 如果左右子树的高度相同，则是一棵满二叉树：
  if (hl == hr) {
    return (int)pow(2, hl) - 1;
  }
  // 如果左右高度不同，则按照普通二叉树的逻辑计算：
  return 1 + countNodes(root->left) + countNodes(root->right);
}

// 迭代
#define MAXQUEUE 17000
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
int countNodes(struct TreeNode* root) {
  if (root == NULL) return 0;
  int count = 0;

  enQueue(root);
  while (!empty()) {
    int n = size;
    for (int i = 0; i < n; ++i) {
      struct TreeNode* node = deQueue();
      count++;
      if (node->left) enQueue(node->left);
      if (node->right) enQueue(node->right);
    }
  }
  return count;
}

class Solution {
 public:
  int countNodes(TreeNode* root) {
    TreeNode* l = root;
    TreeNode* r = root;

    int lh = 0;
    int rh = 0;
    while (l) {
      ++lh;
      l = l->left;
    }
    while (r) {
      ++rh;
      r = r->right;
    }

    if (lh == rh) {
      return (int)pow(2, lh) - 1;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
  }
};
