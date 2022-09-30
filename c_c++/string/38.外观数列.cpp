/*
给定一个正整数n，输出外观数列的第n项。
外观数列是一个整数序列，从数字1开始，
序列中的每一项都是对前一项的描述。
你可以将其视作是由递归公式定义的数字字符串序列：
countAndSay(1) = "1"
countAndSay(n)是对countAndSay(n-1)的描述，
然后转换成另一个数字字符串。
前五项如下：
1.1
2.11
3.21
4.1211
5.111221
第一项是数字1
描述前一项，这个数是1即一个1，记作11；
描述前一项，这个数是11即二个1，记作21；
描述前一项，这个数是21即一个2+一个1，记作1211；
描述前一项，这个数是1211即一个1+一个2+二个1，记作111221；
要描述一个数字字符串，首先要将字符串分割为最小数量的组，
每个组都由连续的最多相同字符组成。
然后对于每个组，先描述字符的数量，然后描述字符，形成一个描述组。
要将描述转换为数字字符串，
先将每组中的字符数量用数字替换，再将所有描述组连接起来。

示例1：
输入：n = 1
输出："1"
解释：这是一个基本样例。

示例2：
输入：n = 4
输出："1211"
解释：
countAndSay(1) = 1
countAndSay(2) = 读1 = 一个1 = 11
countAndSay(3) = 读11 = 二个1 = 21
countAndSay(4) = 读21 = 一个2 + 一个1 = 12 + 11 = 1211

提示：1 <= n <= 30
*/

char *countAndSay(int n) {
  int size = 5000;
  char *result = (char *)malloc(sizeof(char) * size);
  memset(result, 0, sizeof(char) * size);
  result[0] = '1';
  char temp[size];
  for (int i = 2; i <= n; ++i) {
    int len = strlen(result);
    int count = 1;
    memset(temp, 0, sizeof(temp));
    for (int j = 1; j <= len; ++j) {
      if (result[j] != result[j - 1] || j == len) {
        sprintf(temp + strlen(temp), "%d%c", count, result[j - 1]);
        temp[strlen(temp)] = 0;
        count = 1;
      } else {
        ++count;
      }
    }
    memcpy(result, temp, sizeof(char) * strlen(temp));
    result[strlen(temp)] = 0;
  }
  return result;
}

class Solution {
 public:
  string countAndSay(int n) {
    string prev = "1";
    for (int i = 2; i <= n; ++i) {
      int n = prev.size();
      string curr;
      int left = 0;
      int right = 0;
      // 与[面试题0106字符串压缩]写法类似：
      while (right < n) {
        if (prev[left] != prev[right]) {
          curr += to_string(right - left);
          curr += prev[left];
          left = right;
        }
        if (right == n - 1) {
          curr += to_string(right - left + 1);
          curr += prev[left];
          left = right;
        }
        ++right;
      }
      prev = curr;
    }

    return prev;
  }
};