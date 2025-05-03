/*
给一个字符串word和一个非负整数k。
返回word的中，每个元音字母（'a'、'e'、'i'、'o'、'u'）至少出现一次，
并且恰好包含k个辅音字母的子字符串的总数。

示例1：
输入：word = "aeioqq", k = 1
输出：0
解释：不存在包含所有元音字母的子字符串。

示例2：
输入：word = "aeiou", k = 0
输出：1
解释：唯一一个包含所有元音字母且不含辅音字母的子字符串是 word[0..4]，即"aeiou"。

示例3：
输入：word = "ieaouqqieaouqq", k = 1
输出：3
解释：包含所有元音字母并且恰好含有一个辅音字母的子字符串有：
     word[0..5]，即"ieaouq"。
     word[6..11]，即"qieaou"。
     word[7..12]，即"ieaouq"。

提示：
5 <= word.length <= 2 * 10^5
word仅由小写英文字母组成。
0 <= k <= word.length - 5
*/

class Solution {
 public:
  long long countOfSubstrings(string word, int k) {
    auto check = [](int *hash) -> bool {
      return hash['a' - 'a'] && hash['e' - 'a'] && hash['i' - 'a'] &&
             hash['o' - 'a'] && hash['u' - 'a'];
    };

    auto get = [](int *hash) -> int {
      int cnt = 0;
      for (char c = 'a'; c <= 'z'; ++c) {
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
          cnt += hash[c - 'a'];
        }
      }
      return cnt;
    };

    int l1 = 0, l2 = 0;
    int r = 0;
    long long ans = 0;
    int n = word.size();
    int hash1[26]{};
    int hash2[26]{};
    while (r < n) {
      hash1[word[r] - 'a']++;
      while (check(hash1) && get(hash1) > k) {
        // 能不能把使用至多？
        // 至多和前面的每个元音字母至少出现一次冲突，至少要求子串越长越好，
        // 而至多要求子串越短越好，这样必须分开求解（总共要计算四个滑动窗口），
        // 相比使用至少的代码的直接求解要麻烦许多。
        hash1[word[l1++] - 'a']--;
      }

      hash2[word[r] - 'a']++;
      while (check(hash2) && get(hash2) > k - 1) {
        hash2[word[l2++] - 'a']--;
      }

      ans += l2 - l1;
      ++r;
    }
    return ans;
  }
};