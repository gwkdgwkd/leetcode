/*
给一个整数数组nums和一个整数x。
每一次操作时，应当移除数组nums最左边或最右边的元素，
然后从x中减去该元素的值。
请注意，需要修改数组以供接下来的操作使用。
如果可以将x恰好减到0，返回最小操作数；否则，返回-1。

示例1：
输入：nums = [1,1,4,2,3], x = 5
输出：2
解释：最佳解决方案是移除后两个元素，将x减到0。

示例2：
输入：nums = [5,6,7,8,9], x = 4
输出：-1

示例3：
输入：nums = [3,2,20,1,1,3], x = 10
输出：5
解释：最佳解决方案是移除后三个元素和前两个元素（总共5次操作），将x减到0。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4
1 <= x <= 10^9
*/

/*
把问题转换成从nums中移除一个最长的子数组，使得剩余元素的和为x。
换句话说，要从nums中找最长的子数组，其元素和等于s−x，这里s为nums所有元素之和。
*/
class Solution {
 public:
  int minOperations(vector<int>& nums, int x) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total < x) {
      return -1;
    }
    int target = total - x;

    int n = nums.size();
    int left = 0;
    int right = 0;
    int sum = 0;
    int len = -1;  // 不能为0，target可能为0

    while (right < n) {
      sum += nums[right++];
      while (sum > target) {
        sum -= nums[left++];
      }
      if (sum == target) {
        len = max(len, right - left);
      }
    }

    return len == -1 ? -1 : n - len;
  }
};