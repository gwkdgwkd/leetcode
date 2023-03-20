/*
给你一个字符串s，找到s中最长的回文子串。

示例1：
输入：s = "babad"
输出："bab"
解释："aba"同样是符合题意的答案。

示例2：
输入：s = "cbbd"
输出："bb"

提示：
1 <= s.length <= 1000
s仅由数字和英文字母组成
*/

char* longestPalindrome(char* s) {
  int len = strlen(s);
  bool dp[len][len];  // dp[i][j]表示s[i]到s[j]是否为回文子串
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < len; ++i) {
    dp[i][i] = true;  // 只有一个元素，那么是回文
  }

  int maxlen = 1;
  int start = 0;
  for (int i = len - 2; i >= 0; --i) {   // 从底向上遍历
    for (int j = i + 1; j < len; ++j) {  // 从左向右遍历
      // [i...j]范围内第一个和最后一个元素相等，才可能是回文
      if (s[i] == s[j]) {
        // [i...j]是回文的条件：
        // 1.只有i和j两个元素，并且i和j相等，那么是回文
        // 2.[i+1...j-1]是回文，并且i和j相等，那么[i...j]是回文
        if (j == i + 1 || dp[i + 1][j - 1] == true) {
          dp[i][j] = true;
          // 有新的最长回文，更新开始位置和长度：
          if (j - i + 1 > maxlen) {
            maxlen = j - i + 1;
            start = i;
          }
        }
      }
    }
  }
  s[start + maxlen] = 0;

  return s + start;
}

// 动态规划，与647类似，写法相同
char* longestPalindrome(char* s) {
  int len = strlen(s);
  bool dp[len][len];
  memset(dp, 0, sizeof(dp));

  int max = 1;
  int start = 0;
  for (int i = len - 1; i >= 0; --i) {
    for (int j = i; j < len; ++j) {
      if (s[i] == s[j]) {
        if (j - i <= 1) {
          dp[i][j] = true;
        } else if (dp[i + 1][j - 1]) {
          dp[i][j] = true;
        }
        if (dp[i][j] && j - i + 1 > max) {
          max = j - i + 1;
          start = i;
        }
      }
    }
  }

  s[start + max] = 0;

  return s + start;
}

// 中心扩展算法
char* longestPalindrome(char* s) {
  int pLeft = 0;
  int pRight = 0;
  int n = strlen(s);
  int len = -1;
  for (int i = 0; i < 2 * n - 1; i++) {
    int left = i / 2;
    int right = i / 2 + i % 2;
    while (left >= 0 && right < n && s[left] == s[right]) {
      if ((right - left + 1) > len) {
        len = right - left + 1;
        pLeft = left;
        pRight = right;
      }
      left--;
      right++;
    }
  }
  char* ans = (char*)calloc(len + 1, sizeof(char));
  int z = 0;
  for (int j = pLeft; j < pRight + 1; j++) {
    ans[z++] = s[j];
  }
  return ans;
}

// Manacher算法

class Solution {
 public:
  string longestPalindrome(string s) {
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    int start = 0;
    int len = 1;
    for (int i = n - 1; i >= 0; --i) {  // i=n-2也行，但不对吧？
      dp[i][i] = true;
      for (int j = i + 1; j < n; ++j) {
        if (s[i] == s[j]) {
          if (j == i + 1 || dp[i + 1][j - 1]) {
            dp[i][j] = true;
            if (j - i + 1 > len) {
              start = i;
              len = j - i + 1;
            }
          }
        }
      }
    }

    return string(s.begin() + start, s.begin() + start + len);
  }
};

class Solution {
 public:
  string longestPalindrome(string s) {
    int n = s.size();

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
      dp[i][i] = true;
    }

    int start = 0;
    int len = 1;
    for (int i = n - 2; i >= 0; --i) {
      for (int j = i + 1; j < n; ++j) {
        if (s[i] == s[j]) {
          if (j == i + 1 || dp[i + 1][j - 1]) {
            dp[i][j] = true;
            if (j - i + 1 > len) {
              len = j - i + 1;
              start = i;
            }
          }
        }
      }
    }

    return string(s.begin() + start, s.begin() + start + len);
  }
};
