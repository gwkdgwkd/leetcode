/*
堆盘子，设想有一堆盘子，堆太高可能会倒下来。
因此，在现实生活中，盘子堆到一定高度时，就会另外堆一堆盘子。
请实现数据结构SetOfStacks，模拟这种行为。
SetOfStacks应该由多个栈组成，并且在前一个栈填满时新建一个栈。
此外，push()和pop()应该与普通栈的操作方法相同，
也就是说，pop()返回的值，应该跟只有一个栈时的情况一样。
进阶：实现一个popAt(int index)方法，根据指定的子栈，执行pop操作。
当某个栈为空时，应当删除该栈。
当栈中没有元素或不存在该栈时，pop，popAt应返回-1。

示例1:
输入：
["StackOfPlates", "push", "push", "popAt", "pop", "pop"]
[[1], [1], [2], [1], [], []]
输出：
[null, null, null, 2, 1, -1]

示例2:
输入：
["StackOfPlates", "push", "push", "push", "popAt", "popAt", "popAt"]
[[2], [1], [2], [3], [0], [0], [0]]
输出：
[null, null, null, null, 2, 1, 3]
*/

typedef struct {
  int* stack[10001];
  int top[10001];
  int size;
  int cap
} StackOfPlates;
StackOfPlates* stackOfPlatesCreate(int cap) {
  StackOfPlates* ret = calloc(sizeof(StackOfPlates), 1);
  ret->cap = cap;
  return ret;
}
void stackOfPlatesPush(StackOfPlates* obj, int val) {
  if (obj->cap == 0) {
    return;
  }
  if (obj->size == 0 || obj->top[obj->size - 1] == obj->cap) {
    obj->stack[obj->size] = calloc(sizeof(int), obj->cap);
    obj->stack[obj->size][0] = val;
    obj->top[obj->size] = 1;
    obj->size++;
    return;
  }

  obj->stack[obj->size - 1][obj->top[obj->size - 1]] = val;
  obj->top[obj->size - 1]++;
}
int stackOfPlatesPop(StackOfPlates* obj) {
  if (obj->size == 0) {
    return -1;
  }
  int ret = obj->stack[obj->size - 1][obj->top[obj->size - 1] - 1];
  obj->top[obj->size - 1]--;
  if (obj->top[obj->size - 1] == 0) {
    free(obj->stack[obj->size - 1]);
    obj->size--;
  }
  return ret;
}
int stackOfPlatesPopAt(StackOfPlates* obj, int index) {
  if (obj->size < index + 1) {
    return -1;
  }
  int ret = obj->stack[index][obj->top[index] - 1];
  obj->top[index]--;
  if (obj->top[index] == 0) {
    free(obj->stack[index]);
    for (int i = index + 1; i < obj->size; i++) {
      obj->stack[i - 1] = obj->stack[i];
      obj->top[i - 1] = obj->top[i];
    }
    obj->size--;
  }
  return ret;
}
void stackOfPlatesFree(StackOfPlates* obj) {
  for (int i = 0; i < obj->size; i++) {
    free(obj->stack[i]);
  }
  free(obj);
}

class StackOfPlates {
 public:
  StackOfPlates(int cap) { capacity = cap; }
  void push(int val) {
    if (capacity == 0) {
      return;
    }
    if (stks.empty() || stks.back().size() == capacity) {
      stks.emplace_back(stack<int>());
    }
    stks.back().push(val);
  }
  int pop() {
    if (capacity == 0 || stks.empty()) {
      return -1;
    }
    int res = stks.back().top();
    stks.back().pop();
    if (stks.back().empty()) {
      stks.pop_back();
    }
    return res;
  }
  int popAt(int index) {
    if (capacity == 0 || index >= stks.size() || stks[index].empty()) {
      return -1;
    }
    int res = stks[index].top();
    stks[index].pop();
    if (stks[index].empty()) {
      stks.erase(stks.begin() + index);
    }
    return res;
  }

 private:
  vector<stack<int>> stks;
  int capacity;
};