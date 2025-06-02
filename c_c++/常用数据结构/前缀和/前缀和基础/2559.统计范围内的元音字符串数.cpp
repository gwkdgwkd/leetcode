/*
给一个下标从0开始的字符串数组words以及一个二维整数数组queries。
每个查询queries[i]=[li, ri]会要求我们统计，
在words中下标在li到ri范围内（包含这两个值）并且以元音开头和结尾的字符串的数目。
返回一个整数数组，其中数组的第i个元素对应第i个查询的答案。
注意：元音字母是'a'、'e'、'i'、'o'和'u'。

示例1：
输入：words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
输出：[2,3,0]
解释：以元音开头和结尾的字符串是"aba"、"ece"、"aa"和"e"。
     查询[0,2]结果为2（字符串 "aba" 和 "ece"）。
     查询[1,4]结果为3（字符串 "ece"、"aa"、"e"）。
     查询[1,1]结果为0。
     返回结果[2,3,0]。

示例2：
输入：words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
输出：[3,2,1]
解释：每个字符串都满足这一条件，所以返回[3,2,1]。


提示：
1 <= words.length <= 10^5
1 <= words[i].length <= 40
words[i] 仅由小写英文字母组成
sum(words[i].length) <= 3 * 10^5
1 <= queries.length <= 105
0 <= queries[j][0] <= queries[j][1] < words.length
*/

class Solution {
 public:
  vector<int> vowelStrings(vector<string>& words,
                           vector<vector<int>>& queries) {
    int n = words.size();
    vector<int> v(n, 0);
    vector<int> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      char h = words[i][0];
      char t = words[i].back();
      if ((h == 'a' || h == 'e' || h == 'i' || h == 'o' || h == 'u') &&
          (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u')) {
        v[i] = 1;
      }

      pre[i + 1] = pre[i] + v[i];
    }

    vector<int> ans;
    for (int i = 0; i < queries.size(); ++i) {
      ans.emplace_back(pre[queries[i][1] + 1] - pre[queries[i][0]]);
    }

    return ans;
  }
};