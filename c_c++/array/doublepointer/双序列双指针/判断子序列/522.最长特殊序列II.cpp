/*
给定字符串列表strs，返回其中最长的特殊序列的长度。如果最长特殊序列不存在，返回-1。
特殊序列定义如下：该序列为某字符串独有的子序列（即不能是其他字符串的子序列）。
s的子序列可以通过删去字符串s中的某些字符实现。
例如，"abc"是"aebdc"的子序列，因为可以删除"aebdc"中的下划线字符来得到"abc"。
"aebdc"的子序列还包括"aebdc"、 "aeb"和""(空字符串)。

示例1：
输入：strs = ["aba","cdc","eae"]
输出：3

示例2：
输入：strs = ["aaa","aaa","aa"]
输出：-1


提示:
2 <= strs.length <= 50
1 <= strs[i].length <= 10
strs[i]只包含小写英文字母
*/

class Solution {
  // 时间复杂度：O(n^2m)，其中n是strs的长度，m是strs[i]的最大长度。
  //           最坏情况下，所有字符串长度均为m，需要枚举O(n^2)对字符串，
  //           每对需要O(m)的时间判断，所以时间复杂度为O(n^2m)。
  // 空间复杂度：O(1)。
  bool isSubsequence(string s, string t) {
    int n = s.size();
    int m = t.size();
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
      if (s[i] == t[j]) {
        ++j;
      }
      ++i;
    }
    return j == m;
  }

 public:
  int findLUSlength(vector<string>& strs) {
    // 按字符串长度从大到小排队：
    sort(strs.begin(), strs.end(),
         [](const auto& a, const auto& b) { return a.size() > b.size(); });
    int n = strs.size();
    for (int i = 0; i < n; ++i) {
      int j = 0;
      while (j < n) {
        if (i != j && isSubsequence(strs[j], strs[i])) {
          break;
        }
        ++j;
      }
      if (j == n) {
        return strs[i].size();
      }
    }

    return -1;
  }
};