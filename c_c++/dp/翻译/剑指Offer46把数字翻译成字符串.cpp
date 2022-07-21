/*
给定一个数字，我们按照如下规则把它翻译为字符串：0翻译成“a”，
1翻译成“b”，……，11翻译成“l”，……，25翻译成“z”。
一个数字可能有多个翻译。
请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

示例1:
输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"

提示： 0 <= num < 2^31
*/

int translateNum(int num) {
  if (num < 10) {
    return 1;
  }

  int len = 0;
  char nums[10];
  while (num) {
    nums[len++] = num % 10;
    num = num / 10;
  }

  for (int i = 0, j = len - 1; i < j; ++i, --j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
  }

  int dp[len];
  dp[0] = 1;
  dp[1] = (nums[0] * 10 + nums[1] < 26 && nums[0] * 10 + nums[1] > 9)
              ? dp[0] + 1
              : dp[0];
  for (int i = 2; i < len; ++i) {
    int k = nums[i - 1] * 10 + nums[i];
    if (k > 9 && k < 26) {
      dp[i] = dp[i - 1] + dp[i - 2];
    } else {
      dp[i] = dp[i - 1];
    }
  }

  return dp[len - 1];
}

class Solution {
 public:
  int translateNum(int num) {
    string s = to_string(num);

    int n = s.size();
    if (n == 1) return n;
    vector<int> dp(n, 0);
    dp[0] = 1;
    int k = (s[0] - '0') * 10 + (s[1] - '0');
    if (9 < k && k < 26) {
      dp[1] = dp[0] + 1;
    } else {
      dp[1] = dp[0];
    }

    for (int i = 2; i < n; ++i) {
      k = (s[i - 1] - '0') * 10 + (s[i] - '0');

      if (9 < k && k < 26) {
        dp[i] = dp[i - 1] + dp[i - 2];
      } else {
        dp[i] = dp[i - 1];
      }
    }
    return dp[n - 1];
  }
};