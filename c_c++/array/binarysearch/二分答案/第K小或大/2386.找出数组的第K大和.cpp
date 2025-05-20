/*
给一个整数数组nums和一个正整数k。可以选择数组的任一子序列并且对其全部元素求和。
数组的第k大和定义为：可以获得的第k个最大子序列和（子序列和允许出现重复）返回数组的第k大和。
子序列是一个可以由其他数组删除某些或不删除元素派生而来的数组，且派生过程不改变剩余元素的顺序。
注意：空子序列的和视作0。

示例1：
输入：nums = [2,4,-2], k = 5
输出：2
解释：所有可能获得的子序列和列出如下，按递减顺序排列：
     6、4、4、2、2、0、0、-2
     数组的第5大和是2。

示例2：
输入：nums = [1,-2,3,4,-10,12], k = 16
输出：10
解释：数组的第16大和是10。


提示：
n == nums.length
1 <= n <= 10^5
-10^9 <= nums[i] <= 10^9
1 <= k <= min(2000, 2n)
*/

class Solution {
 public:
  long long kSum(vector<int> &nums, int k) {
    long sum = 0;
    for (int &x : nums) {
      if (x >= 0) {
        sum += x;

      } else {
        x = -x;
      }
    }
    ranges::sort(nums);
    auto check = [&](long sum_limit) -> bool {
      int cnt = 1;  // 空子序列算一个
      function<void(int, long long)> dfs = [&](int i, long long s) {
        if (cnt == k || i == nums.size() || s + nums[i] > sum_limit) {
          return;
        }
        cnt++;                    // s + nums[i] <= sum_limit
        dfs(i + 1, s + nums[i]);  // 选
        dfs(i + 1, s);            // 不选
      };

      dfs(0, 0);
      return cnt == k;  // 找到k个元素和不超过sum_limit的子序列
    };

    long long left = -1, right = accumulate(nums.begin(), nums.end(), 0LL);
    while (left + 1 < right) {  // 开区间二分，原理见【前置知识】
      long long mid = (left + right) / 2;
      (check(mid) ? right : left) = mid;
    }

    return sum - right;
  }
};
