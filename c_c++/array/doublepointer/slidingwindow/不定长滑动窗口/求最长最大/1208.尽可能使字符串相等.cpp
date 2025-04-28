/*
给两个长度相同的字符串，s和t。
将s中的第i个字符变到t中的第i个字符需要|s[i] - t[i]|的开销（开销可能为0），
也就是两个字符的ASCII码值的差的绝对值。
用于变更字符串的最大预算是maxCost。
在转化字符串时，总开销应当小于等于该预算，这也意味着字符串的转化可能是不完全的。
如果可以将s的子字符串转化为它在t中对应的子字符串，则返回可以转化的最大长度。
如果s中没有子字符串可以转化成t中对应的子字符串，则返回0。

示例1：
输入：s = "abcd", t = "bcdf", maxCost = 3
输出：3
解释：s中的"abc"可以变为"bcd"。开销为3，所以最大长度为3。

示例2：
输入：s = "abcd", t = "cdef", maxCost = 3
输出：1
解释：s中的任一字符要想变成t中对应的字符，其开销都是2。因此，最大长度为1。

示例3：
输入：s = "abcd", t = "acde", maxCost = 0
输出：1
解释：a -> a, cost = 0，字符串未发生变化，所以最大长度为1。


提示：
1 <= s.length, t.length <= 10^5
0 <= maxCost <= 10^6
s和t都只含小写英文字母。
*/

class Solution {
 public:
  int equalSubstring(string s, string t, int maxCost) {
    int n = s.size();
    int right = 0;
    int left = 0;
    int sum = 0;
    int ans = 0;
    while (right < n) {
      sum += abs(s[right] - t[right]);
      while (sum > maxCost) {
        sum -= abs(s[left] - t[left]);
        ++left;
      }
      ans = max(ans, right - left + 1);
      ++right;
    }
    return ans;
  }
};