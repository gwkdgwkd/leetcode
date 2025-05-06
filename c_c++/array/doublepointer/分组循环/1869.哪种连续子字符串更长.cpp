/*
给一个二进制字符串s。
如果字符串中由1组成的最长连续子字符串严格长于由0组成的最长连续子字符串，返回rue；
否则，返回false。
例如，s = "110100010"中，由1组成的最长连续子字符串的长度是2，
由0组成的最长连续子字符串的长度是3。
注意，如果字符串中不存在0，此时认为由0组成的最长连续子字符串的长度是0。
字符串中不存在1的情况也适用此规则。

示例1：
输入：s = "1101"
输出：true
解释：由1组成的最长连续子字符串的长度是2："1101"
     由0组成的最长连续子字符串的长度是1："1101"
     由1组成的子字符串更长，故返回true。

示例2：
输入：s = "111000"
输出：false
解释：由1组成的最长连续子字符串的长度是3："111000"
     由0组成的最长连续子字符串的长度是3："111000"
     由1组成的子字符串不比由0组成的子字符串长，故返回false。

示例3：
输入：s = "110100010"
输出：false
解释：由1组成的最长连续子字符串的长度是2："110100010"
     由0组成的最长连续子字符串的长度是3："110100010"
     由1组成的子字符串不比由0组成的子字符串长，故返回false。


提示：
1 <= s.length <= 100
s[i]不是'0'就是'1'
*/

class Solution {
 public:
  bool checkZeroOnes(string s) {
    int n = s.size();
    int left = 0;
    int right = 0;
    int l[2]{};
    while (right < n) {
      if (s[right] != s[left]) {
        int i = s[left] - '0';
        l[i] = max(l[i], right - left);
        left = right;
      }
      if (right == n - 1) {
        int i = s[left] - '0';
        l[i] = max(l[i], right - left + 1);
      }
      ++right;
    }
    return l[1] > l[0];
  }
};

// 分组循环
class Solution {
 public:
  bool checkZeroOnes(string s) {
    int max0 = -1, max1 = -1;
    int cnt0 = 1, cnt1 = 1;
    int n = s.length();
    for (int i = 0; i < n;) {
      if (s[i] == '0') {
        for (i++; i < n && s[i] == s[i - 1]; i++, cnt0++)
          ;
        max0 = max(max0, cnt0);
        cnt0 = 1;
      } else {
        for (i++; i < n && s[i] == s[i - 1]; i++, cnt1++)
          ;
        max1 = max(max1, cnt1);
        cnt1 = 1;
      }
    }
    return max1 > max0;
  }
};
