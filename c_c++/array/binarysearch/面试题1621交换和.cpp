/*
给定两个整数数组，请交换一对数值（每个数组中取一个数值），使得两个数组所有元素的和相等。
返回一个数组，第一个元素是第一个数组中要交换的元素，第二个元素是第二个数组中要交换的元素。
若有多个答案，返回任意一个均可。若无满足条件的数值，返回空数组。

示例：
输入：array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
输出：[1, 3]

示例：
输入：array1 = [1, 2, 3], array2 = [4, 5, 6]
输出：[]

提示：1 <= array1.length, array2.length <= 100000
*/

int binarysearch(int *nums, int left, int right, int target) {
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    } else {
      return mid;
    }
  }

  return -1;
}
int cmp(int *a, int *b) { return *a - *b; }
int *findSwapValues(int *array1, int array1Size, int *array2, int array2Size,
                    int *returnSize) {
  int sum1 = 0;
  for (int i = 0; i < array1Size; ++i) {
    sum1 += array1[i];
  }

  int sum2 = 0;
  for (int i = 0; i < array2Size; ++i) {
    sum2 += array2[i];
  }

  int sum = sum1 + sum2;
  if (sum % 2) {
    *returnSize = 0;
    return NULL;
  }

  int target = (sum1 - sum2) / 2;
  qsort(array2, array2Size, sizeof(int), cmp);

  int *res = NULL;
  *returnSize = 0;
  for (int i = 0; i < array1Size; ++i) {
    int index = binarysearch(array2, 0, array2Size - 1, array1[i] - target);
    if (index != -1) {
      res = (int *)malloc(sizeof(int) * 2);
      *returnSize = 2;
      res[0] = array1[i];
      res[1] = array2[index];
    }
  }

  return res;
}

class Solution {
 public:
  int binarySearch(vector<int> &arr, int left, int right, int target) {
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] < target) {
        left = mid + 1;
      } else if (arr[mid] > target) {
        right = mid - 1;
      } else {
        return mid;
      }
    }

    return -1;
  }
  vector<int> findSwapValues(vector<int> &array1, vector<int> &array2) {
    int sum1 = accumulate(array1.begin(), array1.end(), 0);
    int sum2 = accumulate(array2.begin(), array2.end(), 0);

    if ((sum1 + sum2) % 2) {
      return {};
    }

    int target = (sum1 - sum2) / 2;
    sort(array1.begin(), array1.end());
    for (int i = 0; i < array2.size(); ++i) {
      int index =
          binarySearch(array1, 0, array1.size() - 1, array2[i] + target);
      if (index != -1) {
        return {array2[i] + target, array2[i]};
      }
    }

    return {};
  }
};