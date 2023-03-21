/*
给定一个字符串s和一个字符串t，计算在s的子序列中t出现的个数。
子序列是指通过删除一些字符也可以不删除，且不干扰剩余字符相对位置所组成的新字符串。
例如，"ACE"是"ABCDE"的一个子序列，而"AEC"不是，保证答案符合32位带符号整数范围。

示例1：
输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示，有3种可以从s中得到"rabbit"的方案。
rabbbit
rabbbit
rabbbit

示例2：
输入：s = "babgbag", t = "bag"
输出：5
解释：
如下图所示，有5种可以从s中得到"bag"的方案。
babgbag
babgbag
babgbag
babgbag
babgbag

提示：
0 <= s.length, t.length <= 1000
s和t由英文字母组成
*/

// 剑指OfferII097子序列的数目

// 动态规划
int numDistinct(char* s, char* t) {
  int m = strlen(s);
  int n = strlen(t);

  // dp[i][j]：以i-1为结尾的s⼦序列中出现以j-1为结尾的t的个数为dp[i][j]。
  unsigned int dp[m + 1][n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 0; i <= m; i++) {
    // dp[i][0]表示：
    // 以i-1为结尾的s可以随便删除元素，出现空字符串的个数。
    // 那么dp[i][0]⼀定都是1，因为也就是把以i-1为结尾的s，
    // 删除所有元素，出现空字符串的个数就是1。
    // dp[0][0]应该是1，空字符串s，可以删除0个元素，变成空字符串t。
    dp[i][0] = 1;
  }
  // dp[0][j]：
  // 空字符串s可以随便删除元素，出现以j-1为结尾的字符串t的个数。
  // 那么dp[0][j]⼀定都是0，s如论如何也变成不了t。
  // for (int j = 1; j <= n; j++) {
  //   dp[0][j] = 0;
  // }

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s[i - 1] == t[j - 1]) {
        // 当s[i-1]与t[j-1]相等时，dp[i][j]可以有两部分组成：
        // 1.⼀部分是⽤s[i-1]来匹配，那么个数为dp[i-1][j-1]；
        // 2.⼀部分是不⽤s[i-1]来匹配，个数为dp[i-1][j]。
        // 为什么还要考虑不⽤s[i-1]来匹配，都相同了指定要匹配啊。
        // 例如：s[bagg]和t[bag]，s[3]和t[2]是相同的，
        // 但是字符串s也可以不⽤s[3]来匹配，即⽤s[0]s[1]s[2]组成的bag。
        // 当然也可以⽤s[3]来匹配，即：s[0]s[1]s[3]组成的bag。
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      } else {
        // 当s[i-1]与t[j-1]不相等时，dp[i][j]只有⼀部分组成，不⽤s[i-1]来匹配，即：
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[m][n];
}

class Solution {
 public:
  int numDistinct(string s, string t) {
    int m = s.size();
    int n = t.size();
    vector<vector<unsigned>> dp(m + 1, vector<unsigned>(n + 1, 0));
    for (int i = 0; i <= m; ++i) {
      dp[i][0] = 1;
    }

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (s[i - 1] == t[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }

    return dp[m][n];
  }
};
