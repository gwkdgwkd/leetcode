/*
有一个书店老板，他的书店开了n分钟。每分钟都有一些顾客进入这家商店。
给定一个长度为n的整数数组customers，其中customers[i]是在第i分钟开始时进入商店的顾客数量，
所有这些顾客在第i分钟结束后离开。
在某些分钟内，书店老板会生气。
如果书店老板在第i分钟生气，那么grumpy[i] = 1，否则grumpy[i] = 0。
当书店老板生气时，那一分钟的顾客就会不满意，若老板不生气则顾客是满意的。
书店老板知道一个秘密技巧，能抑制自己的情绪，
可以让自己连续minutes分钟不生气，但却只能使用一次。
请返回这一天营业下来，最多有多少客户能够感到满意。

示例1：
输入：customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
输出：16
解释：书店老板在最后3分钟保持冷静。
     感到满意的最大客户数量=1 + 1 + 1 + 1 + 7 + 5 = 16

示例2：
输入：customers = [1], grumpy = [0], minutes = 1
输出：1


提示：
n == customers.length == grumpy.length
1 <= minutes <= n <= 2 * 10^4
0 <= customers[i] <= 1000
grumpy[i] == 0 or 1
*/

class Solution {
  // 时间复杂度：O(n)，其中n为customers的长度。
  // 空间复杂度：O(1)。
 public:
  int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
    int n = customers.size();
    int sum = 0;
    int tmp = 0;
    int index = 0;
    for (int i = 0; i < n; ++i) {
      if (grumpy[i]) {
        sum += customers[i];
      }

      if (i < minutes - 1) {
        continue;
      }
      int left = i - minutes + 1;
      if (sum > tmp) {
        tmp = sum;
        index = left;
      }

      if (grumpy[left]) {
        sum -= customers[left];
      }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (grumpy[i] == 0 || (grumpy[i] && i >= index && i < index + minutes)) {
        ans += customers[i];
      }
    }

    return ans;
  }
};