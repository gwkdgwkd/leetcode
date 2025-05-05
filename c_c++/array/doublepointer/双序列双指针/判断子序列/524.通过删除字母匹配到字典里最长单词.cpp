/*
给一个字符串s和一个字符串数组dictionary，找出并返回dictionary中最长的字符串，
该字符串可以通过删除s中的某些字符得到。
如果答案不止一个，返回长度最长且字母序最小的字符串。如果答案不存在，则返回空字符串。

示例1：
输入：s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
输出："apple"

示例2：
输入：s = "abpcplea", dictionary = ["a","b","c"]
输出："a"


提示：
1 <= s.length <= 1000
1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 1000
s和dictionary[i]仅由小写英文字母组成
*/

class Solution {
  // [392.判断子序列]的方法
  bool isSubsequence(string s, string t) {
    int ns = s.size();
    int nt = t.size();
    int is = 0;
    int it = 0;
    while (is < ns && it < nt) {
      if (s[is] == t[it]) {
        ++it;
      }
      ++is;
    }

    return it == nt;
  }

 public:
  string findLongestWord(string s, vector<string> &dictionary) {
    sort(dictionary.begin(), dictionary.end(), [&](string &a, string &b) {
      if (a.size() == b.size()) {
        return a < b;
      }
      return a.size() > b.size();
    });
    for (string &t : dictionary) {
      if (isSubsequence(s, t)) {
        return t;
      }
    }

    return "";
  }
};