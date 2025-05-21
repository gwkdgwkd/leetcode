/*
给一个整数数组nums。
如果一组数字(i,j)满足nums[i] == nums[j]且i < j，就可以认为这是一组好数对。
返回好数对的数目。

示例1：
输入：nums = [1,2,3,1,1,3]
输出：4
解释：有4组好数对，分别是(0,3),(0,4),(3,4),(2,5)，下标从0开始

示例2：
输入：nums = [1,1,1,1]
输出：6
解释：数组中的每组数字都是好数对

示例 3：
输入：nums = [1,2,3]
输出：0


提示：
1 <= nums.length <= 100
1 <= nums[i] <= 100
*/

class Solution {
 public:
  int numIdenticalPairs(vector<int>& nums) {
    int ans = 0;
    unordered_map<int, int> cnt;
    for (int x : nums) {
      ans += cnt[x]++;
    }
    return ans;
  }
};