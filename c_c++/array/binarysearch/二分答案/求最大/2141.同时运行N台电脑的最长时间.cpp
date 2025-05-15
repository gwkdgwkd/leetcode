/*
有n台电脑。给整数n和一个下标从0开始的整数数组batteries，
其中第i个电池可以让一台电脑运行batteries[i]分钟。
想使用这些电池让全部n台电脑同时运行。
一开始，可以给每台电脑连接至多一个电池。然后在任意整数时刻，
都可以将一台电脑与它的电池断开连接，并连接另一个电池，可以进行这个操作任意次。
新连接的电池可以是一个全新的电池，也可以是别的电脑用过的电池。
断开连接和连接新的电池不会花费任何时间。
注意，不能给电池充电。
请返回可以让n台电脑同时运行的最长分钟数。

示例1：
输入：n = 2, batteries = [3,3,3]
输出：4
解释：一开始，将第一台电脑与电池0连接，第二台电脑与电池1连接。
     2分钟后，将第二台电脑与电池1断开连接，并连接电池2。注意，电池0还可以供电1分钟。
     在第3分钟结尾，需要将第一台电脑与电池0断开连接，然后连接电池1。
     在第4分钟结尾，电池1也被耗尽，第一台电脑无法继续运行。
     我们最多能同时让两台电脑同时运行4分钟，所以我们返回4。

示例2：
输入：n = 2, batteries = [1,1,1,1]
输出：2
解释：一开始，将第一台电脑与电池0连接，第二台电脑与电池2连接。
     一分钟后，电池0和电池2同时耗尽，所以需要将它们断开连接，
     并将电池1和第一台电脑连接，电池3和第二台电脑连接。
     1分钟后，电池1和电池3也耗尽了，所以两台电脑都无法继续运行。
     我们最多能让两台电脑同时运行2分钟，所以我们返回2。


提示：
1 <= n <= batteries.length <= 10^5
1 <= batteries[i] <= 10^9
*/

// 二分答案
class Solution {
 public:
  long long maxRunTime(int n, vector<int>& batteries) {
    auto check = [&](long long m) {
      // 假设可以让n台电脑同时运行m分钟，那么对于电量大于m的电池，其只能被使用m分钟。
      // 因此每个电池的使用时间至多为min(batteries[i],m)，将其累加起来，记作sum。
      // 那么要让n台电脑同时运行m分钟，必要条件是 n*m≤sum。
      long long sum = 0;
      for (int b : batteries) {
        sum += min((long long)b, m);
      }
      return sum >= m * n;
    };
    long long left = 1;
    long long right =
        accumulate(batteries.begin(), batteries.end(), 0L) / n + 1;
    while (left <= right) {
      long long mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};

class Solution {
 public:
  long long maxRunTime(int n, vector<int>& batteries) {
    long long tot = reduce(batteries.begin(), batteries.end(), 0L);
    long long l = 0, r = tot / n + 1;  // 开区间一定要+1
    while (l + 1 < r) {
      long long x = l + (r - l) / 2;
      long long sum = 0;
      for (long long b : batteries) {
        sum += min(b, x);
      }
      (n * x <= sum ? l : r) = x;
    }

    return l;
  }
};

// 排序 + 贪心
class Solution {
 public:
  long long maxRunTime(int n, vector<int>& batteries) {
    ranges::sort(batteries, greater());
    long long sum = reduce(batteries.begin(), batteries.end(), 0L);

    for (int i = 0;; i++) {
      // 记电池电量和为sum，则理论上至多可以供电x=sum/n分钟
      if (batteries[i] <= sum / n) {
        // 若该电池电量不超过x，则其余电池的电量均不超过x，可以供电x分钟
        return sum / n;
      } else {
        // 若该电池电量超过x，则将其供给一台电脑，问题缩减为n−1台电脑的子问题
        sum -= batteries[i];
        n--;
      }
    }
  }
};
