/*
丑数是可以被a或b或c整除的正整数。
给四个整数：n 、a 、b 、c，请设计一个算法来找出第n个丑数。

示例1：
输入：n = 3, a = 2, b = 3, c = 5
输出：4
解释：丑数序列为 2, 3, 4, 5, 6, 8, 9, 10... 其中第3个是4。

示例2：
输入：n = 4, a = 2, b = 3, c = 4
输出：6
解释：丑数序列为2, 3, 4, 6, 8, 9, 10, 12... 其中第4个是6。

示例3：
输入：n = 5, a = 2, b = 11, c = 13
输出：10
解释：丑数序列为2, 4, 6, 8, 10, 11, 12, 13... 其中第5个是10。


提示：
1 <= n, a, b, c <= 10^9
1 <= a * b * c <= 10^18
本题结果在[1, 2 * 10^9]的范围内
*/

class Solution {
  typedef long long ll;
  // 最大公约数
  ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
  // 最小公倍数
  ll lcm(ll a, ll b) { return a * b / gcd(a, b); }

 public:
  int nthUglyNumber(int n, int a, int b, int c) {
    ll ab = lcm(a, b);
    ll ac = lcm(a, c);
    ll bc = lcm(b, c);
    ll abc = lcm(ab, c);
    auto check = [&](ll m) {
      ll cnt = m / a + m / b + m / c - m / ab - m / ac - m / bc + m / abc;
      return cnt >= n;
    };
    ll countPerCycle = check(abc);  // 一个最小公倍数周期内丑数个数
    int cycles = n / countPerCycle;  // n包含多少个最小公倍数周期
    // 搜索区间周期优化为[abc*cycles, abc*(cycles+1))周期区间左闭右开
    ll left = abc * cycles - 1;
    ll right = abc * (cycles + 1);
    while (left <= right) {
      ll mid = (left + right) >> 1;
      // 容斥原理：计算cnt为[1,mid]中的丑数个数
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return (int)left;
  }
};

class Solution {
 public:
  int nthUglyNumber(int n, int a, int b, int c) {
    const long long la = a;
    const long long lb = b;
    const long long lc = c;
    const long long lab = lcm(la, lb);
    const long long lac = lcm(la, lc);
    const long long lbc = lcm(lb, lc);
    const long long labc = lcm(lab, lc);
    const long long maxabc = max({a, b, c});
    const auto countLessEqual = [=](long long x) -> long long {
      return x / la + x / lb + x / lc - x / lab - x / lac - x / lbc + x / labc;
    };
    const long long m = countLessEqual(labc);
    const long long q = n / m, r = n % m;
    long long hi = min(labc, r * maxabc);
    long long lo = 0;
    while (lo <= hi) {
      const long long mi = (lo + hi) / 2;
      if (countLessEqual(mi) < r)
        lo = mi + 1;
      else
        hi = mi - 1;
    }
    return lo + q * labc;
  }
};
