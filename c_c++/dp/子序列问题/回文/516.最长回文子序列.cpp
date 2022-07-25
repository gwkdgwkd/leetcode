/*
给你一个字符串s，找出其中最长的回文子序列，并返回该序列的长度。
子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

示例1：
输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为"bbbb"。

示例2：
输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为"bb"。

提示：
1 <= s.length <= 1000
s仅由小写英文字母组成
*/

// 回⽂⼦串（5）是要连续的，回⽂⼦序列（516）可不是连续的！

// 动态规划
int longestPalindromeSubseq(char* s) {
  int len = strlen(s);
  // dp[i][j]：s在[i,j]范围内最⻓的回⽂⼦序列的⻓度为dp[i][j]
  int dp[len][len];
  memset(dp, 0, sizeof(dp));
  // 当i与j相同，那么dp[i][j]⼀定是等于1的，即：
  // 1.⼀个字符的回⽂⼦序列⻓度就是1
  // 2.其他情况dp[i][j]初始为0就⾏
  for (int i = 0; i < len; ++i) {
    dp[i][i] = 1;
  }

  // dp[i][j]是依赖于dp[i+1][j-1]和dp[i+1][j]，
  // 也就是从矩阵的⻆度来说，dp[i][j]下⼀⾏的数据。
  // 所以遍历i的时候⼀定要从下到上遍历，这样才能保证，下⼀⾏的数据是经过计算的。
  for (int i = len - 1; i >= 0; --i) {
    for (int j = i + 1; j < len; ++j) {
      if (s[i] == s[j]) {
        // 对于[i:j]，如果s[i]与s[j]相同，那么dp[i][j]等于[i+1:j-1]的最长长度加上2
        dp[i][j] = dp[i + 1][j - 1] + 2;
      } else {
        // 对于[i:j]，如果s[i]与s[j]不相同，那么dp[i][j]等于[i+1:j]和[i:j-1]的最大值
        dp[i][j] = fmax(dp[i + 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[0][len - 1];
}

class Solution {
 public:
  int longestPalindromeSubseq(string s) {
    int n = s.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
      dp[i][i] = 1;
    }

    for (int i = n - 1; i >= 0; --i) {
      for (int j = i + 1; j < n; ++j) {
        if (s[i] == s[j]) {
          dp[i][j] = dp[i + 1][j - 1] + 2;
        } else {
          dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
      }
    }

    return dp[0][n - 1];
  }
};
