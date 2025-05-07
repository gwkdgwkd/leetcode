/*
给一个整数数组nums，目标是令nums中的所有元素相等。
完成一次减少操作需要遵照下面的几个步骤：
找出nums中的最大值。记这个值为largest并取其下标i（下标从0开始计数）。
如果有多个元素都是最大值，则取最小的i。
找出nums中的下一个最大值，这个值严格小于largest，记为nextLargest。
将nums[i]减少到nextLargest。
返回使nums中的所有元素相等的操作次数。


示例1：
输入：nums = [5,1,3]
输出：3
解释：需要3次操作使nums中的所有元素相等：
     1.largest=5下标为0。nextLargest=3。将nums[0]减少到3。nums=[3,1,3]。
     2.largest=3下标为0。nextLargest=1。将nums[0]减少到1。nums=[1,1,3]。
     3.largest=3下标为2。nextLargest=1。将nums[2]减少到1。nums=[1,1,1]。

示例2：
输入：nums = [1,1,1]
输出：0
解释：nums中的所有元素已经是相等的。

示例3：
输入：nums = [1,1,2,2,3]
输出：4
解释：需要4次操作使nums中的所有元素相等：
     1.largest=3下标为4。nextLargest=2。将nums[4]减少到2。nums=[1,1,2,2,2]。
     2.largest=2下标为2。nextLargest=1。将nums[2]减少到1。nums=[1,1,1,2,2]。
     3.largest=2下标为3。nextLargest=1。将nums[3]减少到1。nums=[1,1,1,1,2]。
     4.largest=2下标为4。nextLargest=1。将nums[4]减少到1。nums=[1,1,1,1,1]。


提示：
1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 5 * 10^4
*/

// 分组循环
class Solution {
 public:
  int reductionOperations(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int ans = 0;
    int step = 0;
    int left = 0;
    int right = 0;
    while (right < n) {
      left = right;
      while (right < n && nums[left] == nums[right]) {
        ++right;
      }
      ans += (right - left) * step;
      ++step;
    }
    return ans;
  }
};

class Solution {
 public:
  int reductionOperations(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int res = 0;  // 总操作次数
    int cnt = 0;  // 每个元素操作次数
    for (int i = 1; i < n; ++i) {
      if (nums[i] != nums[i - 1]) {
        ++cnt;
      }
      res += cnt;
    }
    return res;
  }
};
