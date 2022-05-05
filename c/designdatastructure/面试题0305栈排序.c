/*
栈排序。编写程序，对栈进行排序使最小元素位于栈顶。
最多只能使用一个其他的临时栈存放数据，但不得将元素复制到别的数据结构（如数组）中。
该栈支持如下操作：push、pop、peek和isEmpty。当栈为空时，peek 返回-1。

示例1:
输入：
["SortedStack", "push", "push", "peek", "pop", "peek"]
[[], [1], [2], [], [], []]
输出：
[null,null,null,1,null,2]

示例2:
输入： 
["SortedStack", "pop", "pop", "push", "pop", "isEmpty"]
[[], [], [], [1], [], []]
输出：
[null,null,null,null,null,true]

说明:栈中的元素数目在[0, 5000]范围内。
*/

typedef struct {
  int top;
  int stack[5005];
} SortedStack;
SortedStack tmp = {0};  // 临时栈
SortedStack* sortedStackCreate() {
  SortedStack* obj = (SortedStack*)malloc(sizeof(SortedStack));
  memset(obj, 0, sizeof(SortedStack));
  obj->top = -1;
  tmp.top = -1;
  return obj;
}
void Mypush(SortedStack* s, int val) { s->stack[++s->top] = val; }
int MyPop(SortedStack* s, int* val) {
  if (s->top >= 0) {
    *val = s->stack[s->top];
    s->top--;
    return true;
  }
  return false;
}
void sortedStackPush(SortedStack* obj, int val) {
  if (obj->top < 0) {
    obj->stack[++obj->top] = val;
    return;
  } else {
    while (val > obj->stack[obj->top] &&
           obj->stack[obj->top] != -1) {  // 主栈出栈，临时栈入栈
      int value = 0;
      if (MyPop(obj, &value)) {
        Mypush(&tmp, value);
      }
    }
    Mypush(obj, val);       // val入主栈
    while (tmp.top >= 0) {  // 临时栈出栈，主栈入栈
      int value = 0;
      MyPop(&tmp, &value);
      Mypush(obj, value);
    }
  }
}
void sortedStackPop(SortedStack* obj) {
  if (obj->top < 0) {
    return;
  }
  obj->top--;
}
int sortedStackPeek(SortedStack* obj) {
  if (obj->top >= 0) {
    return obj->stack[obj->top];
  }
  return -1;
}
bool sortedStackIsEmpty(SortedStack* obj) {
  if (obj->top < 0) {
    return true;
  }
  return false;
}
void sortedStackFree(SortedStack* obj) { free(obj); }