/*
二进制数转字符串。
给定一个介于0和1之间的实数（如0.72），类型为double，打印它的二进制表达式。
如果该数字无法精确地用32位以内的二进制表示，则打印ERROR。

示例1：
输入：0.625
输出："0.101"

示例2：
输入：0.1
输出："ERROR"
提示：0.1无法被二进制准确表示

提示：
32位包括输出中的"0."这两位。
题目保证输入用例的小数位数最多只有6位
*/

// 十进制小数转换为N进制小数的方法为，乘N取整法：
// 所谓乘N取整法是将十进制的小数乘以N，得到的整数部分作为小数点后第一位。
// 剩余的小数部分再乘以N，得到的整数部分作为小数点后第二位。
// 直到剩余小数部分为0，或达到一定精度为止。
#define MAX_LEN 32
char* printBin(double num) {
  if (num < 0 || num > 1) {
    return "ERROR";
  }

  char* res = (char*)calloc(MAX_LEN + 1, sizeof(char));
  if (res == NULL) {
    return NULL;
  }

  res[0] = '0';
  res[1] = '.';

  int index = 2;
  double temp = num;
  while (index < MAX_LEN && temp != 0) {
    res[index++] = (int)(temp * 2) + '0';  // 加'0'的作用是将数值转换为字符
    if (temp * 2 >= 1) {
      temp = temp * 2 - 1;
    } else {
      temp = temp * 2;
    }
  }

  if (temp != 0) {
    return "ERROR";
  } else {
    return res;
  }
}

class Solution {
 public:
  string printBin(double num) {
    string ans = "0.";
    while (num != 0) {
      num *= 2;
      if (num >= 1) {
        // 乘2后num>=1，说明此时整数部分为1，取完该整数部分1后，
        // num接着利用的还是其小数部分，所以要减掉整数部分（即1）：
        ans += "1";
        num -= 1;
      } else {  // 小于1说明整数部分为0，取该整数部分0
        ans += "0";
      }
      if (ans.size() > 32) return "ERROR";
    }
    return ans;
  }
};
