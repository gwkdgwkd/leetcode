/*
给一个整数数组coins表示不同面额的硬币，另给你一个整数k。
有无限量的每种面额的硬币。但是，你不能组合使用不同面额的硬币。
返回使用这些硬币能制造的第kth小金额。

示例1：
输入：coins = [3,6,9], k = 3
输出：9
解释：给定的硬币可以制造以下金额：
     3元硬币产生3的倍数：3, 6, 9, 12, 15等。
     6元硬币产生6的倍数：6, 12, 18, 24等。
     9元硬币产生9的倍数：9, 18, 27, 36等。
     所有硬币合起来可以产生：3, 6, 9, 12, 15等。

示例2：
输入：coins = [5,2], k = 7
输出：12
解释：给定的硬币可以制造以下金额：
     5元硬币产生5的倍数：5, 10, 15, 20等。
     2元硬币产生2的倍数：2, 4, 6, 8, 10, 12等。
     所有硬币合起来可以产生：2, 4, 5, 6, 8, 10, 12, 14, 15等。


提示：
1 <= coins.length <= 15
1 <= coins[i] <= 25
1 <= k <= 2 * 10^9
coins包含两两不同的整数。
*/

class Solution {
 public:
  long long findKthSmallest(vector<int>& coins, int k) {
    auto check = [&](long long m) -> bool {
      long long cnt = 0;
      for (int i = 1; i < (1 << coins.size()); i++) {  // 枚举所有非空子集
        long long lcm_res = 1;                         // 计算子集LCM
        for (int j = 0; j < coins.size(); j++) {
          if (i >> j & 1) {
            lcm_res = lcm(lcm_res, coins[j]);
            if (lcm_res > m) {  // 太大了
              break;
            }
          }
        }
        cnt += __builtin_popcount(i) % 2 ? m / lcm_res : -m / lcm_res;
      }
      return cnt >= k;
    };

    long long left = k - 1, right = (long long)ranges::min(coins) * k;
    while (left + 1 < right) {
      long long mid = (left + right) / 2;
      (check(mid) ? right : left) = mid;
    }
    return right;
  }
};