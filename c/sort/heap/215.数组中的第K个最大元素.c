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
1 <= k <= nums.length <= 10^4
-104 <= nums[i] <= 10^4
*/

// 剑指OfferII076数组中的第k大的数字

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
    nums[0] = nums[i];  // 更新栈顶，不是结果的都丢弃

    // 堆定已经不是最大的元素来，调整堆
    HeapAdjust(nums, 0, i);
  }
  return nums[0];
}

// 快速选择算法是一个非常经典的算法，和快速排序算法是亲兄弟。
// 快速排序算法很重要的一种变形就是快速选择算法,
// 通常用来在未排序的数组中寻找第k小/第k大的元素。
// 快速选择及其变种是实际应用中最常使用的高效选择算法。
// 快速选择的总体思路与快速排序一致，选择一个元素作为基准来对元素进行分区，
// 将小于和大于基准的元素分在基准左边和右边的两个区域。
// 不同的是，快速选择并不递归访问双边，而是只递归进入一边的元素中继续寻找。
// 这降低了平均时间复杂度，从O(nlogn)至O(n)，不过最坏情况仍然是O(n^2)。
int Partition(int *nums, int left, int right) {  // 与快速排序一样，但是降序
  int ran = rand() % (right - left + 1);
  int pivotkey = nums[left + ran];
  nums[left + ran] = nums[left];
  nums[left] = pivotkey;

  // int key = nums[left];  // 选取第一个元素当作分割点，也可以，但比随机要慢

  while (left < right) {
    while (left < right && nums[right] <= pivotkey) {  // <=降序，>=升序
      --right;
    }
    nums[left] = nums[right];
    while (left < right && nums[left] >= pivotkey) {  // >=降序，<=升序
      ++left;
    }
    nums[right] = nums[left];
  }
  nums[left] = pivotkey;
  return left;
}
int QuickSelect(int *nums, int left, int right, int k) {  // 与快速排序不同
  int p = Partition(nums, left, right);
  if (p > k) {  // [left  p  k  right]
    return QuickSelect(nums, left, p - 1, k);
  } else if (p < k) {  // [left  k  p  right]
    return QuickSelect(nums, p + 1, right, k);
  } else {  // p == k，表示k位置的元素就是第k大的元素
    return nums[p];
  }
}
int findKthLargest(int *nums, int numsSize, int k) {
  srand(time(0));
  return QuickSelect(nums, 0, numsSize - 1, k - 1);
}