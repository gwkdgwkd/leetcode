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