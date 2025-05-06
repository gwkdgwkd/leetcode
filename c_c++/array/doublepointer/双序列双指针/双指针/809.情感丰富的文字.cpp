/*
有时候人们会用重复写一些字母来表示额外的感受，
比如"hello" -> "heeellooo","hi" -> "hiii"。
将相邻字母都相同的一串字符定义为相同字母组，例如："h", "eee", "ll", "ooo"。
对于一个给定的字符串S，如果另一个单词能够通过将一些字母组扩张从而使其和S相同，
我们将这个单词定义为可扩张的（stretchy），扩张操作定义如下：
选择一个字母组（包含字母c），然后往其中添加相同的字母c使其长度达到3或以上。
例如，以"hello"为例，我们可以对字母组"o"扩张得到"hellooo"，
但是无法以同样的方法得到"helloo"因为字母组"oo"长度小于3。
此外，我们可以进行另一种扩张"ll"->"lllll"以获得"helllllooo"。
如果s = "helllllooo"，那么查询词"hello"是可扩张的，
因为可以对它执行这两种扩张操作使得query="hello"->"hellooo"->"helllllooo"=s。
输入一组查询单词，输出其中可扩张的单词数量。

示例：
输入：
s = "heeellooo"
words = ["hello", "hi", "helo"]
输出：1
解释：我们能通过扩张"hello"的"e"和"o"来得到"heeellooo"。
     我们不能通过扩张"helo"来得到"heeellooo"，因为"ll"的长度小于3。


提示：
1 <= s.length, words.length <= 100
1 <= words[i].length <= 100
s和所有在words中的单词都只由小写字母组成。
*/

class Solution {
  bool isExpressive(const string &s, const string &w) {
    int n = s.size();
    int m = w.size();

    int i = 0;
    int j = 0;
    while (i < n && j < m) {
      if (s[i++] != w[j++]) {
        return false;
      }
      int ci = 1;
      while (i < n && s[i] == s[i - 1]) {
        ++ci;
        ++i;
      }
      int cj = 1;
      while (j < m && w[j] == w[j - 1]) {
        ++cj;
        ++j;
      }

      if (ci < cj || (ci != cj && ci < 3)) {
        return false;
      }
    }
    return i == n && j == m;
  }

 public:
  int expressiveWords(string s, vector<string> &words) {
    int n = words.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (isExpressive(s, words[i])) {
        ++ans;
      }
    }
    return ans;
  }
};