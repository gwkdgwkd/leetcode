/*
给定整数数组nums和整数k，请返回数组中第k个最大的元素。
请注意，你需要找的是数组排序后的第k个最大的元素，而不是第k个不同的元素。

示例1:
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5

示例2:
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4

提示：
1 <= k <= nums.length <= 104
-104 <= nums[i] <= 104
*/

// 思路：
// 给nums数组排个序，然后取第k个元素，也就是nums[k-1]，不就行了吗？
// 当然可以，但是排序时间复杂度是O(NlogN)，其中N表示数组nums的长度。
int cmp(const void *a, const void *b) { return *(int *)b - *(int *)a; }
int findKthLargest(int *nums, int numsSize, int k) {
  qsort(nums, numsSize, sizeof(int), cmp);
  for (int i = 0; i < numsSize; ++i) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  return nums[k - 1];
}

// 想要第k大的元素，却给整个数组排序，有点杀鸡用牛刀的感觉
// 使用些技巧，可以把时间复杂度降低到O(NlogK)甚至是O(N)。
// 基于堆排序的选择方法
// 时间复杂度：O(nlog⁡n)，建堆的时间代价是O(n)，删除的总代价是O(klog⁡n)，
//          因为k<n，故渐进时间复杂为O(n+klog⁡n)=O(nlog⁡n)。
// 空间复杂度：O(log⁡n)，即递归使用栈空间的空间代价。
void maxHeapify(int *a, int i, int heapSize) {
  int l = i * 2 + 1, r = i * 2 + 2, largest = i;
  if (l < heapSize && a[l] > a[largest]) {
    largest = l;
  }
  if (r < heapSize && a[r] > a[largest]) {
    largest = r;
  }
  if (largest != i) {
    int t = a[i];
    a[i] = a[largest], a[largest] = t;
    maxHeapify(a, largest, heapSize);
  }
}
void buildMaxHeap(int *a, int heapSize) {
  for (int i = heapSize / 2; i >= 0; --i) {
    maxHeapify(a, i, heapSize);
  }
}
int findKthLargest(int *nums, int numsSize, int k) {
  int heapSize = numsSize;
  buildMaxHeap(nums, heapSize);
  for (int i = numsSize - 1; i >= numsSize - k + 1; --i) {
    int t = nums[0];
    nums[0] = nums[i], nums[i] = t;
    --heapSize;
    maxHeapify(nums, 0, heapSize);
  }
  return nums[0];
}

// 快速选择算法是一个非常经典的算法，和快速排序算法是亲兄弟。
int partition(int *a, int l, int r) {
  int x = a[r], i = l - 1;
  for (int j = l; j < r; ++j) {
    if (a[j] <= x) {
      int t = a[++i];
      a[i] = a[j], a[j] = t;
    }
  }
  int t = a[i + 1];
  a[i + 1] = a[r], a[r] = t;
  return i + 1;
}
int randomPartition(int *a, int l, int r) {
  int i = rand() % (r - l + 1) + l;
  int t = a[i];
  a[i] = a[r], a[r] = t;
  return partition(a, l, r);
}
int quickSelect(int *a, int l, int r, int index) {
  int q = randomPartition(a, l, r);
  if (q == index) {
    return a[q];
  } else {
    return q < index ? quickSelect(a, q + 1, r, index)
                     : quickSelect(a, l, q - 1, index);
  }
}
int findKthLargest(int *nums, int numsSize, int k) {
  srand(time(0));
  return quickSelect(nums, 0, numsSize - 1, numsSize - k);
}
