/*
给一个下标从0开始的字符串s，以及一个下标从0开始的整数数组spaces。
数组spaces描述原字符串中需要添加空格的下标。每个空格都应该插入到给定索引处的字符值之前。
例如，s = "EnjoyYourCoffee"且spaces = [5, 9]，
那么我们需要在'Y'和'C'之前添加空格，这两个字符分别位于下标5和下标9。
因此，最终得到"Enjoy Your Coffee"。
请添加空格，并返回修改后的字符串。

示例1：
输入：s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
输出："Leetcode Helps Me Learn"
解释：下标 8、13和15对应"LeetcodeHelpsMeLearn"中加粗斜体字符。
     接着在这些字符前添加空格。

示例2：
输入：s = "icodeinpython", spaces = [1,5,7,9]
输出："i code in py thon"
解释：下标1、5、7和9对应"icodeinpython"中加粗斜体字符。
     接着在这些字符前添加空格。

示例3：
输入：s = "spacing", spaces = [0,1,2,3,4,5,6]
输出：" s p a c i n g"
解释：字符串的第一个字符前可以添加空格。


提示：
1 <= s.length <= 3 * 10^5
s 仅由大小写英文字母组成
1 <= spaces.length <= 3 * 10^5
0 <= spaces[i] <= s.length - 1
spaces中的所有值严格递增
*/

class Solution {
 public:
  string addSpaces(string s, vector<int>& spaces) {
    int n = s.size();
    int m = spaces.size();
    string ans;
    ans.resize(m + n);

    int j = 0;
    int k = 0;
    for (int i = 0; i < n; ++i) {
      if (j < m && i == spaces[j]) {
        ans[k++] = ' ';
        ++j;
      }
      ans[k++] = s[i];
    }
    return ans;
  }
};