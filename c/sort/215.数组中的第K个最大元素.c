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

void HeapAdjust(int *heap, int top, int size) {
  int temp = heap[top];  // 保存父节点的值
  for (int i = top * 2 + 1; i < size; i = 2 * i + 1) {
    // i是top的左孩子，i+1是top的右孩子
    if (i + 1 < size && heap[i] < heap[i + 1]) {
      ++i;  // 如果右孩子大于左孩子，i指向右孩子
    }
    if (temp > heap[i]) {
      break;  // 如果左右孩子中最大的，比父节点小，什么都不做
    }
    heap[top] = heap[i];  // 父节点等于左右孩子中最大的那个
    top = i;              // top标识目前需要更新的孩子

    // 此时的i位置所表示的孩子（左右孩子中最大并且比父亲节点大）需要被更新，
    // 下次循环，目前的节点i更新到的它的左孩子处，即i=2*i+1
  }
  heap[top] = temp;  // 此时top表示，父亲节点值（temp）应该存放的位置
}

int findKthLargest(int *nums, int numsSize, int k) {
  // 根据无序数组创建大顶堆
  for (int i = numsSize / 2 - 1; i >= 0; --i) {
    // size/2-1是从下标0开始的数组中（当成二叉树），从上到下，从左到右最后一个非叶子节点
    HeapAdjust(nums, i, numsSize);
  }

  // 从大顶堆到升序排列的数组
  for (int i = numsSize - 1; i >= numsSize - k + 1; --i) {
    // 数组最后的元素依次与heap[0]交换，每次把heap中最大的元素放到数组后面
    int temp = nums[i];
    nums[i] = nums[0];
    nums[0] = temp;

    // 堆定已经不是最大的元素来，调整堆
    HeapAdjust(nums, 0, i);
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
