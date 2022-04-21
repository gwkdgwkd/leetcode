/*
定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数在该栈中，
调用min、push及pop的时间复杂度都是O(1)。

示例:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();   --> 返回 0.
minStack.min();   --> 返回 -2.

提示：各函数的调用总次数不超过20000次

注意：本题与155题相同
*/

typedef struct {
  int* stack;
  int top1;
  int* min;
  int top2;
} MinStack;
MinStack* minStackCreate() {
  MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
  obj->stack = (int*)malloc(sizeof(int) * 20000);
  obj->min = (int*)malloc(sizeof(int) * 20000);
  obj->top1 = 0;
  obj->top2 = 0;
  return obj;
}
void minStackPush(MinStack* obj, int x) {
  obj->stack[obj->top1++] = x;
  if (obj->top2 == 0) {
    obj->min[obj->top2++] = x;
  } else {
    obj->min[obj->top2] = fmin(x, obj->min[obj->top2 - 1]);
    ++obj->top2;
  }
}
void minStackPop(MinStack* obj) {
  --obj->top1;
  --obj->top2;
}
int minStackTop(MinStack* obj) { return obj->stack[obj->top1 - 1]; }
int minStackMin(MinStack* obj) { return obj->min[obj->top2 - 1]; }
void minStackFree(MinStack* obj) {
  free(obj->stack);
  free(obj->min);
  free(obj);
  obj = NULL;
}