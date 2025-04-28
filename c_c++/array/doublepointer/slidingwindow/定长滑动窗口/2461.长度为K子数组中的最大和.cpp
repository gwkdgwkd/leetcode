/*
给一个整数数组nums和一个整数k。
请从nums中满足下述条件的全部子数组中找出最大子数组和：
子数组的长度是k，且子数组中的所有元素各不相同。
返回满足题面要求的最大子数组和，如果不存在子数组满足这些条件，返回0。
子数组是数组中一段连续非空的元素序列。

示例1：
输入：nums = [1,5,4,2,9,9,9], k = 3
输出：15
解释：nums中长度为3的子数组是：
     [1,5,4]满足全部条件，和为10。
     [5,4,2]满足全部条件，和为11。
     [4,2,9]满足全部条件，和为15。
     [2,9,9]不满足全部条件，因为元素9出现重复。
     [9,9,9]不满足全部条件，因为元素9出现重复。
     因为15是满足全部条件的所有子数组中的最大子数组和，所以返回15。

示例2：
输入：nums = [4,4,4], k = 3
输出：0
解释：nums中长度为3的子数组是：
     [4,4,4]不满足全部条件，因为元素4出现重复。
     因为不存在满足全部条件的子数组，所以返回0。


提示：
1 <= k <= nums.length <= 10^5
1 <= nums[i] <= 10^5
*/

// 同[2841.几乎唯一子数组的最大和]，把≥m改成=k即可。
class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(k)，哈希表的大小不会超过窗口长度k。
 public:
  long long maximumSubarraySum(vector<int>& nums, int k) {
    long long sum = 0, ans = 0;
    unordered_map<int, int> cnt;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      sum += nums[i];
      cnt[nums[i]]++;
      if (i < k - 1) {
        continue;
      }
      if (cnt.size() == k) {
        ans = max(ans, sum);
      }
      int left = i - k + 1;
      sum -= nums[left];
      if (--cnt[nums[left]] == 0) {
        cnt.erase(nums[left]);
      }
    }

    return ans;
  }
};