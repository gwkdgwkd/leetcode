/*
给定一个完美二叉树，其所有叶子节点都在同一层，
每个父节点都有两个子节点。
填充它的每个next指针，让这个指针指向其下一个右侧节点。
如果找不到下一个右侧节点，则将next指针设置为NULL。
初始状态下，所有next指针都被设置为NULL。

示例1：
输入：root = [1,2,3,4,5,6,7]
输出：[1,#,2,3,#,4,5,6,7,#]
解释：给定二叉树如图A所示，你的函数应该填充它的每个next指针，
     以指向其下一个右侧节点，序列化的输出按层序遍历排列，
     同一层节点由next指针连接，'#'标志着每一层的结束。

示例2:
输入：root = []
输出：[]

提示：
树中节点的数量在[0, 212 - 1]范围内
-1000 <= node.val <= 1000

进阶：
你只能使用常量级额外空间。
使用递归解题也符合要求，本题中递归程序占用的栈空间不算。
*/

struct Node {
  int val;
  struct Node* left;
  struct Node* right;
  struct Node* next;
};

// 迭代
#define MAXQUEUE 5000
struct Node* queue[MAXQUEUE];
int front, tail, size;
int enQueue(struct Node* data) {
  if ((tail + 1) % MAXQUEUE == front) {
    printf("full\n");
    return tail;
  }
  queue[tail % MAXQUEUE] = data;
  tail++;
  size++;
  return tail;
}
struct Node* deQueue() {
  if (front == tail % MAXQUEUE) {
    printf("empty\n");
    return NULL;
  }
  struct Node* ret = queue[front];
  front = (front + 1) % MAXQUEUE;
  size--;
  return ret;
}
int empty() { return size == 0; }
struct Node* connect(struct Node* root) {
  front = tail = size = 0;
  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    struct Node* pre;
    for (int i = 0; i < n; ++i) {
      struct Node* node = deQueue();
      if (i != 0) {
        pre->next = node;
      }
      pre = node;
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
  }

  return root;
}

// 递归
void connectTwoNode(struct Node* l, struct Node* r) {
  if (!l || !r) return;

  l->next = r;
  connectTwoNode(l->left, l->right);
  connectTwoNode(l->right, r->left);
  connectTwoNode(r->left, r->right);
  return;
}
struct Node* connect(struct Node* root) {
  if (!root) return root;

  connectTwoNode(root->left, root->right);
  return root;
}

class Solution {
 public:
  void connect(Node* l, Node* r) {
    if (l == nullptr && r == nullptr) {
      return;
    }

    l->next = r;
    connect(l->left, l->right);
    connect(l->right, r->left);
    connect(r->left, r->right);
  }
  Node* connect(Node* root) {
    if (root == nullptr) {
      return root;
    }

    connect(root->left, root->right);
    return root;
  }
};
