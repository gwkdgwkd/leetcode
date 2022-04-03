/*
返回s字典序最小的子序列，该子序列包含 s的所有不同字符，且只包含一次。
注意：该题与316相同

示例1：
输入：s = "bcabc"
输出："abc"

示例2：
输入：s = "cbacdcbc"
输出："acdb"

提示：
1 <= s.length <= 1000
s由小写英文字母组成
*/

char *smallestSubsequence(char *s) {
  if (s == NULL || strlen(s) == 0) {
    return "";
  }
  if (strlen(s) == 1) {
    return s;
  }
  int len = (int)strlen(s);
  char recode[26] = {0};  // 注意，这里需要初始化为0
  for (int i = 0; i < len; i++) {
    recode[s[i] - 'a']++;
  }

  char *stack = (char *)malloc(sizeof(char) * (len + 1));
  int top = -1;

  int isExist;
  for (int i = 0; i < len; i++) {
    isExist = 0;
    for (int j = 0; j <= top; j++) {
      if (s[i] == stack[j]) {
        isExist = 1;
        break;
      }
    }

    if (isExist) {
      recode[s[i] - 'a']--;
    } else {
      while (top > -1 && stack[top] > s[i] && recode[stack[top] - 'a'] > 1) {
        //如果栈顶字符比当前大，并且后边还会出现
        recode[stack[top] - 'a']--;
        //出栈
        top--;
      }
      //入栈
      stack[++top] = s[i];
    }
  }
  stack[++top] = '\0';
  return stack;
}