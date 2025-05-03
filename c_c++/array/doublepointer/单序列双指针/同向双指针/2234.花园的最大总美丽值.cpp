/*
Alice是n个花园的园丁，她想通过种花，最大化她所有花园的总美丽值。
给一个下标从0开始大小为n的整数数组flowers，其中flowers[i]是第i个花园里已经种的花的数目。
已经种了的花不能移走。同时newFlowers表示Alice额外可以种花的最大数目。
同时还有整数target，full和partial。
如果一个花园有至少target朵花，那么这个花园称为完善的，花园的总美丽值为以下分数之和：
完善花园数目乘以full。
剩余不完善花园里，花的最少数目乘以partial。如果没有不完善花园，那么这一部分的值为0。
请返回Alice种最多newFlowers朵花以后，能得到的最大总美丽值。

示例1：
输入：flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
输出：14
解释：Alice可以按以下方案种花
     在第0个花园种2朵花
     在第1个花园种3朵花
     在第2个花园种1朵花
     在第3个花园种1朵花
     花园里花的数目为[3,6,2,2]。总共种了2 + 3 + 1 + 1 = 7朵花。
     只有1个花园是完善的。
     不完善花园里花的最少数目是2。
     所以总美丽值为1 * 12 + 2 * 1 = 12 + 2 = 14。
     没有其他方案可以让花园总美丽值超过14。

示例2：
输入：flowers = [2,4,5,3], newFlowers = 10, target = 5, full = 2, partial = 6
输出：30
解释：Alice可以按以下方案种花
     在第0个花园种3朵花
     在第1个花园种0朵花
     在第2个花园种0朵花
     在第3个花园种2朵花
     花园里花的数目为[5,4,5,5]。总共种了3 + 0 + 0 + 2 = 5朵花。
     有3个花园是完善的。
     不完善花园里花的最少数目为4。
     所以总美丽值为3 * 2 + 4 * 6 = 6 + 24 = 30。
     没有其他方案可以让花园总美丽值超过30。
     注意，Alice可以让所有花园都变成完善的，但这样她的总美丽值反而更小。


提示：
1 <= flowers.length <= 10^5
1 <= flowers[i], target <= 10^5
1 <= newFlowers <= 10^10
1 <= full, partial <= 10^5
*/

// 枚举完善和不完善的分界线
class Solution {
 public:
  long long maximumBeauty(vector<int>& flowers, long long newFlowers,
                          int target, int full, int partial) {
    int n = flowers.size();
    for (int& x : flowers) {
      x = min(x, target);
    }
    sort(flowers.begin(), flowers.end(), greater<int>());
    long long sum = accumulate(flowers.begin(), flowers.end(), 0LL);
    long long ans = 0;
    if (static_cast<long long>(target) * n - sum <= newFlowers) {
      ans = static_cast<long long>(full) * n;
    }

    long long pre = 0;
    int ptr = 0;
    for (int i = 0; i < n; ++i) {
      if (i != 0) {
        pre += flowers[i - 1];
      }
      if (flowers[i] == target) {
        continue;
      }
      long long rest = newFlowers - (static_cast<long long>(target) * i - pre);
      if (rest < 0) {
        break;
      }
      while (
          !(ptr >= i &&
            static_cast<long long>(flowers[ptr]) * (n - ptr) - sum <= rest)) {
        sum -= flowers[ptr];
        ++ptr;
      }
      rest -= static_cast<long long>(flowers[ptr]) * (n - ptr) - sum;
      ans = max(ans, static_cast<long long>(full) * i +
                         static_cast<long long>(partial) *
                             (min(flowers[ptr] + rest / (n - ptr),
                                  static_cast<long long>(target) - 1)));
    }

    return ans;
  }
};

// 贪心+排序+双指针
class Solution {
 public:
  long long maximumBeauty(vector<int>& flowers, long long newFlowers,
                          int target, int full, int partial) {
    int n = flowers.size();
    // 如果全部种满，还剩下多少朵花？
    long long left_flowers = newFlowers - 1LL * target * n;  // 先减掉
    for (int& flower : flowers) {
      flower = min(flower, target);
      left_flowers += flower;  // 把已有的加回来
    }

    // 没有种花，所有花园都已种满
    if (left_flowers == newFlowers) {
      return 1LL * n * full;  // 答案只能是n*full（注意不能减少花的数量）
    }

    // 可以全部种满
    if (left_flowers >= 0) {
      // 两种策略取最大值：留一个花园种target-1朵花，其余种满；或者，全部种满
      return max(1LL * (target - 1) * partial + 1LL * (n - 1) * full,
                 1LL * n * full);
    }
    ranges::sort(flowers);  // 时间复杂度的瓶颈在这，尽量写在后面
    long long ans = 0, pre_sum = 0;
    int j = 0;
    // 枚举i，表示后缀[i, n-1]种满（i=0的情况上面已讨论）
    for (int i = 1; i <= n; i++) {
      // 撤销，flowers[i-1]不变成target
      left_flowers += target - flowers[i - 1];
      if (left_flowers < 0) {  // 花不能为负数，需要继续撤销
        continue;
      }

      // 满足以下条件说明 [0, j] 都可以种 flowers[j] 朵花
      while (j < i && 1LL * flowers[j] * j <= pre_sum + left_flowers) {
        pre_sum += flowers[j];

        j++;
      }

      // 计算总美丽值
      // 在前缀[0, j-1]中均匀种花，这样最小值最大
      long long avg = (left_flowers + pre_sum) /
                      j;  // 由于上面特判了，这里avg一定小于target
      long long total_beauty = avg * partial + 1LL * (n - i) * full;
      ans = max(ans, total_beauty);
    }

    return ans;
  }
};
