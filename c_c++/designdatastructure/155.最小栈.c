/*
设计一个支持push，pop，top操作，并能在常数时间内检索到最小元素的栈。
实现MinStack类:
MinStack()初始化堆栈对象。
void push(int val)将元素val推入堆栈。
void pop()删除堆栈顶部的元素。
int top()获取堆栈顶部的元素。
int getMin()获取堆栈中的最小元素。

示例1:
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
输出：
[null,null,null,null,-3,null,0,-2]
解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   -->返回-3
minStack.pop();
minStack.top();      -->返回0
minStack.getMin();   -->返回-2

提示：
-2^31 <= val <= 2^31 - 1
pop、top和getMin操作总是在非空栈上调用
push, pop, top, and getMin最多被调用3*10^4次
*/

// 剑指Offer30包含min函数的栈
// 面试题0302栈的最小值

#define MAX 30000
typedef struct {
  int* stack;
  int* min;
  int top;
  int mtop;
} MinStack;
MinStack* minStackCreate() {
  MinStack* ms = (MinStack*)malloc(sizeof(MinStack));
  ms->stack = (int*)malloc(sizeof(int) * MAX);
  ms->min = (int*)malloc(sizeof(int) * MAX);
  ms->top = 0;
  ms->mtop = 0;

  return ms;
}
void minStackPush(MinStack* obj, int val) {
  obj->stack[obj->top++] = val;
  if (obj->mtop == 0) {
    obj->min[obj->mtop++] = val;
  } else {
    obj->min[obj->mtop] = fmin(val, obj->min[obj->mtop - 1]);
    ++obj->mtop;
  }
}
void minStackPop(MinStack* obj) {
  --obj->top;
  --obj->mtop;
}
int minStackTop(MinStack* obj) { return obj->stack[obj->top - 1]; }
int minStackGetMin(MinStack* obj) { return obj->min[obj->mtop - 1]; }
void minStackFree(MinStack* obj) {
  free(obj->stack);
  free(obj->min);
  free(obj);
  obj = NULL;
}