// 题目描述：
// 现基本计算器以计算简单表达式字符串。
// 表达式字符串可以包含左括号（和右括号）、加号+或减号、非负整数和空格。
// 表达式字符串只包含非负整数、+、-、*、/运算符、左右括号和空格。整数除法应该截断为零。
// 您可以假定给定的表达式总是有效的。所有中间结果将在范围内[-2147483648，2147483647]
// "1 + 1" = 2
// " 6-4 / 2 " = 4
// "2*(5+5*2)/3+(6/2+8)" = 21
// "(2+6* 3+5- (3*14/7+2)*5)+3"=-12

// 解题思路:
// 逆波兰计算器的原理是使用逆波兰表达式来计算出表达式的值，我们人类能够熟练使用的是中缀表达式，
// 比如2×(9+6/3-5)+4就是一个中缀表达式，但是看到上面的简单计算器就知道处理起来很麻烦。
// 于是有一种逆波兰计算器，计算是在逆波兰表达式（也叫做后缀表达式）的基础上。
// 逆波兰计算器的计算过程为：从左到右扫描后缀表达式，遇到数字就入栈，遇到操作符就从栈弹出两个数字，
// 然后计算得到的值继续入栈，继续扫描表达式，直到扫描完毕得到结果。
// 从逆波兰计算器的扫描过程可以看到，过程特别简单，代码写起来也比较容易。
// 但现在的难点在于：如何把中缀表达式转成后缀表达式？
// 1.初始化两个栈：运算符栈s1和存储中间结果的栈s2；
// 2.从左到右扫描中缀表达式；
// 3.遇到操作数时，压入到栈s2；
// 4.遇到运算符时：
//  a.如果s1为空或s1栈顶为左括号"("，则压入到s1；
//  b.不满足a，则和s1栈顶运算符比较优先级，高于，则压入s1；
//  c.不满足a和b，弹出s1栈顶运算符并压入到s2，再次回到b。
// 5.遇到右括号")“时，依此弹出s1并压入s2，直到遇到左括号”)"为止，此时丢掉一对括号；
// 6.重复2-5，直到扫描完毕；
// 7.将s2栈弹出压入到s1，然后s1弹出全部，弹出的顺序即为后缀表达式。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMLEN 11

void printStack(char s[][NUMLEN], int len) {
  for (int i = 0; i < len; ++i) {
    printf("%s ", s[i]);
  }
  printf("\n");
}

int priority(char o) {
  if ('+' == o || '-' == o) {
    return 0;
  } else if ('*' == o || '/' == o) {
    return 1;
  } else {
    return -1;
  }
}

int toRPN(char* s, char RPN[][NUMLEN]) {
  int len = strlen(s);

  // 1.初始化两个栈：运算符栈s1和存储中间结果的栈s2；
  char operator[len][NUMLEN];  // s1
  memset(operator, 0, sizeof(operator));
  int topO = 0;
  char tmp[len][NUMLEN];  // s2
  memset(tmp, 0, sizeof(tmp));
  int topT = 0;

  for (int i = 0; i < len; ++i) {  // 2.从左到右扫描中缀表达式；
    switch (s[i]) {
      case '+':
      case '-':
      case '*':
      case '/':
        // 4.遇到运算符时：
        //   a.如果s1为空或s1栈顶为左括号"("，则压入到s1；
        if (topO == 0 || operator[topO - 1][0] == '(') {
          operator[topO++][0] = s[i];
          break;
        }
        //   b.不满足a，则和s1栈顶运算符比较优先级，高于，则压入s1；
        //   c.不满足a和b，弹出s1栈顶运算符并压入到s2，再次回到b。
        while (topO > 0 && priority(s[i]) <= priority(operator[topO - 1][0])) {
          tmp[topT++][0] = operator[topO - 1][0];
          --topO;
        }
        operator[topO++][0] = s[i];
        break;
      case '(':
        operator[topO++][0] = s[i];
        break;
      case ')':
        // 5.遇到右括号")“时，依此弹出s1并压入s2，直到遇到左括号”)"为止，此时丢掉一对括号；
        while (operator[topO - 1][0] != '(') {  // (被丢弃
          tmp[topT++][0] = operator[topO - 1][0];
          --topO;
        }
        --topO;  // (被丢弃
        break;
      case ' ':
        break;
      default: {  // 3.遇到操作数时，压入到栈s2；
        int index = 0;
        while (i < len && s[i] >= '0' && s[i] <= '9') {
          tmp[topT][index++] = s[i];
          ++i;
        }
        --i;  // 写的好丑
        ++topT;
        break;
      }
    }
    // printf("=====%c=====\n", s[i]);
    // printStack(operator, topO);
    // printStack(tmp, topT);
  }

  // 7.将s2栈弹出压入到s1，然后s1弹出全部，弹出的顺序即为后缀表达式。
  while (topT) {
    memcpy(operator[topO++], tmp[topT - 1], strlen(tmp[topT - 1]));
    --topT;
  }
  int index = 0;
  while (topO) {
    memcpy(RPN[index++], operator[topO - 1], strlen(operator[topO - 1]));
    --topO;
  }

  // printStack(RPN, index);

  return index;
}
int calculate(char* s) {
  int len = strlen(s);
  if (len == 0) {
    return 0;
  }
  char RPN[len][NUMLEN];
  memset(RPN, 0, sizeof(RPN));
  int count = toRPN(s, RPN);
  for (int i = 0; i < count; ++i) {
    printf("%s ", RPN[i]);
  }
  printf("\n");

  int res = 0;
  int tmp[count];
  memset(tmp, 0, sizeof(tmp));
  int top = 0;

  int left, right;
  for (int i = 0; i < count; ++i) {
    if (RPN[i][0] == '+' || RPN[i][0] == '-' || RPN[i][0] == '*' ||
        RPN[i][0] == '/') {
      right = tmp[top - 1];
      --top;
      left = tmp[top - 1];
      --top;
      // printf("%d %d\n", left, right);
      switch (RPN[i][0]) {
        case '+':
          res = left + right;
          break;
        case '-':
          res = left - right;
          break;
        case '*':
          res = left * right;
          break;
        case '/':
          res = left / right;
          break;
      }
      tmp[top++] = res;
    } else {
      tmp[top++] = atoi(RPN[i]);
    }
  }
  return res;
}

int main() {
  char* in = "1 + 1";
  printf("%s = %d\n", in, calculate(in));
  // 1 1 +
  // 1 + 1 = 2

  in = " 6-4 / 2 ";
  printf("%s = %d\n", in, calculate(in));
  // 6 4 2 / -
  // 6-4 / 2  = 4

  in = "2*(5+5*2)/3+(6/2+8)";
  printf("%s = %d\n", in, calculate(in));
  // 2 5 5 2 * + * 3 / 6 2 / 8 + +
  // 2*(5+5*2)/3+(6/2+8) = 21

  in = "(2+6* 3+5- (3*14/7+2)*5)+3";
  printf("%s = %d\n", in, calculate(in));
  // 2 6 3 * + 5 + 3 14 * 7 / 2 + 5 * - 3 +
  // (2+6* 3+5- (3*14/7+2)*5)+3 = -12
}
