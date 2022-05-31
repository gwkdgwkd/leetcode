/*
给定一个布尔表达式和一个期望的布尔结果result，
布尔表达式由0(false)、1(true)、&(AND)、|(OR)和^(XOR)符号组成。
实现一个函数，算出有几种可使该表达式得出result值的括号方法。

示例1:
输入: s = "1^0|0|1", result = 0
输出:2
解释: 两种可能的括号方法是
1^(0|(0|1))
1^((0|0)|1)

示例2:
输入: s = "0&0&0&1^1|0", result = 1
输出: 10

提示：运算符的数量不超过19个
*/

// 动态规划
// dp[start][end][0]代表start到end区间内的可得到0的计算方法的数目
// 初始条件位start和end相等的时候
// start和end只需考虑数字1和0的位置，因此step和start以2递增
// j只需考虑运算符的位置，因此同样以2递增
int countEval(char* s, int result) {
  int length = strlen(s);
  int dp[length][length][2];
  memset(dp, 0, sizeof(dp));
  for (int step = 0; step < length; step += 2) {
    for (int i = 0; i + step < length; i += 2) {
      if (step == 0) {
        if (s[i] == '1') {
          dp[i][i + step][1] = 1;
        } else {
          dp[i][i + step][0] = 1;
        }
      } else {
        for (int j = i + 1; j < i + step; j += 2) {
          if (s[j] == '&') {
            dp[i][i + step][0] += dp[i][j - 1][0] * dp[j + 1][i + step][0];
            dp[i][i + step][0] += dp[i][j - 1][0] * dp[j + 1][i + step][1];
            dp[i][i + step][0] += dp[i][j - 1][1] * dp[j + 1][i + step][0];
            dp[i][i + step][1] += dp[i][j - 1][1] * dp[j + 1][i + step][1];
          } else if (s[j] == '|') {
            dp[i][i + step][0] += dp[i][j - 1][0] * dp[j + 1][i + step][0];
            dp[i][i + step][1] += dp[i][j - 1][0] * dp[j + 1][i + step][1];
            dp[i][i + step][1] += dp[i][j - 1][1] * dp[j + 1][i + step][0];
            dp[i][i + step][1] += dp[i][j - 1][1] * dp[j + 1][i + step][1];
          } else {
            dp[i][i + step][0] += dp[i][j - 1][0] * dp[j + 1][i + step][0];
            dp[i][i + step][0] += dp[i][j - 1][1] * dp[j + 1][i + step][1];
            dp[i][i + step][1] += dp[i][j - 1][0] * dp[j + 1][i + step][1];
            dp[i][i + step][1] += dp[i][j - 1][1] * dp[j + 1][i + step][0];
          }
        }
      }
      // printf("dp[%d][%d][0]=%d,dp[%d][%d][1]=%d\n",i,i+step,dp[i][i+step][0],i,i+step,dp[i][i+step][1]);
    }
  }

  return dp[0][length - 1][result];
}

class Solution {
 public:
  int countEval(string s, int result) {
    int n = s.size();

    // dp[start][end][0]代表start到end区间内的可得到0的计算方法的数目
    int dp[n][n][2];  // 区间DP
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++i) {
      if (s[i] == '0' || s[i] == '1') {
        dp[i][i][s[i] - '0'] = 1;
      }
    }

    // 枚举区间长度len，跳步为2，一个数字一个符号
    for (int len = 2; len < n; len += 2) {
      // 枚举区间起点，数字位，跳步为2
      for (int start = 0; start + len < n; start += 2) {
        int end = start + len;
        // 枚举分割点，三种:'&' '|' '^'，跳步为2
        for (int k = start + 1; k <= end - 1; k += 2) {
          if (s[k] == '&') {
            // 结果为0有三种情况： 0&0, 0&1, 1&0
            dp[start][end][0] += dp[start][k - 1][0] * dp[k + 1][end][0];
            dp[start][end][0] += dp[start][k - 1][0] * dp[k + 1][end][1];
            dp[start][end][0] += dp[start][k - 1][1] * dp[k + 1][end][0];
            // 结果为1有一种情况： 1&1
            dp[start][end][1] += dp[start][k - 1][1] * dp[k + 1][end][1];
          }
          if (s[k] == '|') {
            // 结果为0有一种情况： 0|0
            dp[start][end][0] += dp[start][k - 1][0] * dp[k + 1][end][0];
            // 结果为1有三种情况： 0|1, 1|0, 1|1
            dp[start][end][1] += dp[start][k - 1][0] * dp[k + 1][end][1];
            dp[start][end][1] += dp[start][k - 1][1] * dp[k + 1][end][0];
            dp[start][end][1] += dp[start][k - 1][1] * dp[k + 1][end][1];
          }
          if (s[k] == '^') {
            // 结果为0有两种情况： 0^0, 1^1
            dp[start][end][0] += dp[start][k - 1][0] * dp[k + 1][end][0];
            dp[start][end][0] += dp[start][k - 1][1] * dp[k + 1][end][1];
            // 结果为1有两种情况： 0^1, 1^0
            dp[start][end][1] += dp[start][k - 1][0] * dp[k + 1][end][1];
            dp[start][end][1] += dp[start][k - 1][1] * dp[k + 1][end][0];
          }
        }
      }
    }

    return dp[0][n - 1][result];
  }
};