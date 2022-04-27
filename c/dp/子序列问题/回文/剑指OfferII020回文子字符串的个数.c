/*
给定一个字符串s，请计算这个字符串中有多少个回文子字符串。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

示例1：
输入：s = "abc"
输出：3
解释：三个回文子串:"a", "b", "c"

示例2：
输入：s = "aaa"
输出：6
解释：6个回文子串:"a", "a", "a", "aa", "aa", "aaa"

提示：
1 <= s.length <= 1000
s由小写英文字母组成

注意：本题与647 题相同
*/

int countSubstrings(char* s) {
  int len = strlen(s);
  bool dp[len][len];
  memset(dp, 0, sizeof(dp));
  int ret = 0;
  for (int i = 0; i < len; ++i) {
    dp[i][i] = true;
    ++ret;
  }

  for (int i = len - 2; i >= 0; --i) {
    for (int j = i + 1; j < len; ++j) {
      if (s[i] == s[j] && (i + 1 == j || dp[i + 1][j - 1])) {
        dp[i][j] = true;
        ++ret;
      }
    }
  }

  return ret;
}