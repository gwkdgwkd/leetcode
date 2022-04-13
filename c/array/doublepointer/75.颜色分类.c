/*
给定一个包含红色、白色和蓝色、共n个元素的数组nums，原地对它们进行排序，
使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
我们使用整数0、1和2分别表示红色、白色和蓝色。
必须在不使用库的sort函数的情况下解决这个问题。

示例1：
输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]

示例2：
输入：nums = [2,0,1]
输出：[0,1,2]

提示：
n == nums.length
1 <= n <= 300
nums[i]为 0、1或2

进阶：
你可以不使用代码库中的排序函数来解决这道题吗？
你能想出一个仅使用常数空间的一趟扫描算法吗？
*/

void swap(int *a, int *b) {
  int t = *a;
  *a = *b, *b = t;
}
void sortColors(int *nums, int numsSize) {
  int ptr = 0;
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] == 0) {
      swap(&nums[i], &nums[ptr]);
      ++ptr;
    }
  }
  for (int i = ptr; i < numsSize; ++i) {
    if (nums[i] == 1) {
      swap(&nums[i], &nums[ptr]);
      ++ptr;
    }
  }
}

// 双指针？是不是三指针
void sortColors(int *nums, int numsSize) {
  int left = 0;
  int right = numsSize - 1;

  for (int mid = 0; mid < numsSize; ++mid) {
    while (mid < right && nums[mid] == 2) {
      int tmp = nums[mid];
      nums[mid] = nums[right];
      nums[right] = tmp;
      --right;
    }
    if (nums[mid] == 0) {
      int tmp = nums[mid];
      nums[mid] = nums[left];
      nums[left] = tmp;
      ++left;
    }
  }
}