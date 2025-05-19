/*
给一个下标从0开始的整数数组nums和一个整数p。
请从nums中找到p个下标对，每个下标对对应数值取差值，需要使得这p个差值的最大值最小。
同时，需要确保每个下标在这p个下标对中最多出现一次。
对于一个下标对i和j，这一对的差值为|nums[i]-nums[j]|，其中|x|表示x的绝对值。
请返回p个下标对对应数值最大差值的最小值。

示例1：
输入：nums = [10,1,2,7,1,3], p = 2
输出：1
解释：第一个下标对选择1和4，第二个下标对选择2和5。
     最大差值为max(|nums[1]-nums[4]|,|nums[2]-nums[5]|)=max(0, 1)=1。
     所以我们返回1。

示例2：
输入：nums = [4,2,1,2], p = 1
输出：0
解释：选择下标1和3构成下标对。差值为|2-2|=0，这是最大差值的最小值。


提示：
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= p <= (nums.length)/2
*/

// 二分 + 贪心
class Solution {
 public:
  int minimizeMax(vector<int>& nums, int p) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    auto check = [&](int m) {
      int cnt = 0;
      for (int i = 0; i < n - 1; ++i) {
        if (nums[i + 1] - nums[i] <= m) {
          ++cnt;
          ++i;
        }
      }
      return cnt >= p;
    };

    int left = 0;
    int right = nums[n - 1] - nums[0];
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