/*
给定一个字符串数组words，和一个数组groups，两个数组长度都是n。
两个长度相等字符串的汉明距离定义为对应位置字符不同的数目。
需要从下标[0, 1, ..., n - 1]中选出一个最长子序列，
将这个子序列记作长度为k的[i0, i1, ..., ik - 1]，它需要满足以下条件：
相邻下标对应的groups值不同。
即，对于所有满足0<j + 1<k的j都有groups[ij]!=groups[ij+1]。
对于所有0<j + 1<k的下标j，都满足words[ij]和words[ij+1]的长度相等，
且两个字符串之间的汉明距离为1。
请返回一个字符串数组，它是下标子序列依次对应words数组中的字符串连接形成的字符串数组。
如果有多个答案，返回任意一个。
子序列指的是从原数组中删一些（也可能不删）元素，剩余元素不改变相对位置得到的新的数组。
注意：words中的字符串长度可能不相等。

示例1：
输入：words = ["bab","dab","cab"], groups = [1,2,2]
输出：["bab","cab"]
解释：一个可行的子序列是[0,2]。
     groups[0] != groups[2]
     words[0].length == words[2].length且它们之间的汉明距离为1。
     所以一个可行的答案是[words[0],words[2]] = ["bab","cab"]。
     另一个可行的子序列是[0,1]。
     groups[0] != groups[1]
     words[0].length = words[1].length且它们之间的汉明距离为1。
     所以另一个可行的答案是[words[0],words[1]] = ["bab","dab"]。
     符合题意的最长子序列的长度为2。

示例2：
输入：words = ["a","b","c","d"], groups = [1,2,3,4]
输出：["a","b","c","d"]
解释：我们选择子序列[0,1,2,3]。它同时满足两个条件。
     所以答案为[words[0],words[1],words[2],words[3]] = ["a","b","c","d"]。
     它是所有下标子序列里最长且满足所有条件的。
     所以它是唯一的答案。


提示：
1 <= n == words.length == groups.length <= 1000
1 <= words[i].length <= 10
1 <= groups[i] <= n
words中的字符串互不相同。
words[i]只包含小写英文字母。
*/

class Solution {
 public:
  vector<string> getWordsInLongestSubsequence(vector<string>& words,
                                              vector<int>& groups) {
    auto check = [&words](int i, int j) {
      int cnt = 0;
      int n = words[i].size();
      int m = words[j].size();
      if (n != m) {
        return false;
      }
      for (int k = 0; k < n; ++k) {
        if (words[i][k] != words[j][k]) {
          if (++cnt > 1) {
            return false;
          }
        }
      }
      return cnt == 1;
    };

    int n = words.size();
    vector<int> f(n), from(n);
    int max_i = n - 1;

    for (int i = n - 1; i >= 0; i--) {
      for (int j = i + 1; j < n; j++) {
        // 提前比较f[j]与f[i]的大小，如果f[j] <= f[i]，就不用执行更耗时的check了
        if (f[j] > f[i] && groups[j] != groups[i] && check(i, j)) {
          f[i] = f[j];
          from[i] = j;
        }
      }
      f[i]++;  // 加一写在这里
      if (f[i] > f[max_i]) {
        max_i = i;
      }
    }

    int i = max_i;
    int m = f[i];
    vector<string> ans(m);
    for (int k = 0; k < m; k++) {
      ans[k] = words[i];
      i = from[i];
    }
    return ans;
  }
};
