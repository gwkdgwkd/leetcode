/*
给你一个整数数组nums，请计算数组的中心下标。
数组中心下标是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。
如果中心下标位于数组最左端，那么左侧数之和视为0，因为在下标的左侧不存在元素。
这一点对于中心下标位于数组最右端同样适用。
如果数组有多个中心下标，应该返回最靠近左边的那一个。
如果数组不存在中心下标，返回-1。

示例1：
输入：nums = [1, 7, 3, 6, 5, 6]
输出：3
解释：
中心下标是3。
左侧数之和sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11，
右侧数之和sum = nums[4] + nums[5] = 5 + 6 = 11，二者相等。

示例2：
输入：nums = [1, 2, 3]
输出：-1
解释：
数组中不存在满足此条件的中心下标。

示例3：
输入：nums = [2, 1, -1]
输出：0
解释：
中心下标是0。
左侧数之和sum = 0，（下标0左侧不存在元素），
右侧数之和sum = nums[1] + nums[2] = 1 + -1 = 0。

提示：
1 <= nums.length <= 10^4
-1000 <= nums[i] <= 1000
*/

int pivotIndex(int* nums, int numsSize) {
  int presum[numsSize + 1];
  memset(presum, 0, sizeof(presum));

  for (int i = 0; i < numsSize; ++i) {
    presum[i + 1] = presum[i] + nums[i];
  }

  for (int i = 0; i < numsSize; ++i) {
    if (presum[i] - presum[0] == presum[numsSize] - presum[i + 1]) {
      return i;
    }
  }

  return -1;
}