/*
给一个字符串s和一个整数k。
判断是否存在一个长度恰好为k的子字符串，该子字符串需要满足以下条件：
该子字符串只包含一个唯一字符（例如，"aaa"或"bbb"）。
如果该子字符串的前面有字符，则该字符必须与子字符串中的字符不同。
如果该子字符串的后面有字符，则该字符也必须与子字符串中的字符不同。
如果存在这样的子串，返回true；否则，返回false。
子字符串是字符串中的连续、非空字符序列。

示例1：
输入：s = "aaabaaa", k = 3
输出：true
解释：子字符串s[4..6] == "aaa"满足条件：
     长度为3。
     所有字符相同。
     子串"aaa"前的字符是'b'，与'a'不同。
     子串"aaa"后没有字符。

示例2：
输入：s = "abc", k = 2
输出：false
解释：不存在长度为2 、仅由一个唯一字符组成且满足所有条件的子字符串。


提示：
1 <= k <= s.length <= 100
s仅由小写英文字母组成。
*/

class Solution {
 public:
  bool hasSpecialSubstring(string s, int k) {
    int n = s.size();
    int left = 0;
    int right = 0;
    while (right < n) {
      if (s[right] != s[left]) {
        if (right - left == k) {
          return true;
        }
        left = right;
      }
      ++right;
    }
    if (s[right - 1] == s[left] && right - left == k) {
      return true;
    }
    return false;
  }
};

class Solution {
 public:
  bool hasSpecialSubstring(string s, int k) {
    int n = s.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      cnt++;
      if (i == n - 1 || s[i] != s[i + 1]) {
        if (cnt == k) {
          return true;
        }
        cnt = 0;
      }
    }
    return false;
  }
};