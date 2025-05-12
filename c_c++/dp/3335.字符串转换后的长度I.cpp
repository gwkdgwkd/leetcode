/*
给一个字符串s和一个整数t，表示要执行的转换次数。
每次转换需要根据以下规则替换字符串s中的每个字符：
如果字符是'z'，则将其替换为字符串"ab"。
否则，将其替换为字母表中的下一个字符。例如，'a'替换为'b'，'b'替换为'c'，依此类推。
返回恰好执行t次转换后得到的字符串的长度。
由于答案可能非常大，返回其对10^9 + 7取余的结果。

示例1：
输入：s = "abcyy", t = 2
输出：7
解释：第一次转换(t = 1)
        'a'变为'b'
        'b'变为'c'
        'c'变为'd'
        'y'变为'z'
        'y'变为'z'
    第一次转换后的字符串为："bcdzz"
    第二次转换(t = 2)
        'b'变为'c'
        'c'变为'd'
        'd'变为'e'
        'z'变为"ab"
        'z'变为"ab"
    第二次转换后的字符串为："cdeabab"
    最终字符串长度：字符串为"cdeabab"，长度为7个字符。

示例2：
输入：s = "azbk", t = 1
输出：5
解释：第一次转换 (t = 1)
        'a'变为'b'
        'z'变为"ab"
        'b'变为'c'
        'k'变为'l'
     第一次转换后的字符串为："babcl"
     最终字符串长度：字符串为"babcl"，长度为5个字符。


提示：
1 <= s.length <= 10^5
s 仅由小写英文字母组成。
1 <= t <= 10^5
*/

// 递推
class Solution {
 private:
  static constexpr int mod = 1000000007;

 public:
  int lengthAfterTransformations(string s, int t) {
    int cnt[26]{};
    for (char c : s) {
      cnt[c - 'a']++;
    }

    for (int i = 0; i < t; ++i) {
      int nxt[26]{};
      nxt[0] = cnt[25];
      nxt[1] = (cnt[25] + cnt[0]) % mod;
      for (int j = 2; j < 26; ++j) {
        nxt[j] = cnt[j - 1];
      }
      memcpy(cnt, nxt, sizeof(cnt));
    }
    int ans = 0;
    for (int i = 0; i < 26; ++i) {
      ans = (ans + cnt[i]) % mod;
    }
    return ans;
  }
};

// 矩阵快速幂优化DP