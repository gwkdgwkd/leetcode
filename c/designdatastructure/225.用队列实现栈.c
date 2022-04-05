/*
请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop和empty）。
实现MyStack 类：
void push(int x)将元素x压入栈顶。
int pop()移除并返回栈顶元素。
int top()返回栈顶元素。
boolean empty()如果栈是空的，返回true；否则，返回false。

注意：
你只能使用队列的基本操作——也就是pushtoback、peek/popfromfront、size和isempty这些操作。
你所使用的语言也许不支持队列，
你可以使用list（列表）或者deque（双端队列）来模拟一个队列，只要是标准的队列操作即可。

示例：
输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回2
myStack.pop(); // 返回2
myStack.empty(); // 返回False

提示：
1 <= x <= 9
最多调用100 次 push、pop、top 和 empty
每次调用pop和top都保证栈不为空

进阶：你能否仅用一个队列来实现栈。
*/

// 两个队列实现栈
#define LEN 20
typedef struct queue {
  int *data;
  int head;
  int rear;
  int size;
} Queue;
typedef struct {
  Queue *queue1, *queue2;
} MyStack;
Queue *initQueue(int k) {
  Queue *obj = (Queue *)malloc(sizeof(Queue));
  obj->data = (int *)malloc(k * sizeof(int));
  obj->head = -1;
  obj->rear = -1;
  obj->size = k;
  return obj;
}
void enQueue(Queue *obj, int e) {
  if (obj->head == -1) {
    obj->head = 0;
  }
  obj->rear = (obj->rear + 1) % obj->size;
  obj->data[obj->rear] = e;
}
int deQueue(Queue *obj) {
  int a = obj->data[obj->head];
  if (obj->head == obj->rear) {
    obj->rear = -1;
    obj->head = -1;
    return a;
  }
  obj->head = (obj->head + 1) % obj->size;
  return a;
}
int isEmpty(Queue *obj) { return obj->head == -1; }
MyStack *myStackCreate() {
  MyStack *obj = (MyStack *)malloc(sizeof(MyStack));
  obj->queue1 = initQueue(LEN);
  obj->queue2 = initQueue(LEN);
  return obj;
}
void myStackPush(MyStack *obj, int x) {
  if (isEmpty(obj->queue1)) {
    enQueue(obj->queue2, x);
  } else {
    enQueue(obj->queue1, x);
  }
}
int myStackPop(MyStack *obj) {
  if (isEmpty(obj->queue1)) {
    while (obj->queue2->head != obj->queue2->rear) {
      enQueue(obj->queue1, deQueue(obj->queue2));
    }
    return deQueue(obj->queue2);
  }
  while (obj->queue1->head != obj->queue1->rear) {
    enQueue(obj->queue2, deQueue(obj->queue1));
  }
  return deQueue(obj->queue1);
}
int myStackTop(MyStack *obj) {
  if (isEmpty(obj->queue1)) {
    return obj->queue2->data[obj->queue2->rear];
  }
  return obj->queue1->data[obj->queue1->rear];
}
bool myStackEmpty(MyStack *obj) {
  if (obj->queue1->head == -1 && obj->queue2->head == -1) {
    return true;
  }
  return false;
}
void myStackFree(MyStack *obj) {
  free(obj->queue1->data);
  obj->queue1->data = NULL;
  free(obj->queue1);
  obj->queue1 = NULL;
  free(obj->queue2->data);
  obj->queue2->data = NULL;
  free(obj->queue2);
  obj->queue2 = NULL;
  free(obj);
  obj = NULL;
}

// 一个队列实现栈
typedef struct tagListNode {
  struct tagListNode *next;
  int val;
} ListNode;
typedef struct {
  ListNode *top;
} MyStack;
MyStack *myStackCreate() {
  MyStack *stk = calloc(1, sizeof(MyStack));
  return stk;
}
void myStackPush(MyStack *obj, int x) {
  ListNode *node = malloc(sizeof(ListNode));
  node->val = x;
  node->next = obj->top;
  obj->top = node;
}
int myStackPop(MyStack *obj) {
  ListNode *node = obj->top;
  int val = node->val;
  obj->top = node->next;
  free(node);

  return val;
}
int myStackTop(MyStack *obj) { return obj->top->val; }
bool myStackEmpty(MyStack *obj) { return (obj->top == NULL); }
void myStackFree(MyStack *obj) {
  while (obj->top != NULL) {
    ListNode *node = obj->top;
    obj->top = obj->top->next;
    free(node);
  }
  free(obj);
}