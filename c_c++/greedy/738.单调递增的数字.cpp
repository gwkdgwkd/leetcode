/*
当且仅当每个相邻位数上的数字x和y满足x<=y时，
称这个整数是单调递增的。
给定一个整数n，返回小于或等于n的最大数字，且数字呈单调递增。

示例1:
输入: n = 10
输出: 9

示例2:
输入: n = 1234
输出: 1234

示例3:
输入: n = 332
输出: 299

提示: 0 <= n <= 10^9
*/

// 暴力法，超时
bool checkNum(int num) {
  int max = 10;
  while (num) {
    int t = num % 10;
    if (max >= t)
      max = t;
    else
      return false;
    num = num / 10;
  }
  return true;
}
int monotoneIncreasingDigits(int n) {
  for (int i = n; i >= 0; --i) {
    if (checkNum(i)) {
      return i;
    }
  }

  return 0;
}

// 贪心算法
void itoa(int num, char* str, int* strSize) {
  *strSize = 0;
  while (num > 0) {
    str[(*strSize)++] = num % 10 + '0';
    num /= 10;
  }
  for (int i = 0; i < (*strSize) / 2; i++) {
    int tmp = str[i];
    str[i] = str[(*strSize) - 1 - i];
    str[(*strSize) - 1 - i] = tmp;
  }
}
int monotoneIncreasingDigits(int n) {
  int strNSize;
  char strN[11];
  itoa(n, strN, &strNSize);
  int i = 1;
  while (i < strNSize && strN[i - 1] <= strN[i]) {
    i += 1;
  }
  if (i < strNSize) {
    while (i > 0 && strN[i - 1] > strN[i]) {
      strN[i - 1] -= 1;
      i -= 1;
    }
    for (i += 1; i < strNSize; ++i) {
      strN[i] = '9';
    }
  }
  return atoi(strN);
}

class Solution {
 public:
  int monotoneIncreasingDigits(int n) {
    string strN = to_string(n);
    int i = 1;
    while (i < strN.length() && strN[i - 1] <= strN[i]) {
      i += 1;
    }
    if (i < strN.length()) {
      while (i > 0 && strN[i - 1] > strN[i]) {
        strN[i - 1] -= 1;
        i -= 1;
      }
      for (i += 1; i < strN.length(); ++i) {
        strN[i] = '9';
      }
    }
    return stoi(strN);
  }
};