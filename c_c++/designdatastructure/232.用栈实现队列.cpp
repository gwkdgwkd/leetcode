/*
请你仅使用两个栈实现先入先出队列。
队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现MyQueue类：
void push(int x)将元素x推到队列的末尾
int pop()从队列的开头移除并返回元素
int peek()返回队列开头的元素
boolean empty()如果队列为空，返回true；否则，返回false

说明：
你只能使用标准的栈操作，也就是只有pushtotop、
peek/popfromtop、size和isempty操作是合法的。
你所使用的语言也许不支持栈。
你可以使用list或deque（双端队列）来模拟栈，只要是标准的栈操作即可。

示例1：
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2]
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false

提示：
1 <= x <= 9
最多调用100次push、pop、peek和empty
假设所有操作都是有效的（例如，一个空的队列不会调用pop或者peek操作）

进阶：
你能否实现每个操作均摊时间复杂度为O(1)的队列？
换句话说，执行n个操作的总时间复杂度为O(n)，即使其中一个操作可能花费较长时间。
*/

// 面试题0304化栈为队

// 两个栈实现队列
typedef struct {
  int* stk;
  int stkSize;
  int stkCapacity;
} Stack;
Stack* stackCreate(int cpacity) {
  Stack* ret = malloc(sizeof(Stack));
  ret->stk = malloc(sizeof(int) * cpacity);
  ret->stkSize = 0;
  ret->stkCapacity = cpacity;
  return ret;
}
void stackPush(Stack* obj, int x) { obj->stk[obj->stkSize++] = x; }
void stackPop(Stack* obj) { obj->stkSize--; }
int stackTop(Stack* obj) { return obj->stk[obj->stkSize - 1]; }
bool stackEmpty(Stack* obj) { return obj->stkSize == 0; }
void stackFree(Stack* obj) { free(obj->stk); }
typedef struct {
  Stack* inStack;
  Stack* outStack;
} MyQueue;
MyQueue* myQueueCreate() {
  MyQueue* ret = malloc(sizeof(MyQueue));
  ret->inStack = stackCreate(100);
  ret->outStack = stackCreate(100);
  return ret;
}
void in2out(MyQueue* obj) {
  while (!stackEmpty(obj->inStack)) {
    stackPush(obj->outStack, stackTop(obj->inStack));
    stackPop(obj->inStack);
  }
}
void myQueuePush(MyQueue* obj, int x) { stackPush(obj->inStack, x); }
int myQueuePop(MyQueue* obj) {
  if (stackEmpty(obj->outStack)) {
    in2out(obj);
  }
  int x = stackTop(obj->outStack);
  stackPop(obj->outStack);
  return x;
}
int myQueuePeek(MyQueue* obj) {
  if (stackEmpty(obj->outStack)) {
    in2out(obj);
  }
  return stackTop(obj->outStack);
}
bool myQueueEmpty(MyQueue* obj) {
  return stackEmpty(obj->inStack) && stackEmpty(obj->outStack);
}
void myQueueFree(MyQueue* obj) {
  stackFree(obj->inStack);
  stackFree(obj->outStack);
}

class MyQueue {
  stack<int> in;
  stack<int> out;
  void inToOut() {
    while (!in.empty()) {
      out.push(in.top());
      in.pop();
    }
  }

 public:
  MyQueue() {}
  void push(int x) { in.push(x); }
  int pop() {
    if (out.empty()) {
      inToOut();
    }

    int t = out.top();
    out.pop();
    return t;
  }
  int peek() {
    if (out.empty()) {
      inToOut();
    }
    return out.top();
  }
  bool empty() { return out.empty() && in.empty(); }
};
/*
剑指Offer09用两个栈实现队列

用两个栈实现一个队列。队列的声明如下，
请实现它的两个函数appendTail和deleteHead，
分别完成在队列尾部插入整数和在队列头部删除整数的功能。
若队列中没有元素，deleteHead操作返回-1。

示例1：
输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]

示例2：
输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]

提示：
1 <= values <= 10000
最多会对appendTail、deleteHead进行10000次调用
*/

typedef struct {
  int* stack1;
  int top1;
  int* stack2;
  int top2;
} CQueue;
CQueue* cQueueCreate() {
  CQueue* q = (CQueue*)malloc(sizeof(CQueue));
  q->stack1 = (int*)malloc(sizeof(int) * 10000);
  q->stack2 = (int*)malloc(sizeof(int) * 10000);
  q->top1 = 0;
  q->top2 = 0;
  return q;
}
void cQueueAppendTail(CQueue* obj, int value) {
  obj->stack1[obj->top1++] = value;
}
int cQueueDeleteHead(CQueue* obj) {
  if (obj->top2 == 0) {
    while (obj->top1 > 0) {
      obj->stack2[obj->top2++] = obj->stack1[obj->top1 - 1];
      --obj->top1;
    }
  }
  if (obj->top2 > 0) {
    --obj->top2;
    return obj->stack2[obj->top2];
  }
  return -1;
}
void cQueueFree(CQueue* obj) {
  free(obj->stack1);
  free(obj->stack2);
  free(obj);
}