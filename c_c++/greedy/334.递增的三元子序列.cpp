/*
给你一个整数数组nums，判断这个数组中是否存在长度为3的递增子序列。
如果存在这样的三元组下标(i, j, k)且满足i < j < k，
使得nums[i] < nums[j] < nums[k]，返回true；否则，返回false。

示例1：
输入：nums = [1,2,3,4,5]
输出：true
解释：任何i < j < k的三元组都满足题意

示例2：
输入：nums = [5,4,3,2,1]
输出：false
解释：不存在满足题意的三元组

示例3：
输入：nums = [2,1,5,0,4,6]
输出：true
解释：三元组(3, 4, 5)满足题意，
     因为nums[3] == 0 < nums[4] == 4 < nums[5] == 6

提示：
1 <= nums.length <= 5 * 10^5
-2^31 <= nums[i] <= 2^31 - 1

进阶：你能实现时间复杂度为O(n)，空间复杂度为O(1)的解决方案吗？
*/

// 双向遍历
// 时间复杂度：O(n)
// 空间复杂度：O(n)
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
bool increasingTriplet(int *nums, int numsSize) {
  if (numsSize < 3) {
    return false;
  }
  int *leftMin = (int *)malloc(sizeof(int) * numsSize);
  int *rightMax = (int *)malloc(sizeof(int) * numsSize);
  leftMin[0] = nums[0];
  for (int i = 1; i < numsSize; i++) {
    leftMin[i] = MIN(leftMin[i - 1], nums[i]);
  }
  rightMax[numsSize - 1] = nums[numsSize - 1];
  for (int i = numsSize - 2; i >= 0; i--) {
    rightMax[i] = MAX(rightMax[i + 1], nums[i]);
  }
  for (int i = 1; i < numsSize - 1; i++) {
    if (nums[i] > leftMin[i - 1] && nums[i] < rightMax[i + 1]) {
      return true;
    }
  }
  free(leftMin);
  free(rightMax);
  return false;
}

// 贪心算法
// 时间复杂度：O(n)
// 空间复杂度：O(1)
bool increasingTriplet(int *nums, int numsSize) {
  if (numsSize < 3) {
    return false;
  }
  int first = nums[0], second = INT_MAX;
  for (int i = 1; i < numsSize; i++) {
    int num = nums[i];
    if (num > second) {
      return true;
    } else if (num > first) {
      second = num;
    } else {
      first = num;
    }
  }
  return false;
}

class Solution {
 public:
  bool increasingTriplet(vector<int> &nums) {
    int n = nums.size();
    if (n < 3) {
      return false;
    }

    int num1 = nums[0];
    int num2 = INT_MAX;
    for (int i = 1; i < n; ++i) {
      int num3 = nums[i];
      if (num3 > num2) {
        return true;
      } else if (num3 > num1) {
        num2 = num3;
      } else {
        num1 = num3;
      }
    }

    return false;
  }
};