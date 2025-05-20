/*
给两个从小到大排好序且下标从0开始的整数数组nums1和nums2以及一个整数k，
请你返回第k（从1开始编号）小的nums1[i]*nums2[j]的乘积，
其中0 <= i < nums1.length且0 <= j < nums2.length。

示例1：
输入：nums1 = [2,5], nums2 = [3,4], k = 2
输出：8
解释：第2小的乘积计算如下：
     nums1[0] * nums2[0] = 2 * 3 = 6
     nums1[0] * nums2[1] = 2 * 4 = 8
     第2小的乘积为8。

示例2：
输入：nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
输出：0
解释：第6小的乘积计算如下：
     nums1[0] * nums2[1] = (-4) * 4 = -16
     nums1[0] * nums2[0] = (-4) * 2 = -8
     nums1[1] * nums2[1] = (-2) * 4 = -8
     nums1[1] * nums2[0] = (-2) * 2 = -4
     nums1[2] * nums2[0] = 0 * 2 = 0
     nums1[2] * nums2[1] = 0 * 4 = 0
     第6小的乘积为0。

示例3：
输入：nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
输出：-6
解释：第3小的乘积计算如下：
     nums1[0] * nums2[4] = (-2) * 5 = -10
     nums1[0] * nums2[3] = (-2) * 4 = -8
     nums1[4] * nums2[0] = 2 * (-3) = -6
     第3小的乘积为-6。


提示：
1 <= nums1.length, nums2.length <= 5 * 10^4
-10^5 <= nums1[i], nums2[j] <= 10^5
1 <= k <= nums1.length * nums2.length
nums1和nums2都是从小到大排好序的。
*/

typedef long long LL;
const int N = 2e5 + 10, offset = 1e5;
class Solution {
 private:
  int cnt1[N];  // 小于等于某个数的个数
  int cnt2[N];  // 大于等于某个数的个数

 public:
  // 计算乘积小于等于m的数字
  // m < 0   u < 0  找大于等于m / u的数字总个数 上取整
  // m < 0   u > 0  找小于等于m / u的数字总个数 下取整
  // m > 0   u < 0  找大于等于m / u的数字总个数
  // m > 0   u > 0  找小于等于m / u的数字总个数
  // m > 0   u = 0  所有数

  bool check(vector<int>& v, LL m, LL k) {
    LL res = 0;
    for (int i = 0; i < v.size(); i++) {
      int u = v[i];
      if (u == 0) {
        if (m >= 0) res += cnt1[offset * 2];
        continue;
      }

      LL t = m / u + offset;
      if (m < 0) {
        if (u > 0)
          t = floor((double)m / u) + offset;
        else
          t = ceil((double)m / u) + offset;
      }

      LL a, b;
      if (t >= offset * 2)
        a = cnt1[offset * 2], b = 0;
      else if (t < 0)
        a = 0, b = cnt1[offset * 2];
      else
        a = cnt1[t], b = cnt2[t];

      if (m < 0) {
        if (u < 0) res += b;
        if (u > 0) res += a;
      } else {
        if (u > 0) res += a;
        if (u < 0) res += b;
      }
    }

    return res >= k;
  }

  long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2,
                               long long k) {
    for (auto c : nums2) cnt1[c + offset]++, cnt2[c + offset]++;
    for (int i = 1; i <= offset * 2; i++) cnt1[i] += cnt1[i - 1];
    for (int i = 2 * offset; i >= 0; i--) cnt2[i] += cnt2[i + 1];
    LL l = -1e10, r = 1e10;
    while (l <= r) {
      LL mid = (l + r) / 2;
      if (check(nums1, mid, k)) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }

    return l;
  }
};