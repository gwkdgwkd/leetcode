/*
给一个仅由小写英文字母组成的字符串s。
如果一个字符串仅由单一字符组成，那么它被称为特殊字符串。
例如，字符串"abc"不是特殊字符串，而字符串"ddd"、"zz"和"f"是特殊字符串。
返回在s中出现至少三次的最长特殊子字符串的长度，
如果不存在出现至少三次的特殊子字符串，则返回-1。
子字符串是字符串中的一个连续非空字符序列。

示例1：
输入：s = "aaaa"
输出：2
解释：出现三次的最长特殊子字符串是"aa"：子字符串"aaaa"、"aaaa"和"aaaa"。
     可以证明最大长度是 2 。

示例2：
输入：s = "abcdef"
输出：-1
解释：不存在出现至少三次的特殊子字符串。因此返回-1。

示例3：
输入：s = "abcaba"
输出：1
解释：出现三次的最长特殊子字符串是"a"：子字符串"abcaba"、"abcaba"和"abcaba"。
     可以证明最大长度是 1 。


提示：
3 <= s.length <= 5 * 10^5
s仅由小写英文字母组成。
*/

class Solution {
 public:
  int maximumLength(string s) {
    auto check = [&s](int l) {
      unordered_map<string, int> um;
      int n = s.size();
      for (int i = 0; i < n - l + 1; ++i) {
        int j = i;
        while (j < n && s[j] == s[i]) {
          ++j;
          if (j - i == l) {
            um[s.substr(i, j - i)]++;
            break;
          }
        }
      }
      for (auto it = um.begin(); it != um.end(); ++it) {
        if (it->second >= 3) {
          return true;
        }
      }
      return false;
    };

    int left = 1;
    int right = s.size();
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right == 0 ? -1 : right;
  }
};

class Solution {
 public:
  int maximumLength(string s) {
    int n = s.size();
    unordered_map<char, vector<int>> cnt;
    for (int i = 0, j = 0; i < s.size(); i = j) {
      while (j < s.size() && s[j] == s[i]) {
        j++;
      }
      cnt[s[i]].emplace_back(j - i);
    }

    int res = -1;
    for (auto &[_, vec] : cnt) {
      int lo = 1, hi = n - 2;
      while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        int count = 0;
        for (int x : vec) {
          if (x >= mid) {
            count += x - mid + 1;
          }
        }
        if (count >= 3) {
          res = max(res, mid);
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }
    }
    return res;
  }
};