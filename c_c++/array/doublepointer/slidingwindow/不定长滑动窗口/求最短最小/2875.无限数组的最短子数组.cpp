/*
给一个下标从0开始的数组nums和一个整数target。
下标从0开始的数组infinite_nums是通过无限地将nums的元素追加到自己之后生成的。
请从infinite_nums中找出满足元素和等于target的最短子数组，
并返回该子数组的长度。如果不存在满足条件的子数组，返回-1。

示例1：
输入：nums = [1,2,3], target = 5
输出：2
解释：在这个例子中infinite_nums = [1,2,3,1,2,3,1,2,...]。
     区间[1,2]内的子数组的元素和等于target = 5，且长度length = 2。
     可以证明，当元素和等于目标值target = 5时，2是子数组的最短长度。

示例2：
输入：nums = [1,1,1,2,3], target = 4
输出：2
解释：在这个例子中infinite_nums = [1,1,1,2,3,1,1,1,2,3,1,1,...]。
     区间[4,5]内的子数组的元素和等于target = 4，且长度length = 2。
     可以证明，当元素和等于目标值target = 4时，2是子数组的最短长度。

示例3：
输入：nums = [2,4,6,8], target = 3
输出：-1
解释：在这个例子中infinite_nums = [2,4,6,8,2,4,6,8,...]。
     可以证明，不存在元素和等于目标值target = 3的子数组。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= target <= 10^9
*/

/*
分析
*/
class Solution {
 public:
  int minSizeSubarray(vector<int>& nums, int target) {
    long long total =
        accumulate(nums.begin(), nums.end(), 0LL);  // 直接写0会报错
    long long t = target % total;
    int n = nums.size();
    int ans = INT_MAX;
    long long sum = 0;
    int right = 0;
    int left = 0;
    while (right < n * 2) {
      sum += nums[right % n];
      ++right;

      while (sum > t) {
        sum -= nums[left % n];
        ++left;
      }
      if (sum == t) {
        ans = min(ans, right - left);
      }
    }
    return ans == INT_MAX ? -1 : ans + target / total * n;
  }
};