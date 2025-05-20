/*
f(x)是x!末尾是0的数量。回想一下x! = 1 * 2 * 3 * ... *x，且0! = 1。
例如， f(3) = 0，因为3! = 6的末尾没有0；
而 f(11) = 2，因为11! = 39916800末端有2个0。
给定k，找出返回能满足f(x) = k的非负整数x的数量。

示例1：
输入：k = 0
输出：5
解释：0!, 1!, 2!, 3!,和4! 均符合k = 0的条件。

示例2：
输入：k = 5
输出：0
解释：没有匹配到这样的x!，符合k = 5的条件。

示例 3:

输入: k = 3
输出: 5


提示:
0 <= k <= 10^9
*/

class Solution {
 public:
  long long f(long long x) {
    long long ans = 0ll;
    for (x /= 5; x != 0; x /= 5) ans += x;
    return ans;
  }

  int preimageSizeFZF(int k) {
    long long l = 4ll * k, r = 5ll * k;
    while (l < r) {
      const long long m = (l + r) / 2;
      if (f(m) < k)
        l = m + 1;
      else
        r = m;
    }
    return f(l) == k ? 5 : 0;
  }
};