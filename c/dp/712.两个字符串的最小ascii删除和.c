/*
给定两个字符串s1和s2，返回使两个字符串相等所需删除字符的ASCII值的最小和。

示例1:
输入: s1 = "sea", s2 = "eat"
输出: 231
解释: 在"sea"中删除"s"并将"s"的值(115)加入总和。
在"eat"中删除"t"并将116加入总和。
结束时，两个字符串相等，115 + 116 = 231就是符合条件的最小和。

示例2:
输入: s1 = "delete", s2 = "leet"
输出: 403
解释: 在"delete"中删除"dee"字符串变成"let"，
将100[d]+101[e]+101[e]加入总和。
在"leet"中删除"e"将101[e]加入总和。
结束时，两个字符串都等于"let"，结果即为100+101+101+101 = 403 。
如果改为将两个字符串转换为"lee"或"eet"，我们会得到433或417 的结果，比答案更大。

提示:
0 <= s1.length, s2.length <= 1000
s1和s2由小写英文字母组成
*/

int minimumDeleteSum(char *s1, char *s2) {
  int m = strlen(s1);
  int n = strlen(s2);
  int ret = 0;
  if (m == 0) {
    for (int j = 0; j < n; ++j) {
      ret += s2[j];
    }
    return ret;
  }
  if (n == 0) {
    for (int i = 0; i < m; ++i) {
      ret += s1[i];
    }
    return ret;
  }

  int dp[m + 1][n + 1];
  dp[0][0] = 0;
  for (int i = 1; i <= m; ++i) {
    dp[i][0] = dp[i - 1][0] + s1[i - 1];
  }

  for (int j = 1; j <= n; ++j) {
    dp[0][j] = dp[0][j - 1] + s2[j - 1];
  }

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = fmin(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
      }
    }
  }

  // for (int i = 0; i <= m; ++i) {
  //   for (int j = 0; j <= n; ++j) {
  //     printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }

  return dp[m][n];
}
