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