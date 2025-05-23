/*
给一个下标从0开始的整数数组nums。
如果i < j且j - i != nums[j] - nums[i]，那么我们称(i, j)是一个坏数对。
请返回nums中坏数对的总数目。

示例1：
输入：nums = [4,1,3,3]
输出：5
解释：数对(0, 1)是坏数对，因为1 - 0 != 1 - 4。
     数对(0, 2)是坏数对，因为2 - 0 != 3 - 4, 2 != -1。
     数对(0, 3)是坏数对，因为3 - 0 != 3 - 4, 3 != -1。
     数对(1, 2)是坏数对，因为2 - 1 != 3 - 1, 1 != 2。
     数对(2, 3)是坏数对，因为3 - 2 != 3 - 3, 1 != 0。
     总共有5个坏数对，所以我们返回5。

示例2：
输入：nums = [1,2,3,4,5]
输出：0
解释：没有坏数对。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
*/

class Solution {
 public:
  long long countBadPairs(vector<int>& nums) {
    long long count = 0;
    int n = nums.size();
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
      // j−i=nums[j]−nums[i]等价于nums[i]-i==nums[j]-j
      count += cnt[nums[i] - i]++;
    }

    // n个数，一共有n*(n-1)/2对
    return (long long)n * (n - 1) / 2 - count;
  }
};