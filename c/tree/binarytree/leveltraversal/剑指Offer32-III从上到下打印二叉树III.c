/*
请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，
第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

例如:
给定二叉树: [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：
[
  [3],
  [20,9],
  [15,7]
]

提示：节点总数 <= 1000
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

#define MAXQUEUE 1000
struct TreeNode* queue[MAXQUEUE];
int tail, front, size;
int enQueue(struct TreeNode* node) {
  if ((tail + 1) % MAXQUEUE == front) {
    printf("full\n");
    return tail;
  }
  queue[tail % MAXQUEUE] = node;
  ++tail;
  ++size;
  return tail;
}
struct TreeNode* deQueue() {
  if (tail % MAXQUEUE == front) {
    printf("empty\n");
    return NULL;
  }
  struct TreeNode* ret = queue[front];
  front = (front + 1) % MAXQUEUE;
  --size;
  return ret;
}
bool empty() { return size == 0; }
void reverse(int* nums, int left, int right) {
  while (left < right) {
    int temp = nums[left];
    nums[left] = nums[right];
    nums[right] = temp;
    ++left;
    --right;
  }
}
int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes) {
  int** res = (int**)malloc(sizeof(int*) * 1000);
  *returnColumnSizes = (int*)malloc(sizeof(int) * 1000);
  *returnSize = 0;
  tail = front = size = 0;

  if (root != NULL) {
    enQueue(root);
  }

  while (!empty()) {
    int num = size;
    res[*returnSize] = (int*)malloc(sizeof(int) * num);
    (*returnColumnSizes)[*returnSize] = num;
    for (int i = 0; i < num; ++i) {
      struct TreeNode* node = deQueue();
      res[*returnSize][i] = node->val;
      if (node->left) {
        enQueue(node->left);
      }
      if (node->right) {
        enQueue(node->right);
      }
    }
    (*returnSize)++;
  }
  for (int i = 0; i < *returnSize; ++i) {
    if (i % 2) {
      reverse(res[i], 0, (*returnColumnSizes)[i] - 1);
    }
  }

  return res;
}