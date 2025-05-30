/*
两个按非递减顺序排列的整数数组nums1和nums2，另有两个整数m和n，表示nums1和nums2的元素数目。
请你合并nums2到nums1中，使合并后的数组同样按非递减顺序排列。
注意：最终合并后数组不应由函数返回，而是存储在数组nums1中。
nums1的初始长度为m+n，其中前m个元素表示应合并的元素，后n个元素为0，应忽略，nums2的长度为n。

示例1：
输入：nums1 = [1,2,3,0,0,0], m = 3,
     nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并[1,2,3]和[2,5,6]。
合并结果是[1,2,2,3,5,6]，其中斜体加粗标注的为nums1中的元素。

示例2：
输入：nums1 = [1]，m = 1，nums2 = []，n = 0
输出：[1]
解释：需要合并[1]和[]。
合并结果是[1]。

示例3：
输入：nums1 = [0]， m = 0，nums2 = [1]，n = 1
输出：[1]
解释：需要合并的数组是[]和[1]。
合并结果是[1]。
注意，因为m = 0，所以nums1中没有元素。
nums1中仅存的0仅仅是为了确保合并结果可以顺利存放到nums1中。

提示：
nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-10^9 <= nums1[i], nums2[j] <= 10^9

进阶：可以设计实现一个时间复杂度为O(m+n)的算法解决此问题吗？
*/

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
  int i = 0;
  int j = 0;
  int arr[m + n];
  int cur = 0;
  while (i < m && j < n) {
    arr[cur++] = (nums1[i] <= nums2[j] ? nums1[i++] : nums2[j++]);
  }

  while (i < m) {
    arr[cur++] = nums1[i++];
  }
  while (j < n) {
    arr[cur++] = nums2[j++];
  }

  memcpy(nums1, arr, (m + n) * sizeof(int));
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
  int i = 0;
  int j = 0;
  int tmp[m + n];
  int k = 0;

  while (i < m || j < n) {
    if (i == m) {
      tmp[k++] = nums2[j++];
    } else if (j == n) {
      tmp[k++] = nums1[i++];
    } else {
      if (nums1[i] <= nums2[j]) {
        tmp[k++] = nums1[i++];
      } else {
        tmp[k++] = nums2[j++];
      }
    }
  }
  memcpy(nums1, tmp, sizeof(int) * (m + n));
}

// 面试题1001合并排序的数组
// 给定两个排序后的数组A和B，其中A的末端有足够的缓冲空间容纳B。
// 编写一个方法，将B合并入A并排序，初始化A和B的元素数量分别为m和n。
void merge(int* A, int ASize, int m, int* B, int BSize, int n) {
  int ia = m - 1;
  int ib = n - 1;
  int i = ASize - 1;

  while (ia >= 0 || ib >= 0) {
    if (ia < 0) {
      A[i--] = B[ib--];
    } else if (ib < 0) {
      A[i--] = A[ia--];
    } else {
      if (A[ia] >= B[ib]) {
        A[i--] = A[ia--];
      } else {
        A[i--] = B[ib--];
      }
    }
  }
}

int cmp(int* a, int* b) { return *a - *b; }
void merge(int* A, int ASize, int m, int* B, int BSize, int n) {
  memcpy(A + m, B, sizeof(int) * n);
  qsort(A, ASize, sizeof(int), cmp);
}

// 直接合并后排序
class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    for (int i = 0; i != n; ++i) {
      nums1[m + i] = nums2[i];
    }
    sort(nums1.begin(), nums1.end());
  }
};

// 双指针
class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = 0, p2 = 0;
    int sorted[m + n];
    int cur;
    while (p1 < m || p2 < n) {
      if (p1 == m) {
        cur = nums2[p2++];
      } else if (p2 == n) {
        cur = nums1[p1++];
      } else if (nums1[p1] < nums2[p2]) {
        cur = nums1[p1++];
      } else {
        cur = nums2[p2++];
      }
      sorted[p1 + p2 - 1] = cur;
    }
    for (int i = 0; i != m + n; ++i) {
      nums1[i] = sorted[i];
    }
  }
};

// 逆向双指针
class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = m - 1, p2 = n - 1;
    int tail = m + n - 1;
    int cur;
    while (p1 >= 0 || p2 >= 0) {
      if (p1 == -1) {
        cur = nums2[p2--];
      } else if (p2 == -1) {
        cur = nums1[p1--];
      } else if (nums1[p1] > nums2[p2]) {
        cur = nums1[p1--];
      } else {
        cur = nums2[p2--];
      }
      nums1[tail--] = cur;
    }
  }
};

class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i1 = 0;
    int i2 = 0;
    vector<int> ans(m + n);
    int i = 0;
    while (i1 < m && i2 < n) {
      if (nums1[i1] <= nums2[i2]) {
        ans[i++] = nums1[i1++];
      } else {
        ans[i++] = nums2[i2++];
      }
    }
    while (i1 < m) {
      ans[i++] = nums1[i1++];
    }
    while (i2 < n) {
      ans[i++] = nums2[i2++];
    }
    nums1 = ans;
  }
};
