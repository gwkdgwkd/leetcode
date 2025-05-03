/*
给一个下标从0开始长度为n的整数数组nums和一个整数target，
请返回满足0 <= i < j < n且nums[i] + nums[j] < target的下标对(i, j)的数目。

示例1：
输入：nums = [-1,1,2,3,1], target = 2
输出：3
解释：总共有3个下标对满足题目描述：
     (0, 1)，0 < 1且nums[0] + nums[1] = 0 < target
     (0, 2)，0 < 2且nums[0] + nums[2] = 1 < target
     (0, 4)，0 < 4且nums[0] + nums[4] = 0 < target
     注意(0, 3)不计入答案因为nums[0] + nums[3]不是严格小于target。

示例2：
输入：nums = [-6,2,5,-2,-7,-1,3], target = -2
输出：10
解释：总共有10个下标对满足题目描述：
     (0, 1)，0 < 1且nums[0] + nums[1] = -4 < target
     (0, 3)，0 < 3且nums[0] + nums[3] = -8 < target
     (0, 4)，0 < 4且nums[0] + nums[4] = -13 < target
     (0, 5)，0 < 5且nums[0] + nums[5] = -7 < target
     (0, 6)，0 < 6且nums[0] + nums[6] = -3 < target
     (1, 4)，1 < 4且nums[1] + nums[4] = -5 < target
     (3, 4)，3 < 4且nums[3] + nums[4] = -9 < target
     (3, 5)，3 < 5且nums[3] + nums[5] = -3 < target
     (4, 5)，4 < 5且nums[4] + nums[5] = -8 < target
     (4, 6)，4 < 6且nums[4] + nums[6] = -4 < target


提示：
1 <= nums.length == n <= 50
-50 <= nums[i], target <= 50
*/

class Solution {
 public:
  int countPairs(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int ans = 0;
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      if (nums[left] + nums[right] < target) {
        // nums[left]与下标i在区间[left+1,right]中的任何nums[i]相加，
        // 都是<target的，因此直接找到了right−left个合法数对
        ans += right - left;  // right - (left + 1) + 1
        ++left;
      } else {
        // nums[right]与下标i在区间[left,right−1]中的任何nums[i]相加，
        // 都是≥target的
        --right;
      }
    }
    return ans;
  }
};