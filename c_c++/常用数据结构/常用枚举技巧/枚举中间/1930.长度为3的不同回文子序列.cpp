/*
给一个字符串s，返回s中长度为3的不同回文子序列的个数。
即便存在多种方法来构建相同的子序列，但相同的子序列只计数一次。
回文是正着读和反着读一样的字符串。
子序列是由原字符串删除其中部分字符（也可以不删除）且不改变剩余字符之间相对顺序形成的一个新字符串。
例如，"ace"是"abcde"的一个子序列。

示例1：
输入：s = "aabca"
输出：3
解释：长度为3的3个回文子序列分别是：
     "aba"("aabca"的子序列)
     "aaa"("aabca"的子序列)
     "aca"("aabca"的子序列)

示例2：
输入：s = "adc"
输出：0
解释："adc"不存在长度为3的回文子序列。

示例3：
输入：s = "bbcbaba"
输出：4
解释：长度为3的4个回文子序列分别是：
     "bbb"("bbcbaba"的子序列)
     "bcb"("bbcbaba"的子序列)
     "bab"("bbcbaba"的子序列)
     "aba"("bbcbaba"的子序列)


提示：
3 <= s.length <= 10^5
s仅由小写英文字母组成
*/

// 枚举中间的字符
class Solution {
 public:
  int countPalindromicSubsequence(string s) {
    int n = s.size();
    int res = 0;
    // 前缀/后缀字符状态数组
    vector<int> pre(n), suf(n);
    for (int i = 0; i < n; ++i) {
      // 前缀s[0..i-1]包含的字符种类
      pre[i] = (i ? pre[i - 1] : 0) | (1 << (s[i] - 'a'));
    }
    for (int i = n - 1; i >= 0; --i) {
      // 后缀s[i+1..n-1]包含的字符种类
      suf[i] = (i != n - 1 ? suf[i + 1] : 0) | (1 << (s[i] - 'a'));
    }
    // 每种中间字符的回文子序列状态数组
    vector<int> ans(26);
    for (int i = 1; i < n - 1; ++i) {
      ans[s[i] - 'a'] |= (pre[i - 1] & suf[i + 1]);
    }
    // 更新答案
    for (int i = 0; i < 26; ++i) {
      res += __builtin_popcount(ans[i]);
    }
    return res;
  }
};

枚举两侧的字符
class Solution {
 public:
  int countPalindromicSubsequence(string s) {
    int n = s.size();
    int res = 0;
    // 枚举两侧字符
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      int l = 0, r = n - 1;
      // 寻找该字符第一次出现的下标
      while (l < n && s[l] != ch) {
        ++l;
      }
      // 寻找该字符最后一次出现的下标
      while (r >= 0 && s[r] != ch) {
        --r;
      }
      if (r - l < 2) {
        // 该字符未出现，或两下标中间的子串不存在
        continue;
      }
      // 利用哈希集合统计s[l+1..r-1]子串的字符总数，并更新答案
      unordered_set<char> charset;
      for (int k = l + 1; k < r; ++k) {
        charset.insert(s[k]);
      }
      res += charset.size();
    }
    return res;
  }
};

class Solution {
  int bitCout(int n) {
    int cnt = 0;
    while (n) {
      cnt += (n & 1);
      n = n >> 1;
    }
    return cnt;
  }
  int bitCout1(int n) {
    int cnt = 0;
    while (n) {
      cnt++;
      n &= n - 1;
    }
    return cnt;
  }

 public:
  int countPalindromicSubsequence(string s) {
    int n = s.size();
    int suf[26]{};
    for (int i = 1; i < n; ++i) {
      suf[s[i] - 'a']++;
    }
    int pre[26]{};
    int has[26]{};
    for (int i = 1; i < n - 1; ++i) {
      pre[s[i - 1] - 'a']++;
      suf[s[i] - 'a']--;
      for (int j = 0; j < 26; ++j) {
        if (pre[j] > 0 && suf[j] > 0) {
          // has[s[i] - 'a']++;
          // 为什么这句是错的？
          // 想想有没有进行去重操作，如果后续的i，和前面的i有重复且此时，
          // suf[j]和pre[j]也大于0，则会统计重复的回文子序列所以需要去重，
          // 使用位运算含义是，对于s[i]这个字符has[s[i] - a]的第j位为1，
          // 代表s[i]这个字符与第j个字母构成回文子串
          has[s[i] - 'a'] |= (1 << j);
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < 26; ++i) {
      // ans += __builtin_popcount(has[i]);
      // ans += bitCout(has[i]);
      ans += bitCout1(has[i]);
    }
    return ans;
  }
};