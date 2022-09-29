/*
给定一个只包括'('，')'，'{'，'}'，'['，']'的字符串s，
判断字符串是否有效。

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
1 <= s.length <= 10^4
s仅由括号'()[]{}'组成
*/

int stackIndex;
char *stack;
char top() { return stack[stackIndex - 1]; }
void pop() { stackIndex--; }
void push(char c) { stack[stackIndex++] = c; }
bool empty() { return stackIndex == 0; }
bool isValid(char *s) {
  int len = strlen(s);
  stack = (char *)malloc(sizeof(char) * len);
  memset(stack, 0, sizeof(char) * len);
  stackIndex = 0;

  for (int i = 0; i < len; ++i) {
    if (empty()) {
      push(s[i]);
      continue;
    }
    if ((top() == '(' && s[i] == ')') || (top() == '[' && s[i] == ']') ||
        (top() == '{' && s[i] == '}')) {
      pop();
    } else {
      push(s[i]);
    }
  }
  free(stack);
  return empty();
}

class Solution {
 public:
  bool isValid(string s) {
    stack<char> stk;

    for (int i = 0; i < s.size(); ++i) {
      if (stk.empty()) {
        stk.push(s[i]);
        continue;
      }
      if ((stk.top() == '{' && s[i] == '}') ||
          (stk.top() == '(' && s[i] == ')') ||
          (stk.top() == '[' && s[i] == ']')) {
        stk.pop();
      } else {
        stk.push(s[i]);
      }
    }

    return stk.empty();
  }
};