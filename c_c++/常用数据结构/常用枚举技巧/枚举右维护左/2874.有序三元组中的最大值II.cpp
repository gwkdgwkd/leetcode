/*
给一个下标从0开始的整数数组nums。
请从所有满足i < j < k的下标三元组(i, j, k)中，找出并返回下标三元组的最大值。
如果所有满足条件的三元组的值都是负数，则返回0。
下标三元组(i, j, k)的值等于(nums[i] - nums[j]) * nums[k]。

示例1：
输入：nums = [12,6,1,2,7]
输出：77
解释：下标三元组(0, 2, 4)的值是(nums[0] - nums[2]) * nums[4] = 77。
     可以证明不存在值大于77的有序下标三元组。

示例2：
输入：nums = [1,10,3,4,19]
输出：133
解释：下标三元组(1, 2, 4)的值是(nums[1] - nums[2]) * nums[4] = 133。
     可以证明不存在值大于133的有序下标三元组。

示例3：
输入：nums = [1,2,3]
输出：0
解释：唯一的下标三元组(0, 1, 2)的值是一个负数，
     (nums[0] - nums[1]) * nums[2] = -3 。因此，答案是0。


提示：
3 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
*/

/*
枚举j，为了让 (nums[i]−nums[j])∗nums[k]尽量大，
我们需要知道j左侧元素的最大值（让nums[i]−nums[j]尽量大），
以及j右侧元素的最大值（让乘积尽量大）。
也就是计算nums的前缀最大值preMax和后缀最大值sufMax，这可以用递推预处理：
preMax[i]=max(preMax[i−1],nums[i])
sufMax[i]=max(sufMax[i+1],nums[i])
*/
class Solution {
 public:
  long long maximumTripletValue(vector<int>& nums) {
    int n = nums.size();
    vector<int> suf_max(n);
    suf_max[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      suf_max[i] = max(suf_max[i + 1], nums[i]);
    }
    long long ans = 0;
    int pre_max = nums[0];
    for (int j = 1; j < n - 1; j++) {
      ans = max(ans, 1LL * (pre_max - nums[j]) * suf_max[j + 1]);
      pre_max = max(pre_max, nums[j]);
    }

    return ans;
  }
};

// 枚举k，需要知道k左边nums[i]−nums[j]的最大值
class Solution {
 public:
  long long maximumTripletValue(vector<int>& nums) {
    long long ans = 0;
    int max_diff = 0, pre_max = 0;
    for (int x : nums) {
      ans = max(ans, 1LL * max_diff * x);
      max_diff = max(max_diff, pre_max - x);
      pre_max = max(pre_max, x);
    }
    return ans;
  }
};