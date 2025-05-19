/*
给一个下标从0开始长度为n的整数数组stations，其中stations[i]表示第i座城市的供电站数目。
每个供电站可以在一定范围内给所有城市提供电力。
换句话说，如果给定的范围是r，在城市i处的供电站可以给所有满足：
|i - j| <= r且0 <= i, j <= n - 1的城市j供电。
|x|表示x的绝对值。比方说，|7 - 5| = 2 ，|3 - 10| = 7。
一座城市的电量是所有能给它供电的供电站数目。
政府批准了可以额外建造k座供电站，需要决定这些供电站分别应该建在哪里，
这些供电站与已经存在的供电站有相同的供电范围。
给你两个整数r和k，如果以最优策略建造额外的发电站，返回所有城市中，最小电量的最大值是多少。
这k座供电站可以建在多个城市。

示例 1：
输入：stations = [1,2,4,5,0], r = 1, k = 2
输出：5
解释：最优方案之一是把2座供电站都建在城市1。
     每座城市的供电站数目分别为[1,4,4,5,0]。
     城市0的供电站数目为1 + 4 = 5。
     城市1的供电站数目为1 + 4 + 4 = 9。
     城市2的供电站数目为4 + 4 + 5 = 13。
     城市3的供电站数目为5 + 4 = 9。
     城市4的供电站数目为5 + 0 = 5。
     供电站数目最少是5。
     无法得到更优解，所以我们返回5。

示例2：
输入：stations = [4,4,4,4], r = 0, k = 3
输出：4
解释：无论如何安排，总有一座城市的供电站数目是4，所以最优解是4。


提示：
n == stations.length
1 <= n <= 10^5
0 <= stations[i] <= 10^5
0 <= r <= n - 1
0 <= k <= 10^9
*/

class Solution {
 public:
  long long maxPower(vector<int>& stations, int r, int k) {
    int n = stations.size();
    vector<long long> sum(n + 1), power(n), diff(n);

    for (int i = 0; i < n; i++) {
      sum[i + 1] = sum[i] + stations[i];  // 前缀和
    }

    for (int i = 0; i < n; i++) {
      power[i] = sum[min(i + r + 1, n)] - sum[max(i - r, 0)];  // 电量
    }

    auto check = [&](long long min_power) -> bool {
      ranges::fill(diff, 0);  // 重置差分数组
      long long sum_d = 0, need = 0;
      for (int i = 0; i < n; ++i) {
        sum_d += diff[i];  // 累加差分值
        long long m = min_power - power[i] - sum_d;
        if (m > 0) {  // 需要m个供电站
          need += m;
          if (need > k) {
            return false;  // 提前退出这样快一些
          }

          sum_d += m;  // 差分更新
          if (i + r * 2 + 1 < n) {
            diff[i + r * 2 + 1] -= m;  // 差分更新
          }
        }
      }

      return true;
    };

    long long left = ranges::min(power);
    long long right = left + k + 1;  // 开区间写法
    while (left + 1 < right) {
      long long mid = left + (right - left) / 2;
      (check(mid) ? left : right) = mid;
    }

    return left;
  }
};
