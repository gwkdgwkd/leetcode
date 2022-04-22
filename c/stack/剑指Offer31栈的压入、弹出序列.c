/*
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。
假设压入栈的所有数字均不相等。
例如，序列{1,2,3,4,5}是某栈的压栈序列，
序列{4,5,3,2,1}是该压栈序列对应的一个弹出序列，
但{4,3,5,1,2}就不可能是该压栈序列的弹出序列。

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
0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed是popped的排列。

注意：本题与946题相同
*/

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