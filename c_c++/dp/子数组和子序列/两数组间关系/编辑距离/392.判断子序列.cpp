/*
给定字符串s和t，判断s是否为t的子序列。
字符串的一个子序列是原始字符串删除一些，也可以不删除，
字符而不改变剩余字符相对位置形成的新字符串。
例如，"ace"是"abcde"的一个子序列，而"aec"不是。
进阶：
如果有大量输入的S，称作S1, S2, ... , Sk其中k >= 10亿，
需要依次检查它们是否为T的子序列，在这种情况下，你会怎样改变代码？

示例1：
输入：s = "abc", t = "ahbgdc"
输出：true

示例2：
输入：s = "axc", t = "ahbgdc"
输出：false

提示：
0 <= s.length <= 100
0 <= t.length <= 10^4
两个字符串都只由小写字符组成。
*/

// 编辑距离的⼊⻔题⽬，因为从题意中可以发现，只需要计算删除的情况，不⽤考虑增加和替换的情况。

// 动态规划
// 时间复杂度：O(n*m)
// 空间复杂度：O(n*m)
bool isSubsequence(char* s, char* t) {
  int l1 = strlen(s);
  int l2 = strlen(t);
  // dp[i][j]表示以下标i-1为结尾的字符串s，和以下标j-1为结尾的字符串t，相同⼦序列的⻓度。
  int dp[l1 + 1][l2 + 1];
  // dp[i][j]都是依赖于dp[i-1][j-1]和dp[i][j-1]，所以dp[0][0]和dp[i][0]是⼀定要初始化的。
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= l1; ++i) {
    for (int j = 1; j <= l2; ++j) {
      if (s[i - 1] == t[j - 1]) {
        // 找到了⼀个相同的字符，相同⼦序列⻓度⾃然要在dp[i-1][j-1]的基础上加1
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        // 此时相当于t要删除元素，t如果把当前元素t[j-1]删除，
        // 那么dp[i][j]的数值就是看s[i-1]与t[j-2]的⽐较结果了，即：
        dp[i][j] = dp[i][j - 1];
        // dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);  // 也可以
      }
    }
  }

  return dp[l1][l2] == l1;
}

// 双指针
// 时间复杂度：O(m+n)
// 空间复杂度：O(1)
bool isSubsequence(char* s, char* t) {
  int m = strlen(s);
  int n = strlen(t);

  int i = 0, j = 0;
  while (i < m && j < n) {
    if (s[i] == t[j]) {
      ++i;
    }
    ++j;
  }

  return i == m;
}

class Solution {
 public:
  bool isSubsequence(string s, string t) {
    int ls = s.size();
    int lt = t.size();
    int i = 0;
    int j = 0;

    while (i < ls && j < lt) {
      if (s[i] == t[j]) {
        ++i;
      }
      ++j;
    }

    return i == ls;
  }
};

class Solution {
 public:
  bool isSubsequence(string s, string t) {
    int m = s.size();
    int n = t.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (s[i - 1] == t[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
      }
    }

    return dp[m][n] == m;
  }
};
