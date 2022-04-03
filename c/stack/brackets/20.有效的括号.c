/*
给定一个只包括'('，')'，'{'，'}'，'['，']'的字符串s，判断字符串是否有效。

有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。

示例1：
输入：s = "()"
输出：true

示例2：
输入：s = "()[]{}"
输出：true

示例3：
输入：s = "(]"
输出：false

示例4：
输入：s = "([)]"
输出：false

示例5：
输入：s = "{[]}"
输出：true

提示：
1 <= s.length <= 104
s仅由括号'()[]{}'组成
*/

#define STACKSIZE 4000
int stackIndex;
char stack[STACKSIZE];
char top() { return stack[stackIndex - 1]; }
void pop() { stackIndex--; }
void push(char c) { stack[stackIndex++] = c; }
bool empty() { return stackIndex == 0; }
bool isValid(char* s) {
  memset(stack, 0, sizeof(stack));
  stackIndex = 0;

  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    if (empty()) {
      push(s[i]);
    } else {
      if ((top() == '(' && s[i] == ')') || (top() == '[' && s[i] == ']') ||
          (top() == '{' && s[i] == '}')) {
        pop();
      } else {
        push(s[i]);
      }
    }
  }

  return empty();
}