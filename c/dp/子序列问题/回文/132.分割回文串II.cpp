/*
给你一个字符串s，请你将s分割成一些子串，使每个子串都是回文。
返回符合要求的最少分割次数。

示例1：
输入：s = "aab"
输出：1
解释：只需一次分割就可将s分割成["aa","b"]这样两个回文子串。

示例2：
输入：s = "a"
输出：0

示例3：
输入：s = "ab"
输出：1

提示：
1 <= s.length <= 2000
s 仅由小写英文字母组成
*/

// 剑指OfferII094最少回文分割

int minCut(char* s) {
  int len = strlen(s);
  // dp1[i][j]表示从i到j是否为回文
  bool dp1[len][len];
  memset(dp1, 0, sizeof(dp1));
  for (int i = 0; i < len; ++i) {
    dp1[i][i] = true;
  }
  for (int i = len - 2; i >= 0; --i) {
    for (int j = i + 1; j < len; ++j) {
      if (s[i] == s[j] && (j == i + 1 || dp1[i + 1][j - 1])) {
        dp1[i][j] = true;
      }
    }
  }

  // dp2[i]表示从字符串开头到第i个字符的最少回文分割次数
  int dp2[len];
  for (int i = 0; i < len; ++i) {
    if (dp1[0][i]) {  // 是回文，不用分割
      dp2[i] = 0;
    } else {
      dp2[i] = i;
      for (int j = 1; j <= i; ++j) {
        if (dp1[j][i]) {  // j到i是回文
          // [0...j-1 j...i]：分割次数等于0到j-1的分割次数再加1
          dp2[i] = fmin(dp2[i], dp2[j - 1] + 1);
        }
      }
    }
  }

  return dp2[len - 1];
}

class Solution {
 public:
  int minCut(string s) {
    int n = s.size();

    vector<vector<int>> dp1(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; --i) {
      for (int j = i; j < n; ++j) {
        if (s[i] == s[j] && (j - i <= 1 || dp1[i + 1][j - 1])) {
          dp1[i][j] = 1;
        }
      }
    }

    vector<int> dp2(n, 0);
    for (int i = 0; i < n; ++i) {
      if (dp1[0][i]) {
        dp2[i] = 0;
      } else {
        dp2[i] = i;
        for (int j = 1; j <= i; ++j) {
          if (dp1[j][i]) {
            dp2[i] = std::min(dp2[i], dp2[j - 1] + 1);
          }
        }
      }
    }

    return dp2[n - 1];
  }
};