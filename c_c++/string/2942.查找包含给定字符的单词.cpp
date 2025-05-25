/*
给一个下标从0开始的字符串数组words和一个字符x。
请返回一个下标数组，表示下标在数组中对应的单词包含字符x。
注意，返回的数组可以是任意顺序。

示例1：
输入：words = ["leet","code"], x = "e"
输出：[0,1]
解释："e"在两个单词中都出现了："leet"和"code"。所以我们返回下标0和1。

示例2：
输入：words = ["abc","bcd","aaaa","cbc"], x = "a"
输出：[0,2]
解释："a"在"abc"和"aaaa"中出现了，所以我们返回下标0和2。

示例3：
输入：words = ["abc","bcd","aaaa","cbc"], x = "z"
输出：[]
解释："z"没有在任何单词中出现。所以我们返回空数组。


提示：
1 <= words.length <= 50
1 <= words[i].length <= 50
x是一个小写英文字母。
words[i]只包含小写英文字母。
*/

class Solution {
 public:
  vector<int> findWordsContaining(vector<string>& words, char x) {
    int n = words.size();
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
      for (char c : words[i]) {
        if (c == x) {
          ans.emplace_back(i);
          break;
        }
      }
    }
    return ans;
  }
};