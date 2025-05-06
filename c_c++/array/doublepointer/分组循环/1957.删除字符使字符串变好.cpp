/*
一个字符串如果没有三个连续相同字符，那么它就是一个好字符串。
给一个字符串s，请从s删除最少的字符，使它变成一个好字符串。
请返回删除后的字符串。题目数据保证答案总是唯一的。

示例1：
输入：s = "leeetcode"
输出："leetcode"
解释：从第一组'e'里面删除一个'e'，得到"leetcode"。
     没有连续三个相同字符，所以返回"leetcode"。

示例2：
输入：s = "aaabaaaa"
输出："aabaa"
解释：从第一组'a'里面删除一个'a'，得到"aabaaaa"。
     从第二组'a'里面删除两个'a'，得到"aabaa"。
     没有连续三个相同字符，所以返回"aabaa"。

示例3：
输入：s = "aab"
输出："aab"
解释：没有连续三个相同字符，所以返回"aab"。


提示：
1 <= s.length <= 10^5
s只包含小写英文字母。
*/

class Solution {
 public:
  string makeFancyString(string s) {
    int n = s.size();
    int left = 0;
    int right = 1;
    int cnt = 1;
    while (right < n) {
      if (s[right] != s[left]) {
        s[++left] = s[right];
        cnt = 1;
      } else {
        if (cnt < 2) {
          s[++left] = s[right];
          ++cnt;
        }
      }
      ++right;
    }
    return s.substr(0, left + 1);
  }
};

// 分组循环
class Solution {
 public:
  string makeFancyString(string s) {
    string res;
    for (int i = 0; i < s.size();) {
      int start = i;
      i++;
      while (i < s.size() && s[i] == s[i - 1]) {
        i++;
      }
      //[start,i)
      int len = min(2, i - start);
      while (len > 0) {
        res.push_back(s[start]);
        len--;
      }
    }
    return res;
  }
};