/*
给一个整数数组ranks，表示一些机械工的能力值。ranksi是第i位机械工的能力值。
能力值为r的机械工可以在r*n^2分钟内修好n辆车。
同时给你一个整数cars，表示总共需要修理的汽车数目。
请返回修理所有汽车最少需要多少时间。
注意：所有机械工可以同时修理汽车。

示例1：
输入：ranks = [4,2,3,1], cars = 10
输出：16
解释：第一位机械工修2辆车，需要4 * 2 * 2 = 16分钟。
     第二位机械工修2辆车，需要2 * 2 * 2 = 8分钟。
     第三位机械工修2辆车，需要3 * 2 * 2 = 12分钟。
     第四位机械工修4辆车，需要1 * 4 * 4 = 16分钟。
     16分钟是修理完所有车需要的最少时间。

示例2：
输入：ranks = [5,1,8], cars = 6
输出：16
解释：第一位机械工修1辆车，需要5 * 1 * 1 = 5分钟。
     第二位机械工修4辆车，需要1 * 4 * 4 = 16分钟。
     第三位机械工修1辆车，需要8 * 1 * 1 = 8分钟。
     16分钟时修理完所有车需要的最少时间。


提示：
1 <= ranks.length <= 10^5
1 <= ranks[i] <= 100
1 <= cars <= 10^6
*/

/*
如果已知修车的时间t，可以算出每个人在t分钟内能修好多少辆车。
例如一个能力值r=3的人可以在t=16分钟内修好2辆车，但无法修好3辆车。
rn^2≤t
n≤sqrt(r/t)
所以能力值为r的机械工最多可以修​sqrt(r/t)辆车。
​累加每个人在t分钟内能修的车的个数，如果≥cars，则说明可以在t分钟修完所有车。
t越大，能修的车越多，越能满足要求。有了这样的单调性，就可以二分答案了。
*/
class Solution {
 public:
  long long repairCars(vector<int> &ranks, int cars) {
    auto check = [&ranks, &cars](long long mid) {
      long long sum = 0;
      for (int r : ranks) {
        // 开方直接取整的做法是否会有精度误差？
        // 对整数开方，只要整数转浮点没有丢失精度（在2^53−1内），开方出来的整数部分就是正确的。
        sum += sqrt(mid / r);
      }
      return sum >= cars;
    };
    long long left = 1;
    // 二分上界，让能力值最低（修车最快）的人修好所有车所需要的时间：
    int min_r = *min_element(ranks.begin(), ranks.end());
    long long right = 1LL * min_r * cars * cars;
    while (left <= right) {
      long long mid = (left + right) / 2, s = 0;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

class Solution {
 public:
  long long repairCars(vector<int> &ranks, int cars) {
    int min_r = *min_element(ranks.begin(), ranks.end());
    long long left = 0, right = 1LL * min_r * cars * cars;
    while (left + 1 < right) {  // 开区间
      long long mid = (left + right) / 2, s = 0;
      for (int r : ranks) s += sqrt(mid / r);
      (s >= cars ? right : left) = mid;
    }
    return right;
  }
};

/*
优化
能力值相同的人，在t分钟内修好的车的个数是一样的。
根据数据范围，ranks中至多有100个不同的数字，
我们可以统计ranks中每个数字的出现次数，这样每次二分至多循环100次。
此外，如果循环中发现s≥cars，可以提前退出循环。
*/
class Solution {
 public:
  long long repairCars(vector<int> &ranks, int cars) {
    int min_r = ranks[0], cnt[101]{};  // 数组比哈希表更快
    for (int r : ranks) {
      min_r = min(min_r, r);
      cnt[r]++;
    }
    long long left = 0, right = 1LL * min_r * cars * cars;
    while (left + 1 < right) {
      long long mid = (left + right) / 2, s = 0;
      for (int r = min_r; r <= 100 && s < cars; r++)  // 至多循环100次
        s += (long long)sqrt(mid / r) * cnt[r];
      (s >= cars ? right : left) = mid;
    }
    return right;
  }
};