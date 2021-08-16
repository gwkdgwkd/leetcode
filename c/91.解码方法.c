/*
 * @lc app=leetcode.cn id=91 lang=c
 *
 * [91] 解码方法
 */

// @lc code=start

/*
// 动态规划
int numDecodings(char* s) {
  int n = strlen(s);

  if (s[0] == '0' || n < 1) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }

  int dp[n];
  dp[0] = s[0] == '0' ? 0 : 1;
  if ((s[0] - '0') * 10 + s[1] - '0' <= 26) {
    dp[1] = s[1] == '0' ? 1 : 2;
  } else if ((s[0] - '0') * 10 + s[1] - '0' > 26 && s[1] == '0') {
    return 0;
  } else {
    dp[1] = 1;
  }

  for (int i = 2; i < n; ++i) {
    if (s[i] == '0') {
      if (((s[i - 1] - '0') * 10 + s[i] - '0' == 0) ||
          ((s[i - 1] - '0') * 10 + s[i] - '0' > 26)) {
        return 0;
      }
      dp[i] = dp[i - 2];
      continue;
    }
    if (s[i - 1] == '0') {
      dp[i] = dp[i - 1];
      continue;
    }
    if ((s[i - 1] - '0') * 10 + s[i] - '0' <= 26) {
      dp[i] = dp[i - 2] + dp[i - 1];

    } else {
      dp[i] = dp[i - 1];
    }
  }

  return dp[n - 1];
}
*/

// 官方题解
int numDecodings(char* s) {
  int n = strlen(s);
  // a = f[i-2], b = f[i-1], c = f[i]
  int a = 0, b = 1, c;
  for (int i = 1; i <= n; ++i) {
    c = 0;
    if (s[i - 1] != '0') {
      c += b;
    }
    if (i > 1 && s[i - 2] != '0' &&
        ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
      c += a;
    }
    a = b, b = c;
  }
  return c;
}

// @lc code=end
