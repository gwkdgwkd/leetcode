/*
字母序连续字符串是由字母表中连续字母组成的字符串。
换句话说，字符串"abcdefghijklmnopqrstuvwxyz"的任意子字符串都是字母序连续字符串。
例如，"abc"是一个字母序连续字符串，而"acb"和"za"不是。
给一个仅由小写英文字母组成的字符串s，返回其最长的字母序连续子字符串的长度。

示例1：
输入：s = "abacaba"
输出：2
解释：共有4个不同的字母序连续子字符串"a"、"b"、"c"和"ab"。
     "ab"是最长的字母序连续子字符串。

示例2：
输入：s = "abcde"
输出：5
解释："abcde"是最长的字母序连续子字符串。


提示：
1 <= s.length <= 10^5
s由小写英文字母组成
*/

class Solution {
 public:
  int longestContinuousSubstring(string s) {
    int n = s.size();
    int left = 0;
    int right = 0;
    int ans = 0;
    while (right < n) {
      if (right > 0 && s[right] - s[right - 1] != 1) {
        ans = max(ans, right - left);
        left = right;
      }
      ++right;
    }
    ans = max(ans, right - left);

    return ans;
  }
};

class Solution {
 public:
  int longestContinuousSubstring(string s) {
    int ans = 1, cnt = 1;
    for (int i = 1; i < s.length(); i++) {
      if (s[i - 1] + 1 == s[i]) {
        ans = max(ans, ++cnt);
      } else {
        cnt = 1;
      }
    }

    return ans;
  }
};