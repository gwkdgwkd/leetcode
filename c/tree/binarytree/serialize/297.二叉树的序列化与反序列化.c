#define MAX_SIZE 100000

// 前序
void preorder(struct TreeNode* root, char* data) {
  if (!root) {
    sprintf(data + strlen(data), "#,");
    return;
  }
  sprintf(data + strlen(data), "%d,", root->val);
  preorder(root->left, data);
  preorder(root->right, data);
}
char* serialize(struct TreeNode* root) {
  char* res = (char*)malloc(sizeof(char) * MAX_SIZE);
  memset(res, 0, sizeof(res));
  preorder(root, res);
  return res;
}
struct TreeNode* createTree(char* data, int* index) {
  if (data[(*index)] == '#') {
    *index += 2;
    return NULL;
  }
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  char tmp[10] = {0};
  int i = 0;
  while (data[(*index)] != ',') {
    tmp[i++] = data[(*index)++];
  }
  (*index)++;
  root->val = atoi(tmp);
  root->left = createTree(data, index);
  root->right = createTree(data, index);

  return root;
}
struct TreeNode* deserialize(char* data) {
  int index = 0;
  return createTree(data, &index);
}

// 后序
void pastorder(struct TreeNode* root, char* data) {
  if (!root) {
    sprintf(data + strlen(data), "#,");
    return;
  }
  pastorder(root->left, data);
  pastorder(root->right, data);
  sprintf(data + strlen(data), "%d,", root->val);
}
char* serialize(struct TreeNode* root) {
  char* res = (char*)malloc(sizeof(char) * MAX_SIZE);
  memset(res, 0, sizeof(res));
  pastorder(root, res);
  return res;
}
struct TreeNode* createTree(char* data, int* index) {
  if (data[(*index) - 1] == '#') {
    *index -= 2;
    return NULL;
  }
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  char tmp[10] = {0};
  int i = *index - 1;
  for (; data[i] != ','; --i)
    ;
  memcpy(tmp, data + i + 1, (*index - i - 1) * sizeof(char));
  *index = i;
  root->val = atoi(tmp);
  root->right = createTree(data, index);
  root->left = createTree(data, index);

  return root;
}
struct TreeNode* deserialize(char* data) {
  int index = strlen(data) - 1;
  return createTree(data, &index);
}

// 中序遍历的方式行不通，因为无法实现反序列化方法。

// 层级遍历
#define MAXQUEUE 20000
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
char* serialize(struct TreeNode* root) {
  if (!root) return NULL;
  front = tail = size = 0;

  char* res = (char*)malloc(sizeof(char) * MAX_SIZE);
  memset(res, 0, sizeof(res));

  enQueue(root);
  while (!empty()) {
    struct TreeNode* cur = deQueue();
    if (!cur) {
      sprintf(res + strlen(res), "#,");
      continue;
    }
    sprintf(res + strlen(res), "%d,", cur->val);
    enQueue(cur->left);
    enQueue(cur->right);
  }

  return res;
}
struct TreeNode* deserialize(char* data) {
  if (!data) return NULL;
  // printf("%s\n",data);
  front = tail = size = 0;
  memset(queue, 0, sizeof(struct TreeNode*) * MAXQUEUE);

  // 取根节点的val
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  int start = 0;
  int end = 0;
  int i = 0;
  while (data[i++] != ',') {
    end++;
  }
  char tmp[10] = {0};
  memcpy(tmp, data + start, sizeof(char) * (end - start));
  // printf("(%d %d):%s[%d]\n",start,end,tmp,i);
  root->val = atoi(tmp);
  enQueue(root);

  while (i < strlen(data)) {
    struct TreeNode* cur = deQueue();

    // 取左子树的val
    start = end = i;
    while (data[i++] != ',') {
      end++;
    }
    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, data + start, sizeof(char) * (end - start));
    // printf("(%d %d):%s[%d]\n",start,end,tmp,i);
    if (memcmp(tmp, "#", sizeof(char))) {
      struct TreeNode* l = (struct TreeNode*)malloc(sizeof(struct TreeNode));
      l->val = atoi(tmp);
      cur->left = l;
      enQueue(l);
    } else {
      cur->left = NULL;
    }

    // 取右子树的val
    start = end = i;
    while (data[i++] != ',') {
      end++;
    }
    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, data + start, sizeof(char) * (end - start));
    // printf("(%d %d):%s[%d]\n",start,end,tmp,i);
    if (memcmp(tmp, "#", sizeof(char))) {
      struct TreeNode* r = (struct TreeNode*)malloc(sizeof(struct TreeNode));
      r->val = atoi(tmp);
      cur->right = r;
      enQueue(r);
    } else {
      cur->right = NULL;
    }
  }

  return root;
}

// 取巧解法，直接进行强制类型转换，将二叉树和字符串进行强制转换
char* serialize(struct TreeNode* root) { return (char*)root; }
struct TreeNode* deserialize(char* data) {
  return (struct TreeNode*)data;
}