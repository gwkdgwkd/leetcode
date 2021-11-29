int minInsertions(char* s) {
  int res = 0, need = 0;

  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (s[i] == '(') {
      need += 2;
      if (need % 2 == 1) {
        res++;
        need--;
      }
    }

    if (s[i] == ')') {
      need--;
      if (need == -1) {
        res++;
        need = 1;
      }
    }
  }

  return res + need;
}

// 贪心+模拟栈
int minInsertions(char* s) {
  if (s == NULL) {
    return 0;
  }
  int length = strlen(s);
  int left = 0;
  int ans = 0;
  for (int i = 0; i < length; i++) {
    if (s[i] == '(') {
      left++;
    } else {
      if (i + 1 < length && s[i + 1] == ')') {
        i++;
      } else {
        ans++;
      }
      left--;          //消去一个左括号。
      if (left < 0) {  //增加一个左括号。
        left++;
        ans++;
      }
    }
  }
  return ans + left * 2;
}