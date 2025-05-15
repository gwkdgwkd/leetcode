/*
给一个下标从0开始的字符串数组words，和一个下标从0开始的二进制数组groups，两个数组长度都是n。
需要从words中选出最长子序列。
如果对于序列中的任何两个连续串，二进制数组groups中它们的对应元素不同，则words的子序列是不同的。
正式来说，需要从下标[0, 1, ..., n - 1]中选出一个 最长子序列，
将这个子序列记作长度为k的[i0, i1, ..., ik - 1]，
对于所有满足0 <= j < k - 1的j都有groups[ij] != groups[ij + 1]。
请返回一个字符串数组，它是下标子序列依次对应words数组中的字符串连接形成的字符串数组。
如果有多个答案，返回任意一个。
注意：words中的元素是不同的。

示例1：
输入：words = ["e","a","b"], groups = [0,0,1]
输出：["e","b"]
解释：一个可行的子序列是[0,2]，因为 groups[0] != groups[2]。
     所以一个可行的答案是[words[0],words[2]] = ["e","b"]。
     另一个可行的子序列是[1,2]，因为 groups[1] != groups[2]。
     得到答案为[words[1],words[2]] = ["a","b"]。
     这也是一个可行的答案，符合题意的最长子序列的长度为2。

示例2：
输入：words = ["a","b","c","d"], groups = [1,0,1,1]
输出：["a","b","c"]
解释：一个可行的子序列为[0,1,2]，因为groups[0]!=groups[1]且groups[1]!=groups[2]。
     所以一个可行的答案是[words[0],words[1],words[2]] = ["a","b","c"]。
     另一个可行的子序列为[0,1,3]，因为groups[0]!=groups[1]且groups[1]!=groups[3]。
     得到答案为[words[0],words[1],words[3]]=["a","b","d"]。
     这也是一个可行的答案，符合题意的最长子序列的长度为3。


提示：
1 <= n == words.length == groups.length <= 100
1 <= words[i].length <= 10
groups[i]是0或1。
words中的字符串互不相同。
words[i]只包含小写英文字母。
*/

// 贪心，一次遍历
class Solution {
 public:
  vector<string> getLongestSubsequence(vector<string>& words,
                                       vector<int>& groups) {
    int n = groups.size();
    vector<string> ans;
    for (int i = 0; i < n; ++i) {
      if (i == n - 1 || groups[i] != groups[i + 1]) {
        ans.push_back(words[i]);
      }
    }
    return ans;
  }
};

// 动态规划