/*
给两个整数数组nums1和nums2，它们已经按非降序排序，请你返回两个数组的最小公共整数。
如果两个数组nums1和nums2没有公共整数，请你返回-1。
如果一个整数在两个数组中都至少出现一次，那么这个整数是数组nums1和nums2公共的。

示例1：
输入：nums1 = [1,2,3], nums2 = [2,4]
输出：2
解释：两个数组的最小公共元素是2，所以我们返回2。

示例2：
输入：nums1 = [1,2,3,6], nums2 = [2,3,4,5]
输出：2
解释：两个数组中的公共元素是2和3，2是较小值，所以返回2。


提示：
1 <= nums1.length, nums2.length <= 10^5
1 <= nums1[i], nums2[j] <= 10^9
nums1和nums2都是非降序的。
*/

class Solution {
 public:
  int getCommon(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    int i1 = 0;
    int i2 = 0;

    while (i1 < n1 && i2 < n2) {
      if (nums1[i1] > nums2[i2]) {
        ++i2;
      } else if (nums1[i1] < nums2[i2]) {
        ++i1;
      } else {
        return nums1[i1];
      }
    }
    return -1;
  }
};