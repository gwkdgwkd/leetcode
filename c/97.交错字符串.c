/*
 * @lc app=leetcode.cn id=97 lang=c
 *
 * [97] 交错字符串
 */

// @lc code=start

// 动态规划
bool isInterleave(char* s1, char* s2, char* s3) {
  int n = strlen(s1), m = strlen(s2), t = strlen(s3);

  int f[n + 1][m + 1];
  memset(f, 0, sizeof(f));

  if (n + m != t) {
    return false;
  }

  f[0][0] = true;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      int p = i + j - 1;
      if (i > 0) {
        f[i][j] |= (f[i - 1][j] && s1[i - 1] == s3[p]);
      }
      if (j > 0) {
        f[i][j] |= (f[i][j - 1] && s2[j - 1] == s3[p]);
      }
    }
  }

  // for(int i = 0; i <= n; ++i) {
  //   for(int j = 0; j <= m; ++j) {
  //       printf("%d ", f[i][j]);
  //   }
  //   printf("\n");
  // }
  // s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
  // 1 0 0 0 0 0
  // 1 0 0 0 0 0
  // 1 1 1 1 1 0
  // 0 1 1 0 1 0
  // 0 0 1 1 1 1
  // 0 0 0 1 0 1

  return f[n][m];
}
// @lc code=end
