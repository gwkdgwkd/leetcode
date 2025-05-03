/*
给一个下标从0开始的数组nums，数组大小为n，且由非负整数组成。
需要对数组执行n-1步操作，其中第i步操作（从0开始计数）要求对nums中第i个元素执行下述指令：
如果nums[i]==nums[i + 1]，则nums[i]的值变成原来的2倍，nums[i + 1]的值变成0。
否则，跳过这步操作。
在执行完全部操作后，将所有0移动到数组的末尾。
例如，数组[1,0,2,0,0,1]将所有0移动到末尾后变为[1,2,1,0,0,0]。
返回结果数组。
注意操作应当依次有序执行，而不是一次性全部执行。

示例1：
输入：nums = [1,2,2,1,1,0]
输出：[1,4,2,0,0,0]
解释：执行以下操作：
     i = 0:nums[0]和nums[1]不相等，跳过这步操作。
     i = 1:nums[1]和nums[2]相等，nums[1]的值变成原来的2倍，nums[2]的值变成0。
           数组变成[1,4,0,1,1,0]。
     i = 2:nums[2]和nums[3]不相等，所以跳过这步操作。
     i = 3:nums[3]和nums[4]相等，nums[3]的值变成原来的2倍，nums[4]的值变成0。
           数组变成 [1,4,0,2,0,0]。
     i = 4:nums[4]和nums[5]相等，nums[4]的值变成原来的2倍，nums[5]的值变成0。
           数组变成 [1,4,0,2,0,0]。
     执行完所有操作后，将0全部移动到数组末尾，得到结果数组[1,4,2,0,0,0]。

示例2：
输入：nums = [0,1]
输出：[1,0]
解释：无法执行任何操作，只需要将0移动到末尾。


提示：
2 <= nums.length <= 2000
0 <= nums[i] <= 1000
*/

class Solution {
 public:
  vector<int> applyOperations(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
      if (nums[i] == nums[i + 1]) {
        nums[i] *= 2;
        nums[i + 1] = 0;
        ++i;  // 不写也可以
      }
    }

    int slow = 0;
    int fast = 0;
    while (fast < n) {
      if (nums[fast] != 0) {
        nums[slow++] = nums[fast];
      }
      ++fast;
    }
    while (slow < n) {
      nums[slow++] = 0;
    }

    return nums;
  }
};