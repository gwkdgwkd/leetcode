/*
有两个有序且数组内元素互不相同的数组nums1和nums2。
一条合法路径定义如下：
选择数组nums1或者nums2开始遍历（从下标0处开始）。
从左到右遍历当前数组。
如果遇到了nums1和nums2中都存在的值，
那么可以切换路径到另一个数组对应数字处继续遍历（但在合法路径中重复数字只会被统计一次）。
得分定义为合法路径中不同数字的和。
请返回所有可能合法路径中的最大得分。
由于答案可能很大，请将它对10^9+7取余后返回。

示例1：
输入：nums1 = [2,4,5,8,10], nums2 = [4,6,8,9]
输出：30
解释：合法路径包括：
     [2,4,5,8,10],[2,4,5,8,9],[2,4,6,8,9],[2,4,6,8,10],（从nums1开始遍历）
     [4,6,8,9],[4,5,8,10],[4,5,8,9],[4,6,8,10]，（从nums2开始遍历）
     最大得分为上图中的绿色路径[2,4,6,8,10]。

示例2：
输入：nums1 = [1,3,5,7,9], nums2 = [3,5,100]
输出：109
解释：最大得分由路径[1,3,5,100]得到。

示例3：
输入：nums1 = [1,2,3,4,5], nums2 = [6,7,8,9,10]
输出：40
解释：nums1和nums2之间无相同数字，最大得分由路径[6,7,8,9,10]得到。


提示：
1 <= nums1.length, nums2.length <= 10^5
1 <= nums1[i], nums2[i] <= 10^7
nums1和nums2都是严格递增的数组。
*/

// 相交点可以将2个数组都分成(K+1)段，统计每段的和，
// 并取较大值计入结果，可以用双指针快速实现。
class Solution {
 public:
  int maxSum(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    long sum1 = 0;
    long sum2 = 0;
    long ans = 0;

    int i1 = 0;
    int i2 = 0;
    while (i1 < n1 && i2 < n2) {
      if (nums1[i1] < nums2[i2]) {
        sum1 += nums1[i1++];
      } else if (nums1[i1] > nums2[i2]) {
        sum2 += nums2[i2++];
      } else {
        ans += max(sum1, sum2) + nums1[i1];
        sum1 = sum2 = 0;
        ++i1;
        ++i2;
      }
    }

    while (i1 < n1) {
      sum1 += nums1[i1++];
    }
    while (i2 < n2) {
      sum2 += nums2[i2++];
    }
    ans += max(sum1, sum2);
    return ans % ((int)pow(10, 9) + 7);
  }
};

// 动态规划
class Solution {
 private:
  static constexpr int mod = 1000000007;

 public:
  int maxSum(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    long long best1 = 0, best2 = 0;
    int i = 0, j = 0;
    while (i < m || j < n) {
      if (i < m && j < n) {
        if (nums1[i] < nums2[j]) {
          best1 += nums1[i];
          ++i;
        } else if (nums1[i] > nums2[j]) {
          best2 += nums2[j];
          ++j;
        } else {
          long long best = max(best1, best2) + nums1[i];
          best1 = best2 = best;
          ++i;
          ++j;
        }
      } else if (i < m) {
        best1 += nums1[i];
        ++i;
      } else if (j < n) {
        best2 += nums2[j];
        ++j;
      }
    }
    return max(best1, best2) % mod;
  }
};