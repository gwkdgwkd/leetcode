/*
给两个由正整数和0组成的数组nums1和nums2。
必须将两个数组中的所有0替换为严格正整数，并且满足两个数组中所有元素的和相等。
返回最小相等和，如果无法使两数组相等，则返回-1。

示例1：
输入：nums1 = [3,2,0,1,0], nums2 = [6,5,0]
输出：12
解释：可以按下述方式替换数组中的0：
     用2和4替换nums1中的两个0。得到nums1 = [3,2,2,1,4]。
     用1替换nums2中的一个0。得到nums2 = [6,5,1]。
     两个数组的元素和相等，都等于12。可以证明这是可以获得的最小相等和。

示例2：
输入：nums1 = [2,0,2,0], nums2 = [1,4]
输出：-1
解释：无法使两个数组的和相等。


提示：
1 <= nums1.length, nums2.length <= 10^5
0 <= nums1[i], nums2[i] <= 10^6
*/

class Solution {
 public:
  long long minSum(vector<int>& nums1, vector<int>& nums2) {
    long sum1 = 0;
    long sum2 = 0;
    int c1 = 0;
    int c2 = 0;
    for (int num : nums1) {
      if (num == 0) {
        ++c1;
      } else {
        sum1 += num;
      }
    }
    for (int num : nums2) {
      if (num == 0) {
        ++c2;
      } else {
        sum2 += num;
      }
    }

    if (sum1 + c1 > sum2 + c2) {
      swap(sum1, sum2);
      swap(c1, c2);
    }
    sum2 += c2;
    if ((sum2 > sum1 && c1 == 0) || sum2 < sum1 + c1) {
      return -1;
    }
    return sum2;
  }
};

// 分类讨论
class Solution {
 public:
  long long minSum(vector<int>& nums1, vector<int>& nums2) {
    long long sum1 = 0, sum2 = 0;
    long long zero1 = 0, zero2 = 0;
    for (int i : nums1) {
      sum1 += i;
      if (i == 0) {
        sum1++;
        zero1++;
      }
    }
    for (int i : nums2) {
      sum2 += i;
      if (i == 0) {
        sum2++;
        zero2++;
      }
    }
    if (!zero1 && sum2 > sum1 || !zero2 && sum1 > sum2) {
      return -1;
    }
    return max(sum1, sum2);
  }
};