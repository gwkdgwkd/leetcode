/*
给一个下标从0开始的字符串数组words。
如果两个字符串由相同的字符组成，则认为这两个字符串相似。
例如，"abca"和"cba"相似，因为它们都由字符'a'、'b'、'c'组成。
然而，"abacba"和"bcfd"不相似，因为它们不是相同字符组成的。
请找出满足字符串words[i]和words[j]相似的下标对(i,j)，
并返回下标对的数目，其中0 <= i < j <= words.length - 1。

示例1：
输入：words = ["aba","aabb","abcd","bac","aabc"]
输出：2
解释：共有2对满足条件：
     i = 0且j = 1：words[0]和words[1]只由字符'a'和'b'组成。
     i = 3且j = 4：words[3]和words[4]只由字符'a'、'b'和'c'。

示例2：
输入：words = ["aabb","ab","ba"]
输出：3
解释：共有3对满足条件：
     i = 0且j = 1 ：words[0]和words[1]只由字符'a'和'b'组成。
     i = 0且j = 2 ：words[0]和words[2]只由字符'a'和'b'组成。
     i = 1且j = 2 ：words[1]和words[2]只由字符'a'和'b'组成。

示例3：
输入：words = ["nba","cba","dba"]
输出：0
解释：不存在满足条件的下标对，返回0。


提示：
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i]仅由小写英文字母组成
*/

class Solution {
 public:
  int similarPairs(vector<string>& words) {
    unordered_map<int, int> cnt;
    int ans = 0;
    for (auto word : words) {
      int mask = 0;
      for (char c : word) {
        mask |= 1 << (c - 'a');
      }
      ans += cnt[mask]++;
    }
    return ans;
  }
};