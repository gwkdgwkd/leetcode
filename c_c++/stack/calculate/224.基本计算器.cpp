/*
给一个字符串表达式s，请实现一个基本计算器来计算并返回它的值。
注意：不允许使用任何将字符串作为数学表达式计算的内置函数，如eval()。

示例1：
输入：s = "1 + 1"
输出：2

示例2：
输入：s = " 2-1 + 2 "
输出：3

示例3：
输入：s = "(1+(4+5+2)-3)+(6+8)"
输出：23

提示：
1 <= s.length <= 3 * 10^5
s由数字、'+'、'-'、'('、')'和' '组成
s表示一个有效的表达式
'+'不能用作一元运算(例如，"+1"和"+(2 + 3)"无效)
'-'可以用作一元运算(即"-1"和"-(2 + 3)"是有效的)
输入中不存在两个连续的操作符
每个数字和运行的计算将适合于一个有符号的32位整数
*/

int calculate(char *s) {
  int n = strlen(s);
  int ops[n], top = 0;
  int sign = 1;
  ops[top++] = sign;

  int ret = 0;
  int i = 0;
  while (i < n) {
    if (s[i] == ' ') {
      i++;
    } else if (s[i] == '+') {
      sign = ops[top - 1];
      i++;
    } else if (s[i] == '-') {
      sign = -ops[top - 1];
      i++;
    } else if (s[i] == '(') {
      ops[top++] = sign;
      i++;
    } else if (s[i] == ')') {
      top--;
      i++;
    } else {
      long num = 0;
      while (i < n && s[i] >= '0' && s[i] <= '9') {
        num = num * 10 + s[i] - '0';
        i++;
      }
      ret += sign * num;
    }
  }
  return ret;
}

class Solution {
 public:
  int calculate(string s) {
    stack<int> ops;
    ops.push(1);
    int sign = 1;

    int ret = 0;
    int n = s.length();
    int i = 0;
    while (i < n) {
      if (s[i] == ' ') {
        i++;
      } else if (s[i] == '+') {
        sign = ops.top();
        i++;
      } else if (s[i] == '-') {
        sign = -ops.top();
        i++;
      } else if (s[i] == '(') {
        ops.push(sign);
        i++;
      } else if (s[i] == ')') {
        ops.pop();
        i++;
      } else {
        long num = 0;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
          num = num * 10 + s[i] - '0';
          i++;
        }
        ret += sign * num;
      }
    }
    return ret;
  }
};

// 递归
int dfs(char **str) {
  char *s = *str;
  int len = strlen(s);
  int i = 0;
  int *stack = (int *)malloc(sizeof(int) * len);
  int top = 0;
  int num = 0;
  int res = 0;
  char sign = '+';
  char ch;

  while (*s != '\0') {
    ch = *s;
    if (isdigit(ch)) {  // 数字处理
      num = num * 10 + (ch - '0');
    }
    if (ch == '(') {  // 遇到左括号, 递归处理
      s++;
      num = dfs(&s);
    }
    // 处理加减号, 左右括号, 结束符
    if ((!isdigit(ch) && ch != ' ') || *(s + 1) == '\0') {
      if (sign == '+') {  // 可以扩展乘除运算
        stack[top++] = num;
      } else if (sign == '-') {
        stack[top++] = -num;
      }
      sign = ch;
      num = 0;
      if (ch == ')') {  // 遇到右括号, 退出本次处理, 更新字符串起始
        *str = s;
        break;
      }
    }
    s++;
  }
  while (top > 0) {
    res += stack[--top];
  }
  free(stack);
  return res;
}
int calculate(char *s) { return dfs(&s); }