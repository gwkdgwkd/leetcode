/*
只有满足下面几点之一，括号字符串才是有效的：
它是一个空字符串，或者它可以被写成AB（A与B连接）,其中A和B都是有效字符串，
或者它可以被写作(A)，其中A是有效字符串。
给定一个括号字符串s，移动N次，你就可以在字符串的任何位置插入一个括号。
例如，如果s = "()))"，你可以插入一个开始括号为"(()))"或结束括号为"())))" 。
返回为使结果字符串s有效而必须添加的最少括号数。

示例1：
输入：s = "())"
输出：1

示例2：
输入：s = "((("
输出：3

提示：
1 <= s.length <= 1000
s只包含'('和')'字符。
*/

// 栈
int minAddToMakeValid(char* s) {
  int length = strlen(s);
  char* stack = (char*)malloc(sizeof(char) * 1000);
  int top = 1;

  stack[top++] = s[0];
  for (int i = 1; i < length; i++) {
    if ((stack[top - 1] == '(') && (s[i] == ')')) {
      top--;
    } else {
      stack[top++] = s[i];
    }
  }

  return top - 1;
}

int minAddToMakeValid(char* s) {
  int res = 0;   // res记录插入次数
  int need = 0;  // need变量记录右括号的需求量
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == '(') {
      need++;  // 对右括号的需求+1
    }

    if (s[i] == ')') {
      need--;  // 对右括号的需求-1
      if (need == -1) {
        need = 0;
        res++;  // 需插入一个左括号
      }
    }
  }

  return res + need;
}

// 单调栈？
int minAddToMakeValid(char* s) {
  char Stack[500];
  int top = 0;
  int i = 0, count = 0;
  while (s[i] != '\0') {
    if (s[i] == '(') Stack[top++] = '(';

    if (s[i] == ')') {
      if (top == 0)
        count++;
      else
        top--;
    }  // )if

    i++;
  }  // while

  count += top;

  return count;
}