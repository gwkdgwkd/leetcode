/*
根据逆波兰表示法，求表达式的值，有效的算符包括+、-、*、/。
每个运算对象可以是整数，也可以是另一个逆波兰表达式。
注意两个整数之间的除法只保留整数部分，可以保证给定的逆波兰表达式总是有效的。
换句话说，表达式总会得出有效数值且不存在除数为0的情况。

示例1：
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

示例2：
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6

示例3：
输入：tokens = ["10","6","9","3","+","-11",
               "*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

提示：
1 <= tokens.length <= 10^4
tokens[i]是一个算符（"+"、"-"、"*" 或 "/"），
或是在范围[-200, 200]内的一个整数

逆波兰表达式：逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。
平常使用的算式则是一种中缀表达式，如(1 + 2)*(3 + 4)
该算式的逆波兰表达式写法为((1 2 +)(3 4 +)*)
*/

// 剑指OfferII036后缀表达式

// 逆波兰表达式主要有以下两个优点：
// 1.去掉括号后表达式无歧义；
// 2.适合用栈操作，遇到数字则入栈，遇到算符则取出栈顶两个数字计算，并将结果入栈。

// 栈
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
      } else if (tokens[i][0] == '-') {
        push(l - r);
      } else if (tokens[i][0] == '*') {
        push(l * r);
      } else if (tokens[i][0] == '/') {
        push(l / r);
      }
    } else {
      push(atoi(tokens[i]));
    }
  }
  int ret = top();
  pop();

  return ret;
}

// 栈
int evalRPN(char** tokens, int tokensSize) {
  int stack[10000];
  int top = 0;

  for (int i = 0; i < tokensSize; ++i) {
    if (strlen(tokens[i]) == 1 &&
        (tokens[i][0] == '+' || tokens[i][0] == '-' || tokens[i][0] == '*' ||
         tokens[i][0] == '/')) {
      int b = stack[--top];
      int a = stack[--top];
      if (tokens[i][0] == '+') {
        stack[top++] = a + b;
      } else if (tokens[i][0] == '-') {
        stack[top++] = a - b;
      } else if (tokens[i][0] == '*') {
        stack[top++] = a * b;
      } else if (tokens[i][0] == '/') {
        stack[top++] = a / b;
      }
    } else {
      stack[top++] = atoi(tokens[i]);
    }
  }
  return stack[top - 1];
}

class Solution {
 public:
  int evalRPN(vector<string>& tokens) {
    stack<int> stk;
    for (int i = 0; i < tokens.size(); ++i) {
      if (tokens[i].size() == 1 &&
          (tokens[i][0] == '+' || tokens[i][0] == '-' || tokens[i][0] == '*' ||
           tokens[i][0] == '/')) {
        int b = stk.top();
        stk.pop();
        int a = stk.top();
        stk.pop();
        if (tokens[i][0] == '+') {
          stk.push(a + b);
        } else if (tokens[i][0] == '-') {
          stk.push(a - b);
        } else if (tokens[i][0] == '*') {
          stk.push(a * b);
        } else if (tokens[i][0] == '/') {
          stk.push(a / b);
        }
      } else {
        stk.push(atoi(tokens[i].c_str()));
      }
    }

    return stk.top();
  }
};