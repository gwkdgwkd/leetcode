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