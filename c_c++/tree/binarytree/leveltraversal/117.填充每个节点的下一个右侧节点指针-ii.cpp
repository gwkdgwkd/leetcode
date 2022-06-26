/*
填充它的每个next指针，让这个指针指向其下一个右侧节点。
如果找不到下一个右侧节点，则将next指针设置为NULL。
初始状态下，所有next指针都被设置为NULL。

进阶：
你只能使用常量级额外空间。
使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。

示例：
输入：root = [1,2,3,4,5,null,7]
输出：[1,#,2,3,#,4,5,7,#]
解释：给定二叉树如图A所示，你的函数应该填充它的每个next指针，以指向其下一个右侧节点，
如图B所示。序列化输出按层序遍历顺序（由next指针连接），'#'表示每层的末尾。

提示：
树中的节点数小于6000
-100 <= node.val <= 100
*/

struct Node {
  int val;
  struct Node* left;
  struct Node* right;
  struct Node* next;
};

// 迭代，和116写法一样
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

// 不是完全二叉树，不能用116题的递归？

class Solution {
 public:
  Node* connect(Node* root) {
    if (root == nullptr) {
      return root;
    }

    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
      int n = q.size();

      Node* pre;
      for (int i = 0; i < n; ++i) {
        Node* cur = q.front();
        q.pop();
        if (i > 0) {
          pre->next = cur;
        }
        pre = cur;
        if (cur->left) {
          q.push(cur->left);
        }

        if (cur->right) {
          q.push(cur->right);
        }
      }
    }
    return root;
  }
};