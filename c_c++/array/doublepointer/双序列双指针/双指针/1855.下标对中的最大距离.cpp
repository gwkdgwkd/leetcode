/*
给两个非递增的整数数组nums1​​​​​​和nums2​​​​​​，数组下标均从0开始计数。
下标对(i, j)中0 <= i < nums1.length且0 <= j < nums2.length。
如果该下标对同时满足i <= j且nums1[i] <= nums2[j]，则称之为有效下标对，
该下标对的距离为j - i​​。​​
返回所有有效下标对(i, j)中的最大距离。如果不存在有效下标对，返回0。
一个数组arr，如果每个1 <= i < arr.length均有arr[i-1] >= arr[i]成立，
那么该数组是一个非递增数组。

示例1：
输入：nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
输出：2
解释：有效下标对是(0,0),(2,2),(2,3),(2,4),(3,3),(3,4)和(4,4)。
     最大距离是2，对应下标对(2,4) 。

示例2：
输入：nums1 = [2,2,2], nums2 = [10,10,1]
输出：1
解释：有效下标对是(0,0),(0,1)和(1,1)。
     最大距离是1，对应下标对(0,1)。

示例3：
输入：nums1 = [30,29,19,5], nums2 = [25,25,25,25,25]
输出：2
解释：有效下标对是(2,2),(2,3),(2,4),(3,3)和(3,4)。
     最大距离是2，对应下标对(2,4)。


提示：
1 <= nums1.length <= 10^5
1 <= nums2.length <= 10^5
1 <= nums1[i], nums2[j] <= 10^5
nums1和nums2都是非递增数组
*/

// 暴力法，超时
class Solution {
 public:
  int maxDistance(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < m; ++j) {
        if (nums1[i] <= nums2[j]) {
          ans = max(ans, j - i);
        }
      }
    }
    return ans;
  }
};

// 双指针，超时，为什么？
class Solution {
 public:
  int maxDistance(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int j = m - 1;
      while (j >= i && nums1[i] > nums2[j]) {
        --j;
      }
      ans = max(ans, j - i);
    }
    return ans;
  }
};

/* 双指针
遍历nums2​中的下标j，同时寻找此时符合要求的nums1​中最小的下标i。
假设下标j对应的最小下标为i，当j变为j+1时，由于nums2​非递增，
即nums2​[j]≥nums2​[j+1]，那么nums1​中可取元素的上界不会增加。
同时由于nums1​也非递增，因此j+1对应的最小下标i′一定满足i′≥i。
那么就可以在遍历j的同时维护对应的i，并用res来维护下标对(i,j)的最大距离。
将res初值置为0，这样即使存在nums1​[i]≤nums2​[j]但i>j这种不符合要求的情况，
由于此时距离为负因而不会对结果产生影响（不存在时也返回0）。
另外，在维护最大距离的时候要注意下标i的合法性，即i<n1​，其中n1​为nums1​的长度。
*/
class Solution {
 public:
  int maxDistance(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    int i = 0;
    int res = 0;
    for (int j = 0; j < n2; ++j) {
      while (i < n1 && nums1[i] > nums2[j]) {
        ++i;
      }
      if (i < n1) {
        res = max(res, j - i);
      }
    }
    return res;
  }
};