/*
给定两个大小分别为m和n的正序（从小到大）数组nums1和nums2。
请你找出并返回这两个正序数组的中位数。
算法的时间复杂度应该为O(log(m+n))。

示例1：
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2

示例2：
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组= [1,2,3,4] ，中位数(2 + 3) / 2 = 2.5

提示：
nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/

// 归并
// 时间复杂度是：O(m+n)
// 空间复杂度是：O(m+n)
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2,
                              int nums2Size) {
  int len = nums1Size + nums2Size;
  int arr[len];
  int index = 0;

  int i = 0;
  int j = 0;
  while (i < nums1Size && j < nums2Size) {
    if (nums1[i] < nums2[j]) {
      arr[index++] = nums1[i++];
    } else {
      arr[index++] = nums2[j++];
    }
  }
  if (i == nums1Size) {
    while (j < nums2Size) {
      arr[index++] = nums2[j++];
    }
  }
  if (j == nums2Size) {
    while (i < nums1Size) {
      arr[index++] = nums1[i++];
    }
  }

  if (len % 2) {
    return arr[len / 2];
  } else {
    return ((double)(arr[len / 2] + arr[len / 2 - 1])) / 2;
  }
}

// 归并，只遍历，没有真正归并
// 时间复杂度是：O(m+n)
// 空间复杂度是：O(1)
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2,
                              int nums2Size) {
  int i = 0;
  int j = 0;

  int middleValue1 = 0;
  int middleValue2 = 0;
  int middleIndex = 0;
  int index = 0;
  double middleValue;

  middleIndex = (nums1Size + nums2Size) / 2;
  while (index <= middleIndex) {
    if ((i != nums1Size) && (j != nums2Size)) {
      if (nums1[i] <= nums2[j]) {
        middleValue1 = middleValue2;
        middleValue2 = nums1[i++];
      } else {
        middleValue1 = middleValue2;
        middleValue2 = nums2[j++];
      }
    } else if (i != nums1Size) {
      middleValue1 = middleValue2;
      middleValue2 = nums1[i++];
    } else {
      middleValue1 = middleValue2;
      middleValue2 = nums2[j++];
    }
    index++;
  }
  if ((nums1Size + nums2Size) % 2 == 1) {
    middleValue = (double)middleValue2;
  } else {
    middleValue = ((double)middleValue1 + (double)middleValue2) / 2;
  }
  return middleValue;
}

// 二分查找
// 时间复杂度：O(log⁡min⁡(m,n)))
// 空间复杂度：O(1)
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2,
                              int nums2Size) {
  if (nums1Size > nums2Size) {  // 保证nums1比nums2短
    return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
  }

  int m = nums1Size;
  int n = nums2Size;
  int left = 0, right = m;
  int median1 = 0;  // median1：前一部分的最大值
  int median2 = 0;  // median2：后一部分的最小值

  while (left <= right) {
    // 前一部分包含nums1[0 .. i-1]和nums2[0 .. j-1]
    // 后一部分包含nums1[i .. m-1]和nums2[j .. n-1]
    int i = (left + right) / 2;
    int j = (m + n + 1) / 2 - i;

    // nums_im1,nums_i,nums_jm1,nums_j分别表示nums1[i-1],nums1[i],nums2[j-1],nums2[j]
    int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);
    int nums_i = (i == m ? INT_MAX : nums1[i]);
    int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
    int nums_j = (j == n ? INT_MAX : nums2[j]);

    if (nums_im1 <= nums_j) {
      median1 = fmax(nums_im1, nums_jm1);
      median2 = fmin(nums_i, nums_j);
      left = i + 1;
    } else {
      right = i - 1;
    }
  }

  return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
}