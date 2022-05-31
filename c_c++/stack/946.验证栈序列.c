/*
给定pushed和popped两个序列，每个序列中的值都不重复，
只有当它们可能是在最初空栈上进行的推入push和弹出pop操作序列的结果时，
返回true；否则，返回false。

示例1：
输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

示例2：
输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
输出：false
解释：1不能在2之前弹出。

提示：
1 <= pushed.length <= 1000
0 <= pushed[i] <= 1000
pushed的所有元素互不相同
popped.length == pushed.length
popped是pushed的一个排列
*/

bool validateStackSequences(int* pushed, int pushedSize, int* popped,
                            int poppedSize) {
  int stack[pushedSize];
  int top = 0;
  int i = 0;
  int j = 0;

  while (i < pushedSize) {  // 模拟入栈操作
    stack[top++] = pushed[i];
    // 每次都拿栈顶元素与poped比较，如果相等，证明需要出栈
    while (top > 0 && stack[top - 1] == popped[j]) {
      --top;
      ++j;
    }
    ++i;
  }
  return top == 0;  // 如果栈不为空，证明出栈顺序不对
}

// 剑指Offer31栈的压入、弹出序列
// 0 <= pushed.length == popped.length <= 1000
// 0 <= pushed[i], popped[i] < 1000
bool validateStackSequences(int* pushed, int pushedSize, int* popped,
                            int poppedSize) {
  if (pushedSize == 0) return true;

  int stack[pushedSize];
  int top = 0;
  int i = 0;
  int j = 0;

  while (i < pushedSize) {
    stack[top++] = pushed[i];
    while (top > 0 && stack[top - 1] == popped[j]) {
      --top;
      ++j;
    }
    ++i;
  }
  return top == 0;
}