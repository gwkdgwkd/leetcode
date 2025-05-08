/*
给一个整数数组nums。
返回数组nums中严格递增或严格递减的最长非空子数组的长度。

示例1：
输入：nums = [1,4,3,3,2]
输出：2
解释：nums中严格递增的子数组有[1]、[2]、[3]、[3]、[4]以及[1,4]。
     nums中严格递减的子数组有[1]、[2]、[3]、[3]、[4]、[3,2]以及[4,3]。
     因此，返回2。

示例2：
输入：nums = [3,3,3,3]
输出：1
解释：nums中严格递增的子数组有[3]、[3]、[3]以及[3]。
     nums中严格递减的子数组有[3]、[3]、[3]以及[3]。
     因此，返回1。

示例3：
输入：nums = [3,2,1]
输出：3
解释：nums中严格递增的子数组有[3]、[2]以及[1]。
     nums中严格递减的子数组有[3]、[2]、[1]、[3,2]、[2,1]以及[3,2,1]。
     因此，返回3。


提示：
1 <= nums.length <= 50
1 <= nums[i] <= 50
*/

class Solution {
 public:
  int longestMonotonicSubarray(vector<int>& nums) {
    int n = nums.size();
    int right = 0;
    int ans = 0;
    while (right < n) {
      int left = right++;
      while (right < n && nums[right - 1] < nums[right]) {
        ++right;
      }
      ans = max(ans, right - left);
    }

    right = 0;
    while (right < n) {
      int left = right++;
      while (right < n && nums[right - 1] > nums[right]) {
        ++right;
      }
      ans = max(ans, right - left);
    }

    return ans;
  }
};

class Solution {
 public:
  int longestMonotonicSubarray(vector<int>& a) {
    int ans = 1;
    int i = 0, n = a.size();
    while (i < n - 1) {
      if (a[i + 1] == a[i]) {
        i++;  // 直接跳过
        continue;
      }
      int i0 = i;                  // 记录这一组的开始位置
      bool inc = a[i + 1] > a[i];  // 定下基调：是严格递增还是严格递减
      i += 2;  // i和i+1已经满足要求，从i+2开始判断
      while (i < n && a[i] != a[i - 1] && (a[i] > a[i - 1]) == inc) {
        i++;
      }
      // 从i0到i-1是满足题目要求的（并且无法再延长的）子数组
      ans = max(ans, i - i0);
      i--;
    }
    return ans;
  }
};
