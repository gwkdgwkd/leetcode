/*
给一个数组nums，数组中只包含非负整数。
定义rev(x)的值为将整数x各个数字位反转得到的结果。
比方说rev(123) = 321，rev(120) = 21。
我们称满足下面条件的下标对(i, j)是好的：
0 <= i < j < nums.length
nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
请返回好下标对的数目。由于结果可能会很大，请将结果对10^9+7取余后返回。

示例1：
输入：nums = [42,11,1,97]
输出：2
解释：两个坐标对为：
     (0,3)：42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121。
     (1,2)：11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12。

示例2：
输入：nums = [13,10,35,24,76]
输出：4


提示：
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
*/

class Solution {
 public:
  int countNicePairs(vector<int>& nums) {
    auto rev = [](int num) {
      int ans = 0;
      while (num) {
        ans = ans * 10 + num % 10;
        num /= 10;
      }

      return ans;
    };

    unordered_map<int, int> cnt;
    long long ans = 0;
    for (auto num : nums) {
      ans += cnt[num - rev(num)]++;
    }
    return ans % (1000000007);
  }
};