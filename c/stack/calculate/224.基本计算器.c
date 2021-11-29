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
    if (isdigit(ch)) { /* 数字处理 */
      num = num * 10 + (ch - '0');
    }
    if (ch == '(') { /* 遇到左括号, 递归处理 */
      s++;
      num = dfs(&s);
    }
    /* 处理加减号, 左右括号, 结束符 */
    if ((!isdigit(ch) && ch != ' ') || *(s + 1) == '\0') {
      if (sign == '+') { /* 可以扩展乘除运算 */
        stack[top++] = num;
      } else if (sign == '-') {
        stack[top++] = -num;
      }
      sign = ch;
      num = 0;
      if (ch == ')') { /* 遇到右括号, 退出本次处理, 更新字符串起始 */
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