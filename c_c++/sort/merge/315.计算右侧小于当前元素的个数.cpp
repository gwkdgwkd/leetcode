/*
给一个整数数组nums，按要求返回一个新数组counts。
数组counts有该性质：counts[i]的值是nums[i]右侧小于nums[i]的元素的数量。

示例1：
输入：nums = [5,2,6,1]
输出：[2,1,1,0]
解释：
5的右侧有2个更小的元素(2和1)
2的右侧仅有1个更小的元素(1)
6的右侧有1个更小的元素(1)
1的右侧有0个更小的元素

示例2：
输入：nums = [-1]
输出：[0]

示例3：
输入：nums = [-1,-1]
输出：[0,0]

提示：
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 离散化树状数组

// 归并排序
typedef struct {
  int index;
  int value;
  int cnt;
} Data;
void print(Data* data, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%d(%d,%d) ", data[i].value, data[i].index, data[i].cnt);
  }
  printf("\n");
}
void Merge(Data* numbers, int left, int mid, int right) {
  // tmpArr保存left-right区间内排序后的结果，然后回填给numbers
  Data tmpArr[right - left + 1];
  int lleft = left;
  int rleft = mid + 1;
  int k = 0;
  while (lleft <= mid || rleft <= right) {
    if (rleft > right) {  // 右侧取完
      tmpArr[k++] = numbers[lleft++];
    } else if (lleft > mid) {  // 左侧取完
      tmpArr[k++] = numbers[rleft++];
    } else if (numbers[lleft].value > numbers[rleft].value) {
      // 左边大于右边，把右边比左小的数量加给左边
      numbers[lleft].cnt += right - rleft + 1;
      tmpArr[k++] = numbers[lleft++];
    } else {  // 右边大于等于左边
      tmpArr[k++] = numbers[rleft++];
    }
  }

  for (int i = 0; i < k; i++) {
    numbers[left++] = tmpArr[i];
  }
  // print(tmpArr, sizeof(tmpArr) / sizeof(Data));

  return;
}
void MergeSorting(Data* numbers, int left, int right) {
  if (left == right) {
    return;
  }

  int mid = left + (right - left) / 2;
  MergeSorting(numbers, left, mid);
  MergeSorting(numbers, mid + 1, right);
  Merge(numbers, left, mid, right);
  return;
}
int* countSmaller(int* nums, int numsSize, int* returnSize) {
  // 通过归并排序求解，排序过程中index会变化，需要保存原始index值
  Data* numbers = (Data*)malloc(sizeof(Data) * numsSize);
  for (int i = 0; i < numsSize; i++) {
    numbers[i].index = i;
    numbers[i].value = nums[i];
    numbers[i].cnt = 0;
  }
  // print(numbers, numsSize);

  MergeSorting(numbers, 0, numsSize - 1);
  int* counts = (int*)malloc(sizeof(int) * numsSize);
  memset(counts, 0, sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; i++) {
    counts[numbers[i].index] = numbers[i].cnt;
  }
  *returnSize = numsSize;
  return counts;
}

int main() {
  int nums[] = {5, 2, 6, 1};

  int size;
  int* result = countSmaller(nums, sizeof(nums) / sizeof(int), &size);

  // for (int i = 0; i < size; ++i) {
  //   printf("%d ", result[i]);
  // }
  // printf("\n");

  // 5(0,0) 2(1,0) 6(2,0) 1(3,0)
  // 5(0,1) 2(1,0)
  // 6(2,1) 1(3,0)
  // 6(2,1) 5(0,2) 2(1,1) 1(3,0)
  // 2 1 1 0

  return 0;
}

#include <vector>
using namespace std;
class Solution {
 public:
  typedef pair<int, int> PII;
  vector<int> ans;
  vector<PII> data;
  void merge(int left, int mid, int right) {
    int len = right - left + 1;
    vector<PII> temp(len);
    int cur = 0;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
      if (data[i].first > data[j].first) {
        ans[data[i].second] += right - j + 1;
        temp[cur++] = data[i++];
      } else {
        temp[cur++] = data[j++];
      }
    }
    while (i <= mid) {
      temp[cur++] = data[i++];
    }
    while (j <= right) {
      temp[cur++] = data[j++];
    }
    cur = 0;
    for (int i = left; i <= right; ++i) {
      data[i] = temp[cur++];
    }
  }
  void mergeSort(int left, int right) {
    if (left >= right) {
      return;
    }
    int mid = (left + right) >> 1;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(left, mid, right);
  }
  vector<int> countSmaller(vector<int>& nums) {
    int n = nums.size();
    data.reserve(n);
    ans.resize(n, 0);
    for (int i = 0; i < n; ++i) {
      data.emplace_back(nums[i], i);
    }
    mergeSort(0, n - 1);
    return ans;
  }
};