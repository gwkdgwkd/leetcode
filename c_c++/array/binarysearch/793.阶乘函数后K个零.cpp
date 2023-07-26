/*
f(x)是x!末尾是0的数量。
回想一下x! = 1 * 2 * 3 * ... * x，且0! = 1。
例如，f(3) = 0，因为3! = 6的末尾没有0；
而f(11) = 2，因为11!=39916800末端有2个0。
给定k，找出返回能满足f(x) = k的非负整数x的数量。

示例1：
输入：k = 0
输出：5
解释：0!, 1!, 2!, 3!,和4!均符合k = 0的条件。

示例2：
输入：k = 5
输出：0
解释：没有匹配到这样的x!，符合k = 5的条件。

示例3：
输入：k = 3
输出：5

提示：0 <= k <= 10^9
*/

// 面试题1605阶乘尾数

// 172.阶乘后的零的写法：
long trailingZeroes(long n) {
  long res = 0;
  for (long d = n; d / 5 > 0; d = d / 5) {
    res += d / 5;
  }
  return res;
}

long left_bound(int target) {
  long lo = 0, hi = LONG_MAX;
  while (lo < hi) {
    long mid = lo + (hi - lo) / 2;
    if (trailingZeroes(mid) < target) {
      lo = mid + 1;
    } else if (trailingZeroes(mid) > target) {
      hi = mid;
    } else {
      hi = mid;
    }
  }

  return lo;
}
long right_bound(int target) {
  long lo = 0, hi = LONG_MAX;
  while (lo < hi) {
    long mid = lo + (hi - lo) / 2;
    if (trailingZeroes(mid) < target) {
      lo = mid + 1;
    } else if (trailingZeroes(mid) > target) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  return lo - 1;
}
int preimageSizeFZF(int k) { return right_bound(k) - left_bound(k) + 1; }

class Solution {
 public:
  // 计算x的阶乘末尾有多少个0：
  long zeta(long x) {
    long ans = 0;
    while (x) {
      x /= 5;
      ans += x;
    }
    return ans;
  }

  int preimageSizeFZF(int k) {
    long left = k, right = 5L * k;
    while (left <= right) {
      long mid = left + (right - left) / 2;
      long tmp = zeta(mid);
      if (tmp == k)
        return 5;
      else if (tmp > k)
        right = mid / 5 * 5 - 5;
      else
        left = mid / 5 * 5 + 5;
    }
    return 0;
  }
};
