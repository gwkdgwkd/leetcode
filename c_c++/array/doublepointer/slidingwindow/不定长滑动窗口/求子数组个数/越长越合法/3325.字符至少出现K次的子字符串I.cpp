/*
给一个字符串s和一个整数k，在s的所有子字符串中，
请统计并返回至少有一个字符至少出现k次的子字符串总数。
子字符串是字符串中的一个连续、非空的字符序列。

示例1：
输入：s = "abacb", k = 2
输出：4
解释：符合条件的子字符串如下：
     "aba"（字符'a'出现2次）。
     "abac"（字符'a'出现2次）。
     "abacb"（字符'a'出现2次）。
     "bacb"（字符'b'出现2次）。

示例2：
输入：s = "abcde", k = 1
输出：15
解释：所有子字符串都有效，因为每个字符至少出现一次。


提示：
1 <= s.length <= 3000
1 <= k <= s.length
s仅由小写英文字母组成。
*/

class Solution {
 public:
  int numberOfSubstrings(string s, int k) {
    int n = s.size();
    int cnt[26]{};
    int right = 0;
    int left = 0;
    int ans = 0;
    while (right < n) {
      char r = s[right++];
      cnt[r - 'a']++;
      while (cnt[r - 'a'] == k) {
        cnt[s[left++] - 'a']--;
      }
      ans += left;
    }
    return ans;
  }
};