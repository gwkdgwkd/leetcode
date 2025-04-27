/*
给一个整数数组nums和两个正整数m和k 。
请返回nums中长度为k的几乎唯一子数组的最大和，如果不存在几乎唯一子数组，请返回0。
如果nums的一个子数组有至少m个互不相同的元素，称它是几乎唯一子数组。
子数组指的是一个数组中一段连续非空的元素序列。

示例1：
输入：nums = [2,6,7,3,1,7], m = 3, k = 4
输出：18
解释：总共有3个长度为k = 4的几乎唯一子数组。
     分别为[2, 6, 7, 3]，[6, 7, 3, 1]和[7, 3, 1, 7]。
     这些子数组中，和最大的是[2, 6, 7, 3]，和为18。

示例2：
输入：nums = [5,9,9,2,4,5,4], m = 1, k = 3
输出：23
解释：总共有5个长度为k = 3的几乎唯一子数组。
     分别为[5, 9, 9]，[9, 9, 2]，[9, 2, 4]，[2, 4, 5]和[4, 5, 4]。
     这些子数组中，和最大的是[5, 9, 9]，和为23。

示例3：
输入：nums = [1,2,1,2,1,2,1], m = 3, k = 3
输出：0
解释：输入数组中不存在长度为k = 3的子数组含有至少m = 3个互不相同元素的子数组。
     所以不存在几乎唯一子数组，最大和为0。


提示：
1 <= nums.length <= 2 * 10^4
1 <= m <= k <= nums.length
1 <= nums[i] <= 10^9
*/

class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(k)，哈希表的大小不会超过窗口长度k。
 public:
  long long maxSum(vector<int>& nums, int m, int k) {
    long long ans = 0;
    long long sum = 0;
    int n = nums.size();
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
      sum += nums[i];
      cnt[nums[i]]++;
      if (i < k - 1) {
        continue;
      }
      if (cnt.size() >= m) {
        ans = max(ans, sum);
      }
      sum -= nums[i + 1 - k];
      if (--cnt[nums[i + 1 - k]] == 0) {
        cnt.erase(nums[i + 1 - k]);
      }
    }

    return ans;
  }
};