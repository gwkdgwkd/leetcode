/*
一个正整数如果能被a或b整除，那么它是神奇的。
给定三个整数n,a,b，返回第n个神奇的数字。
因为答案可能很大，所以返回答案对10^9+7取模后的值。

示例1：
输入：n = 1, a = 2, b = 3
输出：2

示例2：
输入：n = 4, a = 2, b = 3
输出：6


提示：
1 <= n <= 10^9
2 <= a, b <= 4 * 10^4
*/

// 二分答案 + 容斥原理
class Solution {
 public:
  int nthMagicalNumber(int n, int a, int b) {
    const int MOD = 1'000'000'007;
    long long lcm = std::lcm(a, b);
    long long left = min(a, b) + n - 2;
    long long right = 1LL * min(a, b) * n;  // 开区间(left, right)
    while (left + 1 < right) {              // 开区间不为空
      long long mid = left + (right - left) / 2;
      (mid / a + mid / b - mid / lcm >= n ? right : left) = mid;
    }

    return right % MOD;
  }
};

class Solution {
 public:
  const int MOD = 1e9 + 7;
  int nthMagicalNumber(int n, int a, int b) {
    long long l = min(a, b);
    long long r = (long long)n * min(a, b);
    int c = lcm(a, b);
    while (l <= r) {
      long long mid = (l + r) / 2;
      long long cnt = mid / a + mid / b - mid / c;
      if (cnt >= n) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    return (r + 1) % MOD;
  }
};

// 找规律
class Solution {
 public:
  const int MOD = 1e9 + 7;
  int nthMagicalNumber(int n, int a, int b) {
    int c = lcm(a, b);
    int m = c / a + c / b - 1;
    int r = n % m;
    int res = (long long)c * (n / m) % MOD;
    if (r == 0) {
      return res;
    }
    int addA = a, addB = b;
    for (int i = 0; i < r - 1; ++i) {
      if (addA < addB) {
        addA += a;
      } else {
        addB += b;
      }
    }
    return (res + min(addA, addB) % MOD) % MOD;
  }
};
