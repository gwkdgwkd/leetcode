/*
给一个字符串s，请找出满足每个字符最多出现两次的最长子字符串，并返回该的最大长度。

示例1：
输入：s = "bcbbbcba"
输出：4
解释：以下子字符串长度为4，并且每个字符最多出现两次："bcbbbcba"。

示例2：
输入：s = "aaaa"
输出：2
解释：以下子字符串长度为2，并且每个字符最多出现两次："aaaa"。


提示：
2 <= s.length <= 100
s仅由小写英文字母组成。
*/

class Solution {
 public:
  int maximumLengthSubstring(string s) {
    int n = s.size();
    int left = 0;
    int right = 0;

    unordered_map<int, int> cnt;
    int ans = 0;
    while (right < n) {
      cnt[s[right]]++;
      while (cnt[s[right]] > 2) {
        cnt[s[left++]]--;
      }
      ans = max(ans, right - left + 1);
      ++right;
    }
    return ans;
  }
};

class Solution {
 public:
  int maximumLengthSubstring(string s) {
    int n = s.size();
    int left = 0;
    int right = 0;

    int hash[128];
    int ans = 0;
    while (right < n) {
      char c = s[right++];
      hash[c]++;
      while (hash[c] > 2) {
        hash[s[left++]]--;
      }
      ans = max(ans, right - left);
    }
    return ans;
  }
};