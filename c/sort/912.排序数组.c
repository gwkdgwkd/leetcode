/*
给你一个整数数组nums，请你将该数组升序排列。

示例1：
输入：nums = [5,2,3,1]
输出：[1,2,3,5]

示例2：
输入：nums = [5,1,1,2,0,0]
输出：[0,0,1,1,2,5]

提示：
1 <= nums.length <= 5 * 10^4
-5 * 10^4 <= nums[i] <= 5 * 10^4
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
void BuildHeap(int* heap, int size) {
  // 根据无序数组创建大顶堆
  for (int i = size / 2 - 1; i >= 0; --i) {
    // size/2-1是从下标0开始的数组中（当成二叉树），从上到下，从左到右最后一个非叶子节点
    HeapAdjust(heap, i, size);
  }
}
void HeapSort(int* heap, int size) {
  BuildHeap(heap, size);

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
  nums[left] = pivotkey;  // 这句没有也能得到正确结果

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

// 冒泡排序
void BubbleSort(int* nums, int numsSize) {
  for (int i = 0; i < numsSize - 1; ++i) {
    for (int j = 0; j < numsSize - 1 - i; ++j) {
      if (nums[j] > nums[j + 1]) {
        int tmp = nums[j];
        nums[j] = nums[j + 1];
        nums[j + 1] = tmp;
      }
    }
  }
}

// 简单选择排序
void SelectionSort(int* nums, int numsSize) {
  for (int i = 0; i < numsSize - 1; ++i) {
    for (int j = i + 1; j < numsSize; ++j) {
      if (nums[i] > nums[j]) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
      }
    }
  }
}

// 直接插入排序
void InsertSort(int* nums, int size) {
  for (int i = 1; i < size; i++) {
    if (nums[i] < nums[i - 1]) {
      int temp = nums[i];
      int j = i - 1;
      while (j >= 0 && temp < nums[j]) {
        nums[j + 1] = nums[j];
        --j;
      }
      nums[j + 1] = temp;
    }
  }
}

// 希尔排序
void ShellSort(int* nums, int size) {
  int interval = 1;
  while (interval < size / 3) {
    interval = interval * 3 + 1;
  }

  while (interval) {
    for (int i = interval; i < size; ++i) {
      if (nums[i] < nums[i - interval]) {
        int temp = nums[i];
        int j = i - interval;
        while (j >= interval - 1 && temp < nums[j]) {  // j>=0也行
          nums[j + interval] = nums[j];
          j = j - interval;
        }
        nums[j + interval] = temp;
      }
    }
    interval = (interval - 1) / 3;
  }
}

// 归并排序
void Merge(int* nums, int start, int mid, int end) {
  int llen = mid - start + 1;
  int rlen = end - mid;
  int left[llen], right[rlen];
  memcpy(left, nums + start, sizeof(int) * llen);
  memcpy(right, nums + mid + 1, sizeof(int) * rlen);

  int li = 0, ri = 0, k = start;
  while (li < llen && ri < rlen) {
    nums[k++] = left[li] < right[ri] ? left[li++] : right[ri++];
  }
  while (li < llen) {
    nums[k++] = left[li++];
  }
}
void MergeSort(int* nums, int start, int end) {
  if (start < end) {
    int mid = start + (end - start) / 2;
    MergeSort(nums, start, mid);
    MergeSort(nums, mid + 1, end);
    Merge(nums, start, mid, end);
  }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
  srand(time(0));
  QuickSort(nums, 0, numsSize - 1);

  HeapSort(nums, numsSize);

  BubbleSort(nums, numsSize);

  SelectionSort(nums, numsSize);

  InsertSort(nums, numsSize);

  ShellSort(nums, numsSize);

  MergeSort(nums, 0, numsSize - 1);

  *returnSize = numsSize;
  return nums;
}