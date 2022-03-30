/*
给你一个整数数组nums，请你将该数组升序排列。

示例1：
输入：nums = [5,2,3,1]
输出：[1,2,3,5]

示例2：
输入：nums = [5,1,1,2,0,0]
输出：[0,0,1,1,2,5]

提示：
1 <= nums.length <= 5 * 104
-5 * 104 <= nums[i] <= 5 * 104
*/

// 堆排序
void HeapAdjust(int* heap, int parent, int size) {
  int temp = heap[parent];  // 保存父节点的值

  for (int child = parent * 2 + 1; child < size; child = 2 * child + 1) {
    // child是parent的左孩子，child+1是parent的右孩子
    if (child + 1 < size && heap[child] < heap[child + 1]) {
      ++child;  // 如果右孩子大于左孩子，i指向右孩子
    }
    if (temp > heap[child]) {
      break;  // 如果左右孩子中最大的，比父节点小，什么都不做
    }
    heap[parent] = heap[child];  // 父节点等于左右孩子中最大的那个
    parent = child;              // parent标识目前需要更新的孩子

    // 此时的i位置所表示的孩子（左右孩子中最大并且比父亲节点大）需要被更新，
    // 下次循环，目前的节点i更新到的它的左孩子处，即i=2*i+1
  }
  heap[parent] = temp;  // 此时top表示，父亲节点值（temp）应该存放的位置
}
void HeapSort(int* heap, int size) {
  // 根据无序数组创建大顶堆
  for (int i = size / 2 - 1; i >= 0; --i) {
    // size/2-1是从下标0开始的数组中（当成二叉树），从上到下，从左到右最后一个非叶子节点
    HeapAdjust(heap, i, size);
  }

  // 从大顶堆到升序排列的数组
  for (int i = size - 1; i >= 0; --i) {
    // 数组最后的元素依次与heap[0]交换，每次把heap中最大的元素放到数组后面
    int temp = heap[i];
    heap[i] = heap[0];
    heap[0] = temp;

    // 堆定已经不是最大的元素来，调整堆
    HeapAdjust(heap, 0, i);
  }
}

// 快速排序
int Partition(int* nums, int left, int right) {
  // 随机选取，不超时
  int rad = rand() % (right - left + 1);
  int pivotkey = nums[left + rad];
  nums[left + rad] = nums[left];
  nums[left] = pivotkey;

  // int pivotkey = nums[left]; // 超时
  while (left < right) {
    while (left < right && nums[right] >= pivotkey) {
      --right;
    }
    nums[left] = nums[right];
    while (left < right && nums[left] <= pivotkey) {
      ++left;
    }
    nums[right] = nums[left];
  }
  nums[left] = pivotkey;
  return left;
}
void QuickSort(int* nums, int left, int right) {
  if (left < right) {
    int partition = Partition(nums, left, right);
    QuickSort(nums, left, partition - 1);
    QuickSort(nums, partition + 1, right);
  }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
  QuickSort(nums, 0, numsSize - 1);
  HeapSort(nums, numsSize);

  *returnSize = numsSize;
  return nums;
}