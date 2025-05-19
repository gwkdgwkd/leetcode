/*
为了提高自己的代码能力，小张制定了LeetCode刷题计划，
他选中了LeetCode题库中的n道题，编号从0到n-1，
并计划在m天内按照题目编号顺序刷完所有的题目（注意，小张不能用多天完成同一题）。
在小张刷题计划中，小张需要用time[i]的时间完成编号i的题目。
此外，小张还可以使用场外求助功能，通过询问他的好朋友小杨题目的解法，可以省去该题的做题时间。
为了防止小张刷题计划变成小杨刷题计划，小张每天最多使用一次求助。
我们定义m天中做题时间最多的一天耗时为T（小杨完成的题目不计入做题总时间）。
请帮小张求出最小的T是多少。

示例1：
输入：time = [1,2,3,3], m = 2
输出：3
解释：第一天小张完成前三题，其中第三题找小杨帮忙；
     第二天完成第四题，并且找小杨帮忙。
     这样做题时间最多的一天花费了3的时间，并且这个值是最小的。

示例2：
输入：time = [999,999,999], m = 4
输出：0
解释：在前三天中，小张每天求助小杨一次，这样他可以在三天内完成所有的题目并不花任何时间。


限制：
1 <= time.length <= 10^5
1 <= time[i] <= 10000
1 <= m <= 1000
*/

class Solution {
 public:
  int minTime(vector<int>& time, int m) {
    int n = time.size();
    auto check = [&](int t) {
      int cnt = 0;
      int sum = 0;
      int tmp = 0;
      for (int i = 0; i < n; ++i) {
        sum += time[i];
        tmp = max(tmp, time[i]);
        if (sum - tmp > t) {
          sum = 0;
          tmp = 0;
          ++cnt;
          --i;
        }
      }
      ++cnt;
      return cnt <= m;
    };

    int left = 0;
    int right = accumulate(time.begin(), time.end(), 0);
    while (left <= right) {
      int mid = left + (right - left) / 2;
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
  bool Check(int limit, vector<int> cost, int day) {
    // 每组划分limit的最大和，贪心划分看有多少组
    int useday, totaltime, maxtime;
    useday = 1;
    totaltime = maxtime = 0;
    for (int i = 0; i < cost.size(); ++i) {
      int nexttime = min(maxtime, cost[i]);
      if (nexttime + totaltime <= limit) {
        totaltime += nexttime;
        maxtime = max(maxtime, cost[i]);
      } else {
        ++useday;
        totaltime = 0;
        maxtime = cost[i];
      }
    }
    return (useday <= day);
  }
  int minTime(vector<int>& time, int m) {
    int left, right, middle;
    left = right = 0;
    for (int i = 0; i < time.size(); ++i) {
      right += time[i];
    }
    while (left <= right) {
      middle = (left + right) >> 1;
      if (Check(middle, time, m))
        right = middle - 1;
      else
        left = middle + 1;
    }
    return left;
  }
};