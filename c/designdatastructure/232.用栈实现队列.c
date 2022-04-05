/*
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现MyQueue类：
void push(int x)将元素x推到队列的末尾
int pop()从队列的开头移除并返回元素
int peek()返回队列开头的元素
boolean empty()如果队列为空，返回true；否则，返回false

说明：
你只能使用标准的栈操作——也就是只有pushtotop,peek/popfromtop,size和isempty操作是合法的。
你所使用的语言也许不支持栈。你可以使用list或者deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

示例1：
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
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