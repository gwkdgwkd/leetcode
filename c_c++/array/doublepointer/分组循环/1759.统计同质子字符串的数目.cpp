/*
给一个字符串s，返回s中同质子字符串的数目。
由于答案可能很大，只需返回对10^9+7取余后的结果。
同质字符串的定义为：如果一个字符串中的所有字符都相同，那么该字符串就是同质字符串。
子字符串是字符串中的一个连续字符序列。

示例1：
输入：s = "abbcccaa"
输出：13
解释：同质子字符串如下所列：
     "a"   出现3次。
     "aa"  出现1次。
     "b"   出现2次。
     "bb"  出现1次。
     "c"   出现3次。
     "cc"  出现2次。
     "ccc" 出现1次。
     3 + 1 + 2 + 1 + 3 + 2 + 1 = 13

示例2：
输入：s = "xy"
输出：2
解释：同质子字符串是"x"和"y"。

示例3：
输入：s = "zzzzz"
输出：15


提示：
1 <= s.length <= 10^5
s由小写字符串组成。
*/

class Solution {
 public:
  int countHomogenous(string s) {
    int n = s.size();
    int left = 0;
    int right = 0;
    long long ans = 0;
    long long mod = 1e9 + 7;
    int cnt = 0;
    while (right < n) {
      if (s[left] != s[right]) {
        ans += (long long)cnt * (cnt + 1) / 2;
        cnt = 1;
        left = right;
      } else {
        ++cnt;
      }
      ++right;
    }
    ans += (long long)cnt * (cnt + 1) / 2;
    return ans % mod;
  }
};

class Solution {
 public:
  int countHomogenous(string s) {
    int n = s.size();
    int left = 0;
    int right = 0;
    long long ans = 0;
    long long mod = 1e9 + 7;
    while (right < n) {
      if (s[left] != s[right]) {
        int c = right - left;
        ans += (long long)c * (c + 1) / 2;
        left = right;
      }
      ++right;
    }
    int c = right - left;
    ans += (long long)c * (c + 1) / 2;

    return ans % mod;
  }
};
