/*
给定一个已按照升序排列的整数数组numbers，请你从数组中找出两个数满足相加之和等于目标数target。
函数应该以长度为2的整数数组的形式返回这两个数的下标值。
numbers的下标从0开始计数，
所以答案数组应当满足0 <= answer[0] < answer[1] < numbers.length。
假设数组中存在且只存在一对符合条件的数字，同时一个数字不能使用两次。

示例1：
输入：numbers = [1,2,4,6,10], target = 8
输出：[1,3]
解释：2与6之和等于目标数8。因此index1 = 1, index2 = 3。

示例2：
输入：numbers = [2,3,4], target = 6
输出：[0,2]

示例3
输入：numbers = [-1,0], target = -1
输出：[0,1]

提示：
2 <= numbers.length <= 3 * 10^4
-1000 <= numbers[i] <= 1000
numbers按递增顺序排列
-1000 <= target <= 1000
仅存在一个有效答案

注意：本题与167题相似（下标起点不同）
*/

// 二分查找
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize) {
  int *ret = (int *)malloc(sizeof(int) * 2);
  *returnSize = 2;

  for (int i = 0; i < numbersSize; ++i) {
    int low = i + 1, high = numbersSize - 1;
    while (low <= high) {
      int mid = (high - low) / 2 + low;
      if (numbers[mid] == target - numbers[i]) {
        ret[0] = i, ret[1] = mid;
        return ret;
      } else if (numbers[mid] > target - numbers[i]) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
  }
  ret[0] = -1, ret[1] = -1;
  return ret;
}

// 双指针
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize) {
  int left = 0;
  int right = numbersSize - 1;

  while (left < right) {
    int sum = numbers[left] + numbers[right];
    if (sum > target) {
      --right;
    } else if (sum < target) {
      ++left;
    } else {
      break;
    }
  }

  *returnSize = 2;
  int *res = (int *)malloc(sizeof(int) * 2);
  res[0] = left;
  res[1] = right;

  return res;
}