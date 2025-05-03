/*
给定一个非负整数数组nums，nums中一半整数是奇数，一半整数是偶数。
对数组进行排序，以便当nums[i]为奇数时，i也是奇数；当nums[i]为偶数时，i也是偶数。
可以返回 任何满足上述条件的数组作为答案。

示例1：
输入：nums = [4,2,5,7]
输出：[4,5,2,7]
解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5]也会被接受。

示例2：
输入：nums = [2,3]
输出：[2,3]


提示：
2 <= nums.length <= 2 * 10^4
nums.length是偶数
nums中一半是偶数
0 <= nums[i] <= 1000

进阶：可以不使用额外空间解决问题吗？
*/

class Solution {
 public:
  vector<int> sortArrayByParityII(vector<int>& nums) {
    int i = 0;
    int j = 1;
    while (i < nums.size()) {
      if (nums[i] % 2 == 0) {
        i += 2;
      } else if (nums[j] % 2) {
        j += 2;
      } else {
        swap(nums[i], nums[j]);
        i += 2;
        j += 2;
      }
    }
    return nums;
  }
};