/*
给出由小写字母组成的字符串S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
在S上反复执行重复项删除操作，直到无法继续删除。
在完成所有重复项删除操作后返回最终的字符串，答案保证唯一。

示例：
输入："abbaca"
输出："ca"
解释：
例如，在"abbaca"中，我们可以删除"bb"由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。
之后我们得到字符串"aaca"，其中又只有"aa"可以执行重复项删除操作，所以最后的字符串为"ca"。

提示：
1 <= S.length <= 20000
S仅由小写英文字母组成。
*/

// 栈
#define STACKSIZE 50000
int stackIndex;
char stack[STACKSIZE];
char top() { return stack[stackIndex - 1]; }
void pop() { stackIndex--; }
void push(char c) { stack[stackIndex++] = c; }
bool empty() { return stackIndex == 0; }
char *removeDuplicates(char *s) {
  memset(stack, 0, sizeof(stack));
  stackIndex = 0;

  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    if (empty()) {
      push(s[i]);
    } else {
      if (top() == s[i]) {
        pop();
      } else {
        push(s[i]);
      }
    }
  }

  char *res = (char *)malloc(sizeof(char) * (stackIndex + 1));
  memcpy(res, stack, sizeof(char) * stackIndex);
  res[stackIndex] = 0;
  return res;
}

// 双指针
char *removeDuplicates(char *s) {
  int len = strlen(s);
  int slow = 0;
  int fast = 0;
  while (fast < len) {
    s[slow] = s[fast];
    if (slow > 0 && s[slow] == s[slow - 1]) {
      slow--;
    } else {
      slow++;
    }
    fast++;
  }
  s[slow] = 0;

  return s;
}