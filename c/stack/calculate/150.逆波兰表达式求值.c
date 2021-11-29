// 栈
// 平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
// 该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
// 逆波兰表达式主要有以下两个优点：
//  去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
//  适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中。
#define STACKSIZE 5000
int stackIndex;
int stack[STACKSIZE];
int top() { return stack[stackIndex - 1]; }
void pop() { stackIndex--; }
void push(int c) { stack[stackIndex++] = c; }
bool empty() { return stackIndex == 0; }
int evalRPN(char** tokens, int tokensSize) {
  stackIndex = 0;
  memset(stack, 0, sizeof(stack));

  for (int i = 0; i < tokensSize; ++i) {
    if (strlen(tokens[i]) == 1 &&
        (tokens[i][0] == '+' || tokens[i][0] == '-' || tokens[i][0] == '*' ||
         tokens[i][0] == '/')) {
      int l, r;
      r = top();
      pop();
      l = top();
      pop();
      if (tokens[i][0] == '+') {
        push(l + r);

        // printf("%d + %d = %d\n",l,r,l+r);
      } else if (tokens[i][0] == '-') {
        push(l - r);
        // printf("%d - %d = %d\n",l,r,l - r);
      } else if (tokens[i][0] == '*') {
        push(l * r);
        // printf("%d * %d = %d\n",l,r,l*r);
      } else if (tokens[i][0] == '/') {
        push(l / r);
        // printf("%d / %d = %d\n",l,r,l/r);
      }
    } else {
      push(atoi(tokens[i]));
    }
  }
  int ret = top();
  pop();

  return ret;
}