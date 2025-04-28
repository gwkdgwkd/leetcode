/*
给一个二进制字符串s和一个正整数k。
如果s的某个子字符串中1的个数恰好等于k，则称这个子字符串是一个美丽子字符串。
令len等于最短美丽子字符串的长度。
返回长度等于len且字典序最小的美丽子字符串。
如果s中不含美丽子字符串，则返回一个空字符串。
对于相同长度的两个字符串a和b，如果在a和b出现不同的第一个位置上，
a中该位置上的字符严格大于b中的对应字符，则认为字符串a字典序大于字符串b。
例如，"abcd"的字典序大于"abcc"，
因为两个字符串出现不同的第一个位置对应第四个字符，而d大于c。

示例1：
输入：s = "100011001", k = 3
输出："11001"
解释：示例中共有7个美丽子字符串：
     1.子字符串"100011001"。
     2.子字符串"100011001"。
     3.子字符串"100011001"。
     4.子字符串"100011001"。
     5.子字符串"100011001"。
     6.子字符串"100011001"。
     7.子字符串"100011001"。
     最短美丽子字符串的长度是5。
     长度为5且字典序最小的美丽子字符串是子字符串"11001"。

示例2：
输入：s = "1011", k = 2
输出："11"
解释：示例中共有3个美丽子字符串：
     1.子字符串"1011"。
     2.子字符串"1011"。
     3.子字符串"1011"。
     最短美丽子字符串的长度是2。
     长度为2且字典序最小的美丽子字符串是子字符串"11"。

示例3：
输入：s = "000", k = 1
输出：""
解释：示例中不存在美丽子字符串。


提示：
1 <= s.length <= 100
1 <= k <= s.length
*/

class Solution {
 public:
  string shortestBeautifulSubstring(string s, int k) {
    int n = s.size();
    int t = 0;
    // for(int i = 0; i < n; ++i) {
    //     if(s[i] == '1') {
    //         ++t;
    //     }
    // }
    // if(t < k) {
    //     return "";
    // }

    if (ranges::count(s, '1') < k) {
      return "";
    }
    int left = 0;
    int right = 0;
    string ans = s;
    int cnt = 0;

    while (right < n) {
      if (s[right++] == '1') {
        ++cnt;
      }
      while (cnt > k || s[left] == '0') {
        if (s[left++] == '1') {
          --cnt;
        }
      }
      if (cnt == k) {
        string tmp = s.substr(left, right - left);
        if (tmp.length() < ans.length() ||
            (tmp.length() == ans.length() && tmp < ans)) {
          ans = move(tmp);
        }
      }
    }
    return ans;
  }
};