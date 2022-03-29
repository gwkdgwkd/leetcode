/*
给定一个N叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）。
树的序列化输入是用层序遍历，每组子节点都由null值分隔（参见示例）。

示例1：
输入：root = [1,null,3,2,4,null,5,6]
输出：[[1],[3,2,4],[5,6]]

示例2：
输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：[[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

提示：
树的高度不会超过1000
树的节点总数在[0, 10^4]之间
*/

struct Node {
  int val;
  int numChildren;
  struct Node** children;
};

// 迭代
#define MAXQUEUE 10000
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
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
  int** result = (int**)malloc(sizeof(int*) * 10000);
  *returnSize = 0;
  *returnColumnSizes = (int*)malloc(sizeof(int) * 10000);
  front = tail = size = 0;

  if (root != NULL) {
    enQueue(root);
  }
  while (!empty()) {
    int n = size;
    (*returnColumnSizes)[*returnSize] = n;
    result[*returnSize] = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
      struct Node* node = deQueue();
      result[*returnSize][i] = node->val;
      for (int j = 0; j < node->numChildren; ++j) {
        if (node->children[j]) {
          enQueue(node->children[j]);
        }
      }
    }
    (*returnSize)++;
  }

  return result;
}
