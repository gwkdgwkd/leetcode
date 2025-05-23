/*
峰值元素是指其值严格大于左右相邻值的元素。
给一个整数数组nums，找到峰值元素并返回其索引。
数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。
可以假设nums[-1] = nums[n] = -∞。
必须实现时间复杂度为O(logn)的算法来解决此问题。

示例1：
输入：nums = [1,2,3,1]
输出：2
解释：3是峰值元素，你的函数应该返回其索引2。

示例2：
输入：nums = [1,2,1,3,5,6,4]
输出：1或5
解释：函数可以返回索引1，其峰值元素为2；
     或者返回索引5，其峰值元素为6。


提示：
1 <= nums.length <= 1000
-2^31 <= nums[i] <= 2^31 - 1
对于所有有效的i都有nums[i] != nums[i + 1]
*/

// 这样想，中点所在地方，可能是某座山的山峰，山的下坡处，山的上坡处，如果是山峰，
// 最后会二分终止也会找到，关键是二分方向，并不知道山峰在左边还是右边，可以想象成爬山。
// 如果你往下坡方向走，也许可能遇到新的山峰，但是也许是一个一直下降的坡，最后到边界。
// 但是如果你往上坡方向走，就算最后一直上的边界，由于最边界是负无穷，所以就一定能找到山峰，
// 总的一句话，往递增的方向上，二分，一定能找到，往递减的方向只是可能找到，也许没有。
int findPeakElement(int* nums, int numsSize) {
  int left = 0;
  int right = numsSize - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] > nums[mid + 1]) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
      // int mid = left + (right - left) / 2;
      int mid = left + ((right - left) >> 1);
      if (nums[mid] > nums[mid + 1]) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};