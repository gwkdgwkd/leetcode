/*
给你一个字符串表达式s，请你实现一个基本计算器来计算并返回它的值。
整数除法仅保留整数部分。
你可以假设给定的表达式总是有效的。所有中间结果将在[-2^31, 2^31 - 1]的范围内。
注意：不允许使用任何将字符串作为数学表达式计算的内置函数，比如eval()。

示例1：
输入：s = "3+2*2"
输出：7

示例2：
输入：s = " 3/2 "
输出：1

示例3：
输入：s = " 3+5 / 2 "
输出：5

提示：
1 <= s.length <= 3 * 10^5
s由整数和算符('+', '-', '*', '/')组成，中间由一些空格隔开
s表示一个有效表达式
表达式中的所有整数都是非负整数，且在范围[0, 2^31 - 1]内
题目数据保证答案是一个32-bit整数
*/

// 面试题1626计算器

int calculate(char* s) {
  int n = strlen(s);
  int stk[n], top = 0;
  char preSign = '+';
  int num = 0;
  for (int i = 0; i < n; ++i) {
    if (isdigit(s[i])) {
      num = num * 10 + (int)(s[i] - '0');
    }
    if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1) {
      switch (preSign) {
        case '+':
          stk[top++] = num;
          break;
        case '-':
          stk[top++] = -num;
          break;
        case '*':
          stk[top - 1] *= num;
          break;
        default:
          stk[top - 1] /= num;
      }
      preSign = s[i];
      num = 0;
    }
  }
  int ret = 0;
  for (int i = 0; i < top; i++) {
    ret += stk[i];
  }
  return ret;
}