/*
 * @lc app=leetcode.cn id=69 lang=c
 *
 * [69] x 的平方根
 */

// @lc code=start

// 袖珍计算器算法是一种用指数函数exp和对数函数ln代替平方根函数的方法。通过有限的可以使用的数学函数，得到我们想要计算的结果。
int mySqrt(int x) {
  if (x == 0) {
    return 0;
  }
  int ans = exp(0.5 * log(x));
  return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
}

// 二分查找法
int mySqrt(int x) {
  int left = 0;
  int right = x;
  int mid;
  int ans = -1;
  while (left <= right) {
    mid = left + (right - left) / 2;
    if ((long long)mid * mid <= x) {
      ans = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return ans;
}

// @lc code=end
