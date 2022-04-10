/*
给定两个字符串text1和text2，返回这两个字符串的最长 公共子序列的长度。
如果不存在公共子序列，返回0。
一个字符串的子序列是指这样一个新的字符串：
它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace"是"abcde"的子序列，但"aec"不是"abcde"的子序列。
两个字符串的公共子序列是这两个字符串所共同拥有的子序列。

示例1：
输入：text1 = "abcde", text2 = "ace"
输出：3
解释：最长公共子序列是"ace"，它的长度为3。

示例2：
输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是"abc"，它的长度为3。

示例3：
输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回0。

提示：
1 <= text1.length, text2.length <= 1000
text1和text2仅由小写英文字符组成。
*/

int longestCommonSubsequence(char* text1, char* text2) {
  int len1 = strlen(text1);
  int len2 = strlen(text2);

  // dp[i][j]：⻓度为[0,i-1]的字符串text1与⻓度为[0,j-1]的字符串text2的最⻓公共⼦序列为dp[i][j]
  int dp[len1 + 1][len2 + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (text1[i - 1] == text2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  // for (int i = 0; i <= len1; ++i) {
  //   for (int j = 0; j <= len2; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // "abcde","ace"
  //   0   0   0   0
  //   0   1   1   1
  //   0   1   1   1
  //   0   1   2   2
  //   0   1   2   2
  //   0   1   2   3

  return dp[len1][len2];
}
