/*
给你一个整数数组nums，你需要找出一个连续子数组，
如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
请你找出符合题意的最短子数组，并输出它的长度。

示例1：
输入：nums = [2,6,4,8,10,9,15]
输出：5
解释：你只需要对[6, 4, 8, 10, 9]进行升序排序，
     那么整个表都会变为升序排序。

示例2：
输入：nums = [1,2,3,4]
输出：0

示例3：
输入：nums = [1]
输出：0

提示：
1 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5

进阶：你可以设计一个时间复杂度为O(n)的解决方案吗？
*/

// 排序
// 时间复杂度：O(nlog⁡n)
// 空间复杂度：O(n)
bool is_sorted(int *arr, int arrSize) {
  for (int i = 1; i < arrSize; i++) {
    if (arr[i - 1] > arr[i]) {
      return false;
    }
  }
  return true;
}
int cmp(int *a, int *b) { return *a - *b; }
int findUnsortedSubarray(int *nums, int numsSize) {
  if (is_sorted(nums, numsSize)) {
    return 0;
  }
  int numsSorted[numsSize];
  memcpy(numsSorted, nums, sizeof(int) * numsSize);
  qsort(numsSorted, numsSize, sizeof(int), cmp);
  int left = 0;
  while (nums[left] == numsSorted[left]) {
    left++;
  }
  int right = numsSize - 1;
  while (nums[right] == numsSorted[right]) {
    right--;
  }
  return right - left + 1;
}

class Solution {
 public:
  int findUnsortedSubarray(vector<int> &nums) {
    vector<int> arr(nums);
    sort(arr.begin(), arr.end());

    int start = -1;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      if (nums[i] != arr[i]) {
        start = i;
        break;
      }
    }
    if (start == -1) {
      return 0;
    }
    int end;
    for (int i = n - 1; i >= start; --i) {
      if (nums[i] != arr[i]) {
        end = i;
        break;
      }
    }

    return end - start + 1;
  }
};

// 假设把这个数组分成三段，左段和右段是标准的升序数组，
// 中段数组虽是无序的，但满足最小值大于左段的最大值，
// 最大值小于右段的最小值。
int findUnsortedSubarray(int *nums, int numsSize) {
  int n = numsSize;
  int maxn = INT_MIN, right = -1;
  int minn = INT_MAX, left = -1;
  for (int i = 0; i < n; i++) {
    // 从左到右维持最大值，寻找右边界end：
    if (maxn > nums[i]) {
      right = i;
    } else {
      maxn = nums[i];
    }
    // 从右到左维持最小值，寻找左边界begin：
    if (minn < nums[n - i - 1]) {
      left = n - i - 1;
    } else {
      minn = nums[n - i - 1];
    }
  }
  return right == -1 ? 0 : right - left + 1;
}

// 面试题1616部分排序
// 先排序再比较
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
int *subSort(int *array, int arraySize, int *returnSize) {
  int *tmp = (int *)malloc(sizeof(int) * arraySize);
  memcpy(tmp, array, sizeof(int) * arraySize);

  qsort(tmp, arraySize, sizeof(int), cmp);
  int *retAns = (int *)malloc(2 * sizeof(int));
  retAns[0] = -1;
  retAns[1] = -1;
  *returnSize = 2;

  for (int i = 0; i < arraySize; i++) {
    if (array[i] != tmp[i] && retAns[0] == -1) {
      retAns[0] = i;
    }

    if (array[i] != tmp[i]) {
      retAns[1] = i;
    }
  }

  return retAns;
}
