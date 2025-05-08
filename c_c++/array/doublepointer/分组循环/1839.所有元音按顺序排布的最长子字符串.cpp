/*
当一个字符串满足如下条件时，我们称它是美丽的：
所有5个英文元音字母（'a'，'e'，'i'，'o'，'u'）都必须至少出现一次。
这些元音字母的顺序都必须按照字典序升序排布，
也就是说所有的'a'都在'e'前面，所有的'e'都在'i'前面，以此类推。
比方说，字符串"aeiou"和"aaaaaaeiiiioou"都是美丽的，
但是"uaeio"，"aeoiu"和"aaaeeeooo"不是美丽的。
给一个只包含英文元音字母的字符串word，请你返回word中最长美丽子字符串的长度。
如果不存在这样的子字符串，请返回0。
子字符串是字符串中一个连续的字符序列。

示例1：
输入：word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
输出：13
解释：最长子字符串是"aaaaeiiiiouuu"，长度为13。

示例2：
输入：word = "aeeeiiiioooauuuaeiou"
输出：5
解释：最长子字符串是"aeiou"，长度为5。

示例3：
输入：word = "a"
输出：0
解释：没有美丽子字符串，所以返回0。


提示：
1 <= word.length <= 5 * 10^5
word 只包含字符'a'，'e'，'i'，'o'和'u'。
*/

class Solution {
 public:
  int longestBeautifulSubstring(string word) {
    int n = word.size();
    int ans = 0;
    int left = 0;
    int right = 0;
    unordered_map<char, int> cnt;
    while (right < n) {
      if (right > 0 && word[right - 1] > word[right]) {
        if (cnt['a'] && cnt['e'] && cnt['i'] && cnt['o'] && cnt['u']) {
          ans = max(ans, right - left);
        }
        cnt['a'] = cnt['e'] = cnt['i'] = cnt['o'] = cnt['u'] = 0;
        left = right;
      }
      cnt[word[right]]++;
      ++right;
    }
    if (cnt['a'] && cnt['e'] && cnt['i'] && cnt['o'] && cnt['u']) {
      ans = max(ans, right - left);
    }
    return ans;
  }
};

class Solution {
 private:
  static unordered_set<string> transit;

 public:
  int longestBeautifulSubstring(string word) {
    int cur = 0, ans = 0;
    char status = 'x';

    for (char ch : word) {
      if (transit.count(string(1, status) + ch)) {
        if (status != 'a' && ch == 'a') {
          cur = 1;
        } else {
          ++cur;
        }
        status = ch;
      } else {
        cur = 0;
        status = 'x';
      }
      if (status == 'u') {
        ans = max(ans, cur);
      }
    }

    return ans;
  }
};
unordered_set<string> Solution::transit = {"ae", "ei", "io", "ou", "aa",
                                           "ee", "ii", "oo", "uu", "xa",
                                           "ea", "ia", "oa", "ua"};