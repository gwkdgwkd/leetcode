#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

/*
给你一个整数数组nums，请将该数组升序排列。

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

using namespace std;

namespace n1 {
// 堆排序
void HeapAdjust(int* heap, int parent, int size) {
  int temp = heap[parent];  // 保存父节点的值

  for (int child = parent * 2 + 1; child < size; child = 2 * child + 1) {
    // child是parent的左孩子，child+1是parent的右孩子：
    if (child + 1 < size && heap[child] < heap[child + 1]) {
      ++child;  // 如果右孩子大于左孩子，i指向右孩子
    }
    if (temp > heap[child]) {
      break;  // 如果左右孩子中最大的，比父节点小，什么都不做
    }
    heap[parent] = heap[child];  // 父节点等于左右孩子中最大的那个
    parent = child;              // parent标识目前需要更新的孩子

    // 此时的child位置所表示的孩子（左右孩子中最大并且比父亲节点大）需要被更新，
    // 下次循环，目前的节点child更新到的它的左孩子处，即i=2*i+1
  }
  // 此时parent表示，父亲节点值（temp）应该存放的位置：
  heap[parent] = temp;
}
void BuildHeap(int* heap, int size) {
  // 根据无序数组创建大顶堆
  for (int i = size / 2 - 1; i >= 0; --i) {
    // size/2-1是从下标0开始的数组中（当成二叉树），
    // 从上到下，从左到右最后一个非叶子节点：
    HeapAdjust(heap, i, size);
  }
}
void HeapSort(int* heap, int size) {
  BuildHeap(heap, size);

  // 从大顶堆到升序排列的数组
  for (int i = size - 1; i >= 0; --i) {
    // 数组最后的元素依次与heap[0]交换，
    // 每次把heap中最大的元素放到数组后面：
    int temp = heap[i];
    heap[i] = heap[0];
    heap[0] = temp;

    // 堆定已经不是最大的元素来，调整堆：
    HeapAdjust(heap, 0, i);
  }
}
int* sortArray(int* nums, int numsSize, int* returnSize) {
  HeapSort(nums, numsSize);
  *returnSize = numsSize;
  return nums;
}

class Solution {
  void HeapAdjust(vector<int>& nums, int parent, int len) {
    int temp = nums[parent];
    for (int child = parent * 2 + 1; child < len; child = child * 2 + 1) {
      if (child + 1 < len && nums[child] < nums[child + 1]) {
        ++child;
      }
      if (temp > nums[child]) {
        break;
      }
      nums[parent] = nums[child];
      parent = child;
    }
    nums[parent] = temp;
  }
  void BuildHeap(vector<int>& nums, int len) {
    for (int i = len / 2 - 1; i >= 0; --i) {
      HeapAdjust(nums, i, len);
    }
  }

 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();
    BuildHeap(nums, n);
    for (int i = n - 1; i >= 0; --i) {
      swap(nums[i], nums[0]);
      HeapAdjust(nums, 0, i);
    }
    return nums;
  }
};
}  // namespace n1

namespace n2 {
// 快速排序
namespace two {
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
int* sortArray(int* nums, int numsSize, int* returnSize) {
  srand(time(0));
  QuickSort(nums, 0, numsSize - 1);
  *returnSize = numsSize;
  return nums;
}

class Solution {
  int Partition(vector<int>& nums, int left, int right) {
    int rad = rand() % (right - left + 1);
    int pivotkey = nums[rad + left];
    nums[rad + left] = nums[left];
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
  void QuickSort(vector<int>& nums, int left, int right) {
    if (left < right) {
      int mid = Partition(nums, left, right);
      QuickSort(nums, left, mid);
      QuickSort(nums, mid + 1, right);
    }
  }

 public:
  vector<int> sortArray(vector<int>& nums) {
    srand(time(0));
    int n = nums.size();
    QuickSort(nums, 0, n - 1);
    return nums;
  }
};
}  // namespace two

namespace three {
// 如果重复的元素太多，普通的快速排序会倒退，导致超时
class Solution {
 public:
  void QuickSort(vector<int>& nums, int left, int right) {
    if (left >= right) {
      return;
    }

    int random = left + rand() % (right - left + 1);
    swap(nums[left], nums[random]);
    int pivotkey = nums[left];

    // 三路快排：分为小于，等于，大于三部分
    int li = left;  // 表示小于pivotkey的最右边的位置，初始为第一个位置之前
    int ri = right + 1;  // 表示大于pivotkey的最左边的位置，初始为最后一个之后
    int i = left + 1;  // 表示等于pivotkey的做右边的位置，初始为第一元素
    while (i < ri) {
      if (nums[i] < pivotkey) {
        swap(nums[++li], nums[i++]);
      } else if (nums[i] > pivotkey) {
        swap(nums[--ri], nums[i]);
      } else {
        ++i;
      }
    }
    swap(nums[left], nums[li]);

    // 减1是因为nums[li]与nums[left]交换了，此时是等于pivotkey的：
    QuickSort(nums, left, li - 1);
    QuickSort(nums, ri, right);
  }
  vector<int> sortArray(vector<int>& nums) {
    QuickSort(nums, 0, nums.size() - 1);
    return nums;
  }
};
}  // namespace three
}  // namespace n2

namespace n3 {
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
int* sortArray(int* nums, int numsSize, int* returnSize) {
  BubbleSort(nums, numsSize);
  *returnSize = numsSize;
  return nums;
}

class Solution {
 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
      for (int j = 0; j < n - 1 - i; ++j) {
        if (nums[j] > nums[j + 1]) {
          swap(nums[j], nums[j + 1]);
        }
      }
    }

    return nums;
  }
};
}  // namespace n3

namespace n4 {
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
int* sortArray(int* nums, int numsSize, int* returnSize) {
  SelectionSort(nums, numsSize);
  *returnSize = numsSize;
  return nums;
}

class Solution {
 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (nums[j] < nums[i]) {
          swap(nums[i], nums[j]);
        }
      }
    }

    return nums;
  }
};
}  // namespace n4

namespace n5 {
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
int* sortArray(int* nums, int numsSize, int* returnSize) {
  InsertSort(nums, numsSize);
  *returnSize = numsSize;
  return nums;
}

class Solution {
 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();
    for (int i = 1; i < n; ++i) {
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

    return nums;
  }
};
}  // namespace n5

namespace n6 {
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
int* sortArray(int* nums, int numsSize, int* returnSize) {
  ShellSort(nums, numsSize);
  *returnSize = numsSize;
  return nums;
}

class Solution {
 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();
    int interval = 1;
    while (interval < n / 3) {
      interval = interval * 3 + 1;
    }

    while (interval) {
      for (int i = interval; i < n; ++i) {
        if (nums[i - interval] > nums[i]) {
          int tmp = nums[i];
          int j = i - interval;
          while (j >= 0 && nums[j] > tmp) {
            nums[j + interval] = nums[j];
            j -= interval;
          }
          nums[j + interval] = tmp;
        }
      }
      interval = (interval - 1) / 3;
    }
    return nums;
  }
};
}  // namespace n6

namespace n7 {
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
  MergeSort(nums, 0, numsSize - 1);
  *returnSize = numsSize;
  return nums;
}

class Solution {
  void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> l(nums.begin() + left, nums.begin() + mid + 1);
    vector<int> r(nums.begin() + mid + 1, nums.begin() + right + 1);
    int li = 0;
    int ri = 0;
    int ll = l.size();
    int rl = r.size();
    int i = left;
    while (li < ll && ri < rl) {
      nums[i++] = l[li] < r[ri] ? l[li++] : r[ri++];
    }
    while (li < ll) {
      nums[i++] = l[li++];
    }
  }
  void MergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
      int mid = left + (right - left) / 2;
      MergeSort(nums, left, mid);
      MergeSort(nums, mid + 1, right);
      merge(nums, left, mid, right);
    }
  }

 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();
    MergeSort(nums, 0, n - 1);
    return nums;
  }
};
}  // namespace n7

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << argv[0] << " i [0 - 15]" << std::endl;
    return 0;
  }

  vector<int> v = {1, 3, 3, 2, 4, 5, 7, 4, 6, 5, 9, 8};

  int type = atoi(argv[1]);
  switch (type) {
    case 0: {
      int len;
      n1::sortArray(v.data(), v.size(), &len);
      break;
    }
    case 1: {
      n1::Solution s;
      s.sortArray(v);
      break;
    }
    case 2: {
      int len;
      n2::two::sortArray(v.data(), v.size(), &len);
      break;
    }
    case 3: {
      n2::three::Solution s;
      s.sortArray(v);
      break;
    }
    case 4: {
      int len;
      n3::sortArray(v.data(), v.size(), &len);
      break;
    }
    case 5: {
      n3::Solution s;
      s.sortArray(v);
      break;
    }
    case 6: {
      int len;
      n4::sortArray(v.data(), v.size(), &len);
      break;
    }
    case 7: {
      n4::Solution s;
      s.sortArray(v);
      break;
    }
    case 8: {
      int len;
      n5::sortArray(v.data(), v.size(), &len);
      break;
    }
    case 9: {
      n5::Solution s;
      s.sortArray(v);
      break;
    }
    case 10: {
      int len;
      n6::sortArray(v.data(), v.size(), &len);
      break;
    }
    case 11: {
      n6::Solution s;
      s.sortArray(v);
      break;
    }
    case 12: {
      int len;
      n7::sortArray(v.data(), v.size(), &len);
      break;
    }
    case 13: {
      n7::Solution s;
      s.sortArray(v);
      break;
    }
    default:
      std::cout << "invalid type" << std::endl;
      break;
  }

  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
}