
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define true 1
#define false 0
#define MAX 2000
char *stack;
int idx;
void pop() { --idx; }
char top() { return stack[idx - 1]; }
void push(char c) { stack[idx++] = c; }
bool empty() { return idx == 0; }
char *decodeString(char *s) {
  stack = (char *)malloc(MAX * sizeof(char));
  memset(stack, 0, MAX * sizeof(char));
  idx = 0;

  char temp[20];
  int index1 = 0;
  int len = strlen(s);
  int nums[400];
  int index2 = 0;

  int i = 0;
  while (i < len) {
    if (s[i] == '[') {  // 入栈
      push(s[i++]);
    } else if (s[i] >= '0' && s[i] <= '9') {  // 获取数字
      nums[index2] = 0;
      while (i < len && s[i] >= '0' && s[i] <= '9') {
        nums[index2] = nums[index2] * 10 + s[i] - '0';
        ++i;
      }
      ++index2;
    } else if (s[i] == ']') {  // 出栈，把重复的结果入栈
      while (top() != '[') {
        temp[index1++] = top();
        pop();
      }
      pop();
      int num = nums[--index2];
      for (int j = 0; j < num; ++j) {
        for (int k = index1 - 1; k >= 0; --k) {
          push(temp[k]);
        }
      }
      index1 = 0;
      ++i;
    } else {  // 字母入栈
      push(s[i++]);
    }
  }
  stack[idx] = 0;

  return stack;
}

// 递归
#define STR_LEN 2000
char *decodeStringCore(char *s, char **e) {
  char *ret = (char *)malloc(sizeof(char) * STR_LEN);
  char *buf, *end = NULL;
  int count = 0, idx = 0;

  while (*s != '\0') {
    if (isalpha(*s)) {
      ret[idx++] = *s;
    } else if (isdigit(*s)) {
      count = 10 * count + *s - '0';
    } else if (*s == '[') {
      buf = decodeStringCore(s + 1, &end);
      while (count) {
        strcpy(ret + idx, buf);
        idx += strlen(buf);
        count--;
      }
      s = end;
    } else if (*s == ']') {
      *e = s;
      ret[idx] = '\0';
      return ret;
    }
    s++;
  }
  ret[idx] = '\0';
  return ret;
}
char *decodeString1(char *s) {
  char *end = NULL;
  return decodeStringCore(s, &end);
}

int main() {
  char *ret = decodeString("3[a]2[bc]");
  printf("%s\n", ret);  // aaabcbc
  ret = decodeString("3[a2[c]]");
  printf("%s\n", ret);  // accaccacc
  ret = decodeString("1[1[p]1[1[j]]]");
  printf("%s\n", ret);  // pj

  ret = decodeString1("3[a]2[bc]");
  printf("%s\n", ret);  // aaabcbc
  ret = decodeString1("3[a2[c]]");
  printf("%s\n", ret);  // accaccacc
  ret = decodeString1("1[1[p]1[1[j]]]");
  printf("%s\n", ret);  // pj
}