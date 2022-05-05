/*
三合一。描述如何只用一个数组来实现三个栈。
你应该实现push(stackNum, value)、pop(stackNum)、isEmpty(stackNum)、peek(stackNum)方法。
stackNum表示栈下标，value表示压入的值。
构造函数会传入一个stackSize参数，代表每个栈的大小。

示例1:
输入：
["TripleInOne", "push", "push", "pop", "pop", "pop", "isEmpty"]
[[1], [0, 1], [0, 2], [0], [0], [0], [0]]
输出：
[null, null, null, 1, -1, -1, true]
说明：当栈为空时pop, peek返回-1，当栈满时push不压入元素。

示例2:
输入：
["TripleInOne", "push", "push", "push", "pop", "pop", "pop", "peek"]
[[2], [0, 1], [0, 2], [0, 3], [0], [0], [0], [0]]
输出：
[null, null, null, null, 2, 1, -1, -1]

提示： 0 <= stackNum <= 2
*/

typedef struct {
  int top[3];  // 栈顶指针，注意要分成三个
  int size;    // 单个栈的总长度，需要保存下来出入栈时使用
  int* data;  // 只是用一个数组进行数据存储，长度设为三倍的栈总长
} TripleInOne;

TripleInOne* tripleInOneCreate(int stackSize) {
  TripleInOne* obj = (TripleInOne*)malloc(sizeof(TripleInOne));
  obj->data = (int*)calloc(3 * stackSize, sizeof(int));
  obj->size = stackSize;
  obj->top[0] = -1;
  obj->top[1] = -1;
  obj->top[2] = -1;
  return obj;
}
void tripleInOnePush(TripleInOne* obj, int stackNum, int value) {
  if (obj->top[stackNum] == obj->size - 1) {
  } else {
    obj->top[stackNum]++;
    obj->data[obj->top[stackNum] + stackNum * obj->size] = value;
  }
}
int tripleInOnePop(TripleInOne* obj, int stackNum) {
  if (obj->top[stackNum] == -1) {
    return -1;
  } else {
    int value = obj->data[obj->top[stackNum] + stackNum * obj->size];
    obj->top[stackNum]--;
    return value;
  }
}
int tripleInOnePeek(TripleInOne* obj, int stackNum) {
  if (obj->top[stackNum] == -1) {
    return -1;
  }
  return obj->data[obj->top[stackNum] + stackNum * obj->size];
}
bool tripleInOneIsEmpty(TripleInOne* obj, int stackNum) {
  return obj->top[stackNum] == -1;
}
void tripleInOneFree(TripleInOne* obj) {
  free(obj->data);
  free(obj);
}