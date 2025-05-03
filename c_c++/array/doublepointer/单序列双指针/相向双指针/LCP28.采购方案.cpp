/*
小力将N个零件的报价存于数组nums。
小力预算为target，假定小力仅购买两个零件，
要求购买零件的花费不超过预算，请问他有多少种采购方案。
注意：答案需要以1e9 + 7(1000000007)为底取模。

示例1：
输入：nums = [2,5,3,5], target = 6
输出：1
解释：预算内仅能购买nums[0]与nums[2]。

示例2：
输入：nums = [2,2,1,9], target = 10
输出：4
解释：符合预算的采购方案如下：
     nums[0] + nums[1] = 4
     nums[0] + nums[2] = 3
     nums[1] + nums[2] = 3
     nums[2] + nums[3] = 10


提示：
2 <= nums.length <= 10^5
1 <= nums[i], target <= 10^5
*/

class Solution {
 public:
  int purchasePlans(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int left = 0;
    int right = nums.size() - 1;
    long long ans = 0;
    while (left < right) {
      if (nums[left] + nums[right] <= target) {
        ans += right - left;
        ++left;
      } else {
        --right;
      }
    }
    return ans % 1000000007;
  }
};