/*
给一个长度为n的整数数组nums和一个目标值target。
请从nums中选出三个整数，使它们的和与target最接近，返回这三个数的和。
假定每组输入只存在恰好一个解。

示例1：
输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与target最接近的和是2(-1 + 2 + 1 = 2)。

示例2：
输入：nums = [0,0,0], target = 1
输出：0
解释：与target最接近的和是0（0 + 0 + 0 = 0）。


提示：
3 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
-10^4 <= target <= 10^4
*/

class Solution {
 public:
  int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int ans = 0;
    int n = nums.size();
    int diff = INT_MAX;

    for (int i = 0; i < n - 2; ++i) {
      int x = nums[i];
      if (i > 0 && x == nums[i - 1]) {
        continue;
      }

      int s = x + nums[i + 1] + nums[i + 2];
      if (s > target) {
        if (s - target < diff) {
          ans = s;
        }
        break;
      }

      s = x + nums[n - 2] + nums[n - 1];
      if (s < target) {
        if (target - s < diff) {
          diff = target - s;
          ans = s;
        }
        continue;
      }

      int left = i + 1;
      int right = n - 1;
      while (left < right) {
        s = x + nums[left] + nums[right];
        if (s > target) {
          if (s - target < diff) {
            diff = s - target;
            ans = s;
          }
          --right;
        } else if (s < target) {
          if (target - s < diff) {
            diff = target - s;
            ans = s;
          }
          ++left;
        } else {
          return target;
        }
      }
    }
    return ans;
  }
};