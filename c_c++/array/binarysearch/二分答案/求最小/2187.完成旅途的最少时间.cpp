/*
给一个数组time，其中time[i]表示第i辆公交车完成一趟旅途所需要花费的时间。
每辆公交车可以连续完成多趟旅途，也就是说，
一辆公交车当前旅途完成后，可以立马开始下一趟旅途。
每辆公交车独立运行，也就是说可以同时有多辆公交车在运行且互不影响。
给一个整数totalTrips，表示所有公交车总共需要完成的旅途数目。
请返回完成至少totalTrips趟旅途需要花费的最少时间。

示例1：
输入：time = [1,2,3], totalTrips = 5
输出：3
解释：时刻t = 1，每辆公交车完成的旅途数分别为[1,0,0]。
     已完成的总旅途数为1 + 0 + 0 = 1。
     时刻t = 2，每辆公交车完成的旅途数分别为[2,1,0]。
     已完成的总旅途数为2 + 1 + 0 = 3。
     时刻t = 3，每辆公交车完成的旅途数分别为[3,1,1]。
     已完成的总旅途数为3 + 1 + 1 = 5。
     所以总共完成至少5趟旅途的最少时间为3。

示例2：
输入：time = [2], totalTrips = 1
输出：2
解释：只有一辆公交车，它将在时刻t = 2完成第一趟旅途。
     所以完成1趟旅途的最少时间为2。


提示：
1 <= time.length <= 10^5
1 <= time[i], totalTrips <= 10^7
*/

// 闭区间写法
class Solution {
 public:
  long long minimumTime(vector<int>& time, int totalTrips) {
    auto check = [&time, &totalTrips](long long total) {
      long long cnt = 0;
      for (int t : time) {
        cnt += total / t;
      }
      return cnt >= totalTrips;
    };

    long long left = 1;
    long long right =
        (long long)totalTrips * *max_element(time.begin(), time.end());
    while (left <= right) {
      long long mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

// 开闭区间写法
class Solution {
 public:
  long long minimumTime(vector<int>& time, int totalTrips) {
    auto check = [&](long long t) -> bool {
      long long cnt = 0;
      for (int period : time) {
        cnt += t / period;
      }
      return cnt >= totalTrips;
    };

    long long l = 1;
    long long r =
        (long long)totalTrips * *max_element(time.begin(), time.end());
    while (l < r) {
      long long mid = l + (r - l) / 2;
      if (check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }
};

// 开区间写法
class Solution {
 public:
  long long minimumTime(vector<int>& time, int totalTrips) {
    auto check = [&](long long x) -> bool {
      long long sum = 0;
      for (int t : time) {
        sum += x / t;
        if (sum >= totalTrips) {
          return true;
        }
      }

      return false;
    };

    int min_t = ranges::min(time);
    // 循环不变量：check(left)恒为false
    long long left = min_t - 1;
    // 循环不变量：check(right)恒为true
    long long right = 1LL * min_t * totalTrips;
    while (left + 1 < right) {  // 开区间(left, right)不为空
      long long mid = left + (right - left) / 2;
      (check(mid) ? right : left) = mid;
    }

    // 此时left等于right-1
    // check(left) = false且check(right) = true，所以答案是right
    return right;  // 最小的true
  }
};