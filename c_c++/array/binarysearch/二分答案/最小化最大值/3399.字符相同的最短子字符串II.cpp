/*
给一个长度为n的二进制字符串s和一个整数numOps。
可以对s执行以下操作，最多numOps ：
选择任意下标i（其中0<=i<n），并翻转s[i]，即如果s[i]=='1'，则将s[i]改为'0'，反之亦然。
需要最小化s的最长相同的长度，相同子字符串是指子字符串中的所有字符都相同。
返回执行所有操作后可获得的最小长度。

示例1：
输入：s = "000001", numOps = 1
输出：2
解释：将s[2]改为'1'，s变为"001001"。最长的所有字符相同的子串为s[0..1]和s[3..4]。

示例2：
输入：s = "0000", numOps = 2
输出：1
解释：将s[0]和s[2]改为'1'，s变为"1010"。

示例3：
输入：s = "0101", numOps = 0
输出：1


提示：
1 <= n == s.length <= 10^5
s仅由'0'和'1'组成。
0 <= numOps <= n
*/

// 二分答案
class Solution {
 public:
  int minLength(string s, int numOps) {
    unordered_map<int, int> cnt;
    int n = s.length();
    int l = 0;
    int r = 0;
    int c = 0;
    while (r < n) {
      if (s[l] == s[r]) {
        ++c;
        ++r;
      } else {
        l = r;
        cnt[c]++;
        c = 0;
      }
    }
    cnt[c]++;

    auto check = [&](int m) {
      int sum = 0;
      if (m == 1) {
        for (int i = 0; i < n; i++) {
          // 如果s[i]和i的奇偶性不同，cnt加一
          sum += (s[i] ^ i) & 1;
        }
        // n-cnt表示改成1010...
        sum = min(sum, n - sum);
      } else {
        for (auto p : cnt) {
          sum += (p.first / (m + 1)) * p.second;
        }
      }

      return sum <= numOps;
    };

    int left = 1;
    int right = 0;
    for (auto p : cnt) {
      right = max(right, p.first);
    }
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

class Solution {
 public:
  int minLength(string s, int numOps) {
    int n = s.length();
    auto check = [&](int m) -> bool {
      int cnt = 0;
      if (m == 1) {
        // 改成0101...
        for (int i = 0; i < n; i++) {
          // 如果s[i]和i的奇偶性不同，cnt加一
          cnt += (s[i] ^ i) & 1;
        }
        // n-cnt表示改成1010...
        cnt = min(cnt, n - cnt);
      } else {
        int k = 0;
        for (int i = 0; i < n; i++) {
          k++;
          // 到达连续相同子串的末尾
          if (i == n - 1 || s[i] != s[i + 1]) {
            cnt += k / (m + 1);
            k = 0;
          }
        }
      }
      return cnt <= numOps;
    };
    int left = 0, right = n;
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      (check(mid) ? right : left) = mid;
    }
    return right;
  }
};

// 最大堆
class Solution {
 public:
  int minLength(string s, int numOps) {
    int n = s.length();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      cnt += (s[i] ^ i) & 1;
    }
    if (min(cnt, n - cnt) <= numOps) {
      return 1;
    }

    priority_queue<tuple<int, int, int>> pq;
    int k = 0;
    for (int i = 0; i < n; i++) {
      k++;
      // 到达连续相同子串的末尾
      if (i == n - 1 || s[i] != s[i + 1]) {
        pq.emplace(k, k, 1);
        k = 0;
      }
    }

    while (numOps-- && get<0>(pq.top()) > 2) {
      auto [_, k, seg] = pq.top();
      pq.pop();
      pq.emplace(k / (seg + 1), k, seg + 1);  // 重新分割
    }
    return get<0>(pq.top());
  }
};
