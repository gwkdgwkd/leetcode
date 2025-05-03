/*
给一个整数数组nums。请你按照以下顺序依次执行操作，转换nums：
将每个偶数替换为0。
将每个奇数替换为1。
按非递减顺序排序修改后的数组。
执行完这些操作后，返回结果数组。

示例1:
输入：nums = [4,3,2,1]
输出：[0,0,1,1]
解释：将偶数（4和2）替换为0，将奇数（3和1）替换为1。
     现在，nums = [0, 1, 0, 1]。
     按非递减顺序排序nums，得到nums = [0, 0, 1, 1]。

示例2:
输入：nums = [1,5,1,4,2]
输出：[0,0,1,1,1]
解释：将偶数（4和2）替换为0，将奇数（1,5和1）替换为1。
     现在，nums = [1, 1, 1, 0, 0]。
     按非递减顺序排序nums，得到nums = [0, 0, 1, 1, 1]。


提示：
1 <= nums.length <= 100
1 <= nums[i] <= 1000
*/

class Solution {
 public:
  vector<int> transformArray(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      if (nums[i] % 2) {
        nums[i] = 1;
      } else {
        nums[i] = 0;
      }
    }

    int slow = 0;
    int fast = 0;
    while (fast < n) {
      if (nums[fast] == 0) {
        nums[slow++] = nums[fast];  // 0
      }
      ++fast;
    }
    while (slow < n) {
      nums[slow++] = 1;
    }
    return nums;
  }
};