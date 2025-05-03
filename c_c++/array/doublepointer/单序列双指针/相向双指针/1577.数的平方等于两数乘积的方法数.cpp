/*
给两个整数数组nums1和nums2，请返回根据以下规则形成的三元组的数目（类型1和类型2）：
类型1：三元组(i,j,k)，
如果nums1[i]2==nums2[j]*nums2[k]其中0<=i<nums1.length且0<=j<k<nums2.length
类型2：三元组(i,j,k)，
如果nums2[i]2==nums1[j]*nums1[k]其中0<=i<nums2.length且0<=j<k<nums1.length

示例1：
输入：nums1 = [7,4], nums2 = [5,2,8,9]
输出：1
解释：类型1：(1,1,2),nums1[1]^2 = nums2[1] * nums2[2](4^2 = 2 * 8)

示例2：
输入：nums1 = [1,1], nums2 = [1,1,1]
输出：9
解释：所有三元组都符合题目要求，因为 1^2 = 1 * 1
     类型1：(0,0,1),(0,0,2),(0,1,2),(1,0,1),(1,0,2),(1,1,2),
           nums1[i]^2 = nums2[j] * nums2[k]
     类型2：(0,0,1),(1,0,1),(2,0,1),nums2[i]^2 = nums1[j] * nums1[k]

示例3：
输入：nums1 = [7,7,8,3], nums2 = [1,2,9,7]
输出：2
解释：有两个符合题目要求的三元组
     类型1：(3,0,2),nums1[3]^2 = nums2[0] * nums2[2]
     类型2：(3,0,1),nums2[3]^2 = nums1[0] * nums1[1]

示例4：
输入：nums1 = [4,7,9,11,23], nums2 = [3,5,1024,12,18]
输出：0
解释：不存在符合题目要求的三元组

提示：
1 <= nums1.length, nums2.length <= 1000
1 <= nums1[i], nums2[i] <= 10^5
*/

class Solution {
 public:
  int numTriplets(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());

    auto count = [](vector<int>& v1, vector<int>& v2) {
      int n1 = v1.size();
      int n2 = v2.size();
      int ans = 0;
      for (int i = 0; i < n1; ++i) {
        long long target = v1[i] * (long long)v1[i];
        int left = 0;
        int right = n2 - 1;
        while (left < right) {
          long long s = v2[left] * (long long)v2[right];
          if (s < target) {
            ++left;
          } else if (s > target) {
            --right;
          } else {
            if (v2[left] == v2[right]) {
              ans += (right - left + 1) * (right - left) / 2;
              break;
            } else {
              int t1 = 0, t2 = 0;
              int l = v2[left], r = v2[right];
              while (l == v2[left]) {
                ++t1;
                ++left;
              }
              while (r == v2[right]) {
                ++t2;
                --right;
              }
              ans += t1 * t2;
            }
          }
        }
      }
      return ans;
    };

    return count(nums1, nums2) + count(nums2, nums1);
  }
};