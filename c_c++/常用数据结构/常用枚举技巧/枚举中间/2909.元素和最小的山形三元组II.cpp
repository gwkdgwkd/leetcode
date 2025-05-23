/*
给一个下标从0开始的整数数组nums。
如果下标三元组(i, j, k)满足下述全部条件，则认为它是一个山形三元组：
i < j < k
nums[i] < nums[j]且nums[k] < nums[j]
请找出nums中元素和最小的山形三元组，并返回其元素和。如果不存在满足条件的三元组，返回-1。

示例1：
输入：nums = [8,6,1,5,3]
输出：9
解释：三元组(2, 3, 4)是一个元素和等于9的山形三元组，因为：
     2 < 3 < 4
     nums[2] < nums[3] 且 nums[4] < nums[3]
     这个三元组的元素和等于nums[2] + nums[3] + nums[4] = 9。
     可以证明不存在元素和小于9的山形三元组。

示例2：
输入：nums = [5,4,8,7,10,2]
输出：13
解释：三元组(1, 3, 5)是一个元素和等于13的山形三元组，因为：
     1 < 3 < 5
     nums[1] < nums[3] 且 nums[5] < nums[3]
     这个三元组的元素和等于nums[1] + nums[3] + nums[5] = 13。
     可以证明不存在元素和小于13的山形三元组。

示例3：
输入：nums = [6,5,4,3,4,5]
输出：-1
解释：可以证明nums中不存在山形三元组。


提示：
3 <= nums.length <= 10^5
1 <= nums[i] <= 10^8
*/

class Solution {
 public:
  int minimumSum(vector<int>& nums) {
    int n = nums.size();
    vector<int> suf(n);
    suf[n - 1] = nums[n - 1];
    for (int i = n - 2; i > 1; --i) {
      suf[i] = min(suf[i + 1], nums[i]);
    }

    int ans = INT_MAX;
    int pre = nums[0];
    for (int i = 1; i < n - 1; ++i) {
      if (pre < nums[i] && nums[i] > suf[i + 1]) {
        ans = min(ans, pre + nums[i] + suf[i + 1]);
      }
      pre = min(pre, nums[i]);
    }
    return ans == INT_MAX ? -1 : ans;
  }
};
