/*
给定一个字符串(s)和一个字符模式(p)，实现一个支持'?'和'*'的通配符匹配：
'?'可以匹配任何单个字符；
'*'可以匹配任意字符串（包括空字符串）。
两个字符串完全匹配才算匹配成功。
说明：
s可能为空，且只包含从a-z的小写字母。
p可能为空，且只包含从a-z的小写字母，以及字符?和*。

示例1：
输入：
s = "aa"
p = "a"
输出：false
解释："a"无法匹配"aa"整个字符串。

示例2：
输入：
s = "aa"
p = "*"
输出：true
解释：'*'可以匹配任意字符串。

示例3：
输入：
s = "cb"
p = "?a"
输出：false
解释：'?'可以匹配'c',但第二个'a'无法匹配'b'。

示例4：
输入：
s = "adceb"
p = "*a*b"
输出：true
解释：第一个'*'可以匹配空字符串, 第二个'*'可以匹配字符串"dce".

示例5：
输入：
s = "acdcb"
p = "a*c?b"
输出：false
*/

// 动态规划
bool isMatch(char* s, char* p) {
  int m = strlen(s);
  int n = strlen(p);
  // dp[i][j]表示字符串s的前i个字符和模式p的前j个字符是否能匹配
  int dp[m + 1][n + 1];

  // dp[0][0]=true，即当字符串s和模式p均为空时，匹配成功；
  // dp[i][0]=false，即空模式无法匹配非空字符串；
  // dp[0][j]需要分情况讨论：因为星号才能匹配空字符串，
  // 所以只有当模式p的前j个字符均为星号时，dp[0][j]才为真。
  memset(dp, 0, sizeof(dp));
  dp[0][0] = true;
  for (int j = 1; j <= n; ++j) {
    if (p[j - 1] == '*') {
      dp[0][j] = true;
    } else {
      break;
    }
  }

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (p[j - 1] == '*') {
        // 对s没有要求，dp[i][j-1]不使用星号，dp[i-1][j]使用星号
        dp[i][j] = dp[i][j - 1] || dp[i - 1][j];  // |也行
      } else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      }
    }
  }
  return dp[m][n];
}

class Solution {
 public:
  bool isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();

    // 慢、空间大：
    // deque<deque<bool>> dp(m + 1, deque<bool>(n + 1, false));
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, false));
    dp[0][0] = true;
    for (int j = 1; j <= n; ++j) {
      if (p[j - 1] == '*') {
        dp[0][j] = true;
      } else {
        break;
      }
    }

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
          dp[i][j] = dp[i - 1][j - 1];
        } else if (p[j - 1] == '*') {
          dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
        }
      }
    }

    return dp[m][n];
  }
};