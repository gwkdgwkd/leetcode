/*
沿街有一排连续的房屋。每间房屋内都藏有一定的现金。现在有一位小偷计划从这些房屋中窃取现金。
由于相邻的房屋装有相互连通的防盗系统，所以小偷不会窃取相邻的房屋。
小偷的窃取能力定义为他在窃取过程中能从单间房屋中窃取的最大金额。
给你一个整数数组nums表示每间房屋存放的现金金额。形式上，从左起第i间房屋中放有nums[i]美元。
另给一个整数k，表示窃贼将会窃取的最少房屋数。小偷总能窃取至少k间房屋。
返回小偷的最小窃取能力。

示例1：
输入：nums = [2,3,5,9], k = 2
输出：5
解释：小偷窃取至少2间房屋，共有3种方式：
     窃取下标0和2处的房屋，窃取能力为max(nums[0], nums[2]) = 5。
     窃取下标0和3处的房屋，窃取能力为max(nums[0], nums[3]) = 9。
     窃取下标1和3处的房屋，窃取能力为max(nums[1], nums[3]) = 9。
     因此，返回min(5, 9, 9) = 5。

示例2：
输入：nums = [2,7,9,3,1], k = 2
输出：2
解释：共有7种窃取方式。窃取能力最小的情况所对应的方式是窃取下标0和4处的房屋。
     返回max(nums[0], nums[4]) = 2。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= (nums.length + 1)/2
*/

// 二分 + 贪心
class Solution {
 public:
  int minCapability(vector<int> &nums, int k) {
    int n = nums.size();
    auto check = [&](int m) {
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        if (nums[i] <= m) {
          ++cnt;
          ++i;
        }
      }
      return cnt >= k;
    };
    int left = nums[0];
    int right = nums[0];
    for (int i = 1; i < n; ++i) {
      left = min(left, nums[i]);
      right = max(right, nums[i]);
    }

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

// 二分 + DP
class Solution {
  bool check(vector<int> &nums, int k, int mx) {
    int f0 = 0, f1 = 0;
    for (int x : nums) {
      if (x > mx) {
        f0 = f1;

      } else {
        int tmp = f1;

        f1 = max(f1, f0 + 1);

        f0 = tmp;
      }
    }

    return f1 >= k;
  }

 public:
  int minCapability(vector<int> &nums, int k) {
    int left = 0, right = *max_element(nums.begin(), nums.end());
    while (left + 1 < right) {  // 开区间写法
      int mid = left + (right - left) / 2;
      (check(nums, k, mid) ? right : left) = mid;
    }

    return right;
  }
};