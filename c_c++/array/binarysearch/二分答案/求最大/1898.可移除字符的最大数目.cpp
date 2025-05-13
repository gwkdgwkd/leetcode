/*
给两个字符串s和p，其中p是s的一个子序列。
同时，给一个元素互不相同且下标从0开始计数的整数数组removable，
该数组是s中下标的一个子集（s的下标也从0开始计数）。
请找出一个整数k（0 <= k <= removable.length），
选出removable中的前k个下标，然后从s中移除这些下标对应的k个字符。
整数k需满足：在执行完上述步骤后，p仍然是s的一个 子序列。
更正式的解释是，对于每个0 <= i < k，先标记出位于s[removable[i]]的字符，
接着移除所有标记过的字符，然后检查p是否仍然是s的一个子序列。
返回可以找出的最大k，满足在移除字符后p仍然是s的一个子序列。
字符串的一个子序列是一个由原字符串生成的新字符串，
生成过程中可能会移除原字符串中的一些字符（也可能不移除）但不改变剩余字符之间的相对顺序。

示例1：
输入：s = "abcacb", p = "ab", removable = [3,1,0]
输出：2
解释：在移除下标3和1对应的字符后，"abcacb"变成"accb"。"ab"是"accb"的一个子序列。
     如果移除下标3、1和0对应的字符后，"abcacb"变成"ccb"，那么"ab"就不再是s的一个子序列。
     因此，最大的k是2。

示例2：
输入：s = "abcbddddd", p = "abcd", removable = [3,2,1,4,5,6]
输出：1
解释：在移除下标3对应的字符后，"abcbddddd"变成"abcddddd"。
     "abcd"是"abcddddd"的一个子序列。

示例3：
输入：s = "abcab", p = "abc", removable = [0,1,2,3,4]
输出：0
解释：如果移除数组removable的第一个下标，"abc"就不再是s的一个子序列。


提示：
1 <= p.length <= s.length <= 10^5
0 <= removable.length < s.length
0 <= removable[i] < s.length
p是s的一个子字符串
s和p都由小写英文字母组成
removable中的元素互不相同
*/

class Solution {
 public:
  int maximumRemovals(string s, string p, vector<int>& removable) {
    auto check = [&p, &removable](string s, int k) mutable {
      int j = 0;
      for (int i = 0; i < k; ++i) {
        s[removable[j++]] = '0';
      }

      int i = 0;
      j = 0;
      while (i < s.size() && j < p.size()) {
        if (s[i] == p[j]) {
          ++i;
          ++j;
        } else {
          ++i;
        }
      }
      return j == p.size();
    };
    int left = 0;
    int right = removable.size();
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(s, mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};

class Solution {
 public:
  int maximumRemovals(string s, string p, vector<int>& removable) {
    int ns = s.size();
    int np = p.size();
    int n = removable.size();
    // 辅助函数，用来判断移除k个下标后p是否是s_k的子序列
    auto check = [&](int k) -> bool {
      vector<int> state(ns, 1);  // s中每个字符的状态
      for (int i = 0; i < k; ++i) {
        state[removable[i]] = 0;
      }
      // 匹配s_k与p
      int j = 0;
      for (int i = 0; i < ns; ++i) {
        // s[i]未被删除且与p[j]相等时，匹配成功，增加j
        if (state[i] && s[i] == p[j]) {
          ++j;
          if (j == np) {
            return true;
          }
        }
      }
      return false;
    };

    // 二分查找
    int l = 0;
    int r = n + 1;
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l - 1;
  }
};
