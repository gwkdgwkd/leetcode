/*
给定一个包含红色、白色和蓝色、共n个元素的数组nums，
原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
使用整数0、1和2分别表示红色、白色和蓝色。
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
可以不使用代码库中的排序函数来解决这道题吗？
你能想出一个仅使用常数空间的一趟扫描算法吗？
*/

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
void sortColors(int *nums, int numsSize) {  // 这是三指针么？
  int left = 0;
  int right = numsSize - 1;

  while (right >= 0 && nums[right] == 2) {
    --right;
  }
  while (left < numsSize && nums[left] == 0) {
    ++left;
  }

  for (int mid = left; mid <= right; ++mid) {
    while (mid < right && nums[mid] == 2) {
      swap(&nums[mid], &nums[right]);
      --right;
    }
    if (nums[mid] == 0) {
      swap(&nums[mid], &nums[left]);
      ++left;
    }
  }
}

class Solution {
 public:
  void sortColors(vector<int> &nums) {
    int len = nums.size();
    int left = 0;
    int right = len - 1;

    while (left < len && nums[left] == 0) {
      ++left;
    }
    while (right > 0 && nums[right] == 2) {
      --right;
    }

    for (int mid = left; mid <= right; ++mid) {
      while (mid < right && nums[mid] == 2) {
        swap(nums[mid], nums[right]);
        --right;
      }
      if (nums[mid] == 0) {
        swap(nums[mid], nums[left]);
        ++left;
      }
    }
  }
};

/* 插入排序

技巧：O(1)插入元素
假设现在有一个有序数组a=[0,0,1,1,2,2]。
在a中插入一个0，同时保证a是有序的，会怎么做？
最暴力的想法是，把0插在数组的最左边，原来的元素全体右移一位，得到[0,0,0,1,1,2,2]。
这样做是O(n)的。
实际上，可以狸猫换太子：不是插入元素，而是修改元素！
对比一下插入前后：
插入前[0,0,1,1,2,2]。
插入后[0,0,0,1,1,2,2]。
竖着看，其实只有3个位置变了：
原来的a[2]变成0。
原来的a[4]变成1。
末尾新增一个2，相当于a[6]=2。

怎么知道要修改的位置（下标）？
维护0的个数，即为改成0的位置，记作p0​。上例中p0​=2。把a[p0​]改成0。
维护0和1的个数，即为改成1的位置，记作p1​。上例中p1​=4。把a[p1​]改成1。
末尾新增的位置记作i，把a[i]改成2。
*/
class Solution {
 public:
  void sortColors(vector<int> &nums) {
    int p0 = 0, p1 = 0;
    for (int i = 0; i < nums.size(); i++) {
      int x = nums[i];
      nums[i] = 2;
      if (x <= 1) {
        nums[p1++] = 1;
      }
      if (x == 0) {
        nums[p0++] = 0;
      }
    }
  }
};