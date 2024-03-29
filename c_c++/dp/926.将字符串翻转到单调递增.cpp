/*
如果一个二进制字符串，是以一些0（可能没0）后面跟着一些1（也可能没1）的形式组成的，
那么该字符串是单调递增的，给一个二进制字符串s，可以将任何0翻转为1或者将1翻转为0。
返回使s单调递增的最小翻转次数。

示例1：
输入：s = "00110"
输出：1
解释：翻转最后一位得到00111

示例2：
输入：s = "010110"
输出：2
解释：翻转得到011111，或者是000111

示例3：
输入：s = "00011000"
输出：2
解释：翻转得到00000000。

提示：
1 <= s.length <= 10^5
s[i]为'0'或'1'
*/

// 剑指OfferII092翻转字符

int minFlipsMonoIncr(char* s) {
  int len = strlen(s);
  // dp1[i][0]把[0,i]全部变为0的最少次数
  // dp2[i][1]把[0,i]全部变为形式为000...111的最少次数
  int dp[len][2];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = (s[0] != '0');
  dp[0][1] = 0;
  for (int i = 1; i < len; ++i) {
    if (s[i] == '0') {
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = fmin(dp[i - 1][0], dp[i - 1][1] + 1);
    } else {
      dp[i][0] = dp[i - 1][0] + 1;
      dp[i][1] = fmin(dp[i - 1][0], dp[i - 1][1]);
    }
  }
  return dp[len - 1][1];
}

class Solution {
 public:
  int minFlipsMonoIncr(string s) {
    int n = s.size();

    // 比C语言的慢很多，把vector换成数组，和C语言差不多了
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = (s[0] == '0' ? 0 : 1);
    dp[0][1] = 0;

    for (int i = 1; i < n; ++i) {
      if (s[i] == '0') {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1] + 1);
      } else {
        dp[i][0] = dp[i - 1][0] + 1;
        dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + 1);
      }
    }

    // return dp[n - 1][1];  // 也行，为什么?
    return min(dp[n - 1][0], dp[n - 1][1]);
  }
};