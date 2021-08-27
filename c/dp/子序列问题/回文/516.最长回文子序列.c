/*
 * @lc app=leetcode.cn id=516 lang=c
 *
 * [516] 最长回文子序列
 */

// @lc code=start

// 回⽂⼦串是要连续的，回⽂⼦序列可不是连续的！

// 动态规划
int longestPalindromeSubseq(char* s) {
  int len = strlen(s);
  // dp[i][j]：字符串s在[i,j]范围内最⻓的回⽂⼦序列的⻓度为dp[i][j]。
  int dp[len][len];
  memset(dp, 0, sizeof(dp));
  // 当i与j相同，那么dp[i][j]⼀定是等于1的，即：⼀个字符的回⽂⼦序列⻓度就是1。其他情况dp[i][j]初始为0就⾏。
  for (int i = 0; i < len; ++i) {
    dp[i][i] = 1;
  }

  // dp[i][j]是依赖于dp[i+1][j-1]和dp[i+1][j]，也就是从矩阵的⻆度来说，dp[i][j]下⼀⾏的数据。
  // 所以遍历i的时候⼀定要从下到上遍历，这样才能保证，下⼀⾏的数据是经过计算的。
  for (int i = len - 1; i >= 0; --i) {
    for (int j = i + 1; j < len; ++j) {
      if (s[i] == s[j]) {
        // 如果s[i]与s[j]相同，那么dp[i][j]等于掐头去尾除去s[i]和s[j]两个字符后的最长长度加上2
        dp[i][j] = dp[i + 1][j - 1] + 2;
      } else {
        // 如果s[i]与s[j]不相同，说明s[i]和s[j]的同时加⼊ 并不能增加[i,j]区间回⽂⼦串的⻓度，那么分别加⼊s[i]、s[j]看看哪⼀个可以组成最⻓的回⽂⼦序列。
        // 加⼊s[j]的回⽂⼦序列⻓度为dp[i+1][j]。
        // 加⼊s[i]的回⽂⼦序列⻓度为dp[i][j-1]。
        // 那么dp[i][j]⼀定是取最⼤的，即：
        dp[i][j] = fmax(dp[i + 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[0][len - 1];
}

// @lc code=end
