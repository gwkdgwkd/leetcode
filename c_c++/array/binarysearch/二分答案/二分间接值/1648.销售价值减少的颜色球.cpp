/*
有一些球的库存inventory，里面包含着不同颜色的球。一个顾客想要任意颜色总数为orders的球。
这位顾客有一种特殊的方式衡量球的价值：每个球的价值是目前剩下的同色球的数目。
比方说还剩下6个黄球，那么顾客买第一个黄球的时候该黄球的价值为6。
这笔交易以后，只剩下5个黄球了，所以下一个黄球的价值为5，
也就是球的价值随着顾客购买同色球是递减的。
给整数数组inventory，其中inventory[i]表示第i种颜色球一开始的数目。
同时给整数orders，表示顾客总共想买的球数目。可以按照任意顺序卖球。
请返回卖了orders个球以后最大总价值之和。由于答案可能会很大，请返回答案对10^9+7取余数的结果。

示例1：
输入：inventory = [2,5], orders = 4
输出：14
解释：卖1个第一种颜色的球（价值为2)，卖3个第二种颜色的球（价值为5 + 4 + 3）。
     最大总和为2 + 5 + 4 + 3 = 14。

示例2：
输入：inventory = [3,5], orders = 6
输出：19
解释：卖2个第一种颜色的球（价值为3 + 2），卖4个第二种颜色的球（价值为5 + 4 + 3 +
2）。 最大总和为3 + 2 + 5 + 4 + 3 + 2 = 19。

示例3：
输入：inventory = [2,8,4,10,6], orders = 20
输出：110

示例4：
输入：inventory = [1000000000], orders = 1000000000
输出：21
解释：卖1000000000次第一种颜色的球，总价值为500000000500000000。
     500000000500000000对10^9 + 7取余为21。


提示：
1 <= inventory.length <= 10^5
1 <= inventory[i] <= 10^9
1 <= orders <= min(sum(inventory[i]), 10^9)
*/

class Solution {
 public:
  int maxProfit(vector<int>& inventory, int orders) {
    int mod = (int)1e9 + 7;
    int l = 0;
    int r = *max_element(inventory.begin(), inventory.end());
    auto check = [&](int k) -> bool {
      long long sum = 0;
      for (int x : inventory) {
        if (x > k) {
          sum += x - k;
        }
      }
      return sum > orders;
    };
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (check(mid)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    int k = l;
    long long ans = 0;
    long long sum = 0;
    auto range_sum = [&](int x, int y) -> long long {
      return (long long)(x + y) * (y - x + 1) / 2;
    };
    for (int x : inventory) {
      if (x > k) {
        ans += range_sum(k + 1, x);
        sum += x - k;
      }
    }
    ans += (orders - sum) * k;
    return ans % mod;
  }
};