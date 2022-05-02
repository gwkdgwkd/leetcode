/*
给定三个字符串s1、s2、s3，请你帮忙验证s3是否是由s1和s2交错组成的。
两个字符串s和t交错的定义与过程如下，其中每个字符串都会被分割成若干非空子字符串：
s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
交错是s1 + t1 + s2 + t2 + s3 + t3 + ...
或者t1 + s1 + t2 + s2 + t3 + s3 + ...
注意：a+b意味着字符串a和b连接。

示例1：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出：true

示例2：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出：false

示例3：
输入：s1 = "", s2 = "", s3 = ""
输出：true

提示：
0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1、s2和s3都由小写英文字母组成

进阶：您能否仅使用O(s2.length)额外的内存空间来解决它?
*/

// 剑指OfferII096字符串交织

// 动态规划
bool isInterleave(char* s1, char* s2, char* s3) {
  int n = strlen(s1), m = strlen(s2), t = strlen(s3);

  // 表示s1的前i个字符和s2的前j个字符是否能构成s3的前i+j个字符
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
