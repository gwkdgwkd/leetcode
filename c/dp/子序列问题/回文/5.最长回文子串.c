/*
 * @lc app=leetcode.cn id=5 lang=c
 *
 * [5] 最长回文子串
 */

// @lc code=start

char* longestPalindrome(char* s) {
  int n = strlen(s);
  if (n == 1) {
    return s;
  }

  bool dp[n][n];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = true;
  }

  int maxlen = 1;
  int start = 0;
  for (int i = n - 2; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      if (s[i] == s[j]) {  // s[i] != s[j],dp[i][j] = false
        if (j - i <= 2) {
          dp[i][j] = true;
        } else {
          dp[i][j] = dp[i + 1][j - 1];
        }
      }
      if (dp[i][j] && (j - i + 1 > maxlen)) {
        maxlen = j - i + 1;
        start = i;
      }
    }
  }
  s[start + maxlen] = 0;

  return s + start;
}

char* longestPalindrome(char* s) {
  int len = strlen(s);
  // dp[i][j]表示s[i]到s[j]是否为回文子串
  int dp[len][len];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < len; ++i) {
    dp[i][i] = 1;
  }

  int max = 1;
  int start = 0;
  for (int i = len - 2; i >= 0; --i) {
    for (int j = i + 1; j < len; ++j) {
      if (s[i] == s[j]) {
        dp[i][j] = j - i > 1 ? dp[i + 1][j - 1] : 1;
        if (dp[i][j] && j - i + 1 > max) {
          max = j - i + 1;
          start = i;
        }
      }
    }
  }

  // for(int i = 0; i < len; ++i) {
  //   for(int j = 0; j < len; ++j) {
  //       printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // "babad"
  // 1 0 1 0 0
  // 0 1 0 1 0
  // 0 0 1 0 0
  // 0 0 0 1 0
  // 0 0 0 0 1

  s[start + max] = 0;

  return s + start;
}

// 动态规划，与647类似，写法相同
char* longestPalindrome(char* s) {
  int len = strlen(s);
  bool dp[len][len];
  memset(dp, 0, sizeof(dp));

  int max = 1;
  int start = 0;
  for (int i = len - 1; i >= 0; --i) {
    for (int j = i; j < len; ++j) {
      if (s[i] == s[j]) {
        if (j - i <= 1) {
          dp[i][j] = true;
        } else if (dp[i + 1][j - 1]) {
          dp[i][j] = true;
        }
        if (dp[i][j] && j - i + 1 > max) {
          max = j - i + 1;
          start = i;
        }
      }
    }
  }

  s[start + max] = 0;

  return s + start;
}

// @lc code=end
