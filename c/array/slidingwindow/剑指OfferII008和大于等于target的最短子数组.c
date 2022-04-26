/*
找出该数组中满足其和≥ target的长度最小的连续子数组[numsl,numsl+1,...,numsr-1,numsr]，并返回其长度。
如果不存在符合条件的子数组，返回0。

示例1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组[4,3]是该条件下的长度最小的子数组。

示例2：
输入：target = 4, nums = [1,4,4]
输出：1

示例3：
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0

提示：
1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5

进阶：
如果你已经实现O(n)时间复杂度的解法, 请尝试设计一个O(nlog(n))时间复杂度的解法。

注意：本题与209题相同
*/

int minSubArrayLen(int target, int* nums, int numsSize) {
  int res = INT_MAX;
  int left = 0;
  int right = 0;
  int sum = 0;
  while (right < numsSize) {
    sum += nums[right++];
    while (sum >= target) {
      res = fmin(res, right - left);
      sum -= nums[left++];
    }
  }

  return res == INT_MAX ? 0 : res;
}