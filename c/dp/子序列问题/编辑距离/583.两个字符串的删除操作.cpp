/*
给定两个单词word1和word2，返回使得word1和word2相同所需的最小步数。
每步可以删除任意一个字符串中的一个字符。

示例1：
输入: word1 = "sea", word2 = "eat"
输出: 2
解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"

示例2:
输入：word1 = "leetcode", word2 = "etco"
输出：4

提示：
1 <= word1.length, word2.length <= 500
word1和word2只包含小写英文字母
*/

int minDistance(char* word1, char* word2) {
  int len1 = strlen(word1);
  int len2 = strlen(word2);
  if (len1 * len2 == 0) {
    return 0;
  }

  int dp[len1 + 1][len2 + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return len1 - dp[len1][len2] + len2 - dp[len1][len2];
}

// 参考最长公共子串
int minDistance(char* word1, char* word2) {
  int m = strlen(word1);
  int n = strlen(word2);
  int dp[m + 1][n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  // 删除最后的结果就是两个字符串的最长公共子串(1143)，删除的次数为：
  return m - dp[m][n] + n - dp[m][n];
}

// 直接动态规划
int minDistance(char* word1, char* word2) {
  int m = strlen(word1);
  int n = strlen(word2);

  int dp[m + 1][n + 1];
  for (int i = 0; i <= m; ++i) {
    // dp[i][0]：word2为空字符串，以i-1为结尾的字符串word1要删除多少个元素，
    // 才能和word2相同呢，很明显dp[i][0]=i
    dp[i][0] = i;
  }
  for (int j = 0; j <= n; ++j) {
    dp[0][j] = j;  // 同上
  }

  // 可以看出dp[i][j]都是根据左上⽅、正上⽅、正左⽅推出来的。
  // 所以遍历的时候⼀定是从上到下，从左到右，这样保证dp[i][j]可以根据之前计算出来的数值进⾏计算。
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        // 当word1[i-1]与word2[j-1]相同的时候，dp[i][j] = dp[i-1][j-1];
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        // 当word1[i-1]与word2[j-1]不相同的时候，有三种情况：
        // 情况⼀：删word1[i-1]，最少操作次数为dp[i-1][j]+1
        // 情况⼆：删word2[j-1]，最少操作次数为dp[i][j-1]+1
        // 情况三：同时删word1[i-1]和word2[j-1]，操作的最少次数为dp[i-1][j-1]+2
        // dp[i][j] = fmin(dp[i-1][j-1] + 2, fmin(dp[i-1][j], dp[i][j-1]) + 1);
        // 情况三，应该是等于dp[i - 1][j]-1或者dp[i][j - 1]-1，所以可以省略
        dp[i][j] = fmin(dp[i - 1][j], dp[i][j - 1]) + 1;
      }
    }
  }

  return dp[m][n];
}

class Solution {
 public:
  int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
      }
    }

    return m - dp[m][n] + n - dp[m][n];
  }
};
