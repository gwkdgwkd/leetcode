/*
给一个下标从0开始、长度为n的整数数组nums，以及整数indexDifference和整数valueDifference。
任务是从范围[0, n - 1]内找出2个满足下述所有条件的下标i和j：
abs(i-j)>=indexDifference且abs(nums[i]-nums[j])>=valueDifference
返回整数数组answer。
如果存在满足题目要求的两个下标，则answer=[i,j]；否则，answer=[-1,-1]。
如果存在多组可供选择的下标对，只需要返回其中任意一组即可。
注意：i和j可能相等。

示例1：
输入：nums = [5,1,4,1], indexDifference = 2, valueDifference = 4
输出：[0,3]
解释：在示例中，可以选择i = 0和j = 3。
     abs(0 - 3) >= 2且abs(nums[0] - nums[3]) >= 4。
     因此，[0,3]是一个符合题目要求的答案。
     [3,0]也是符合题目要求的答案。

示例2：
输入：nums = [2,1], indexDifference = 0, valueDifference = 0
输出：[0,0]
解释：在示例中，可以选择i = 0和j = 0。
     abs(0 - 0) >= 0且abs(nums[0] - nums[0]) >= 0。
     因此，[0,0]是一个符合题目要求的答案。
     [0,1]、[1,0]和[1,1]也是符合题目要求的答案。

示例3：
输入：nums = [1,2,3], indexDifference = 2, valueDifference = 4
输出：[-1,-1]
解释：在示例中，可以证明无法找出2个满足所有条件的下标。
     因此，返回[-1,-1]。


提示：
1 <= n == nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= indexDifference <= 10^5
0 <= valueDifference <= 10^9
*/

class Solution {
 public:
  vector<int> findIndices(vector<int> &nums, int indexDifference,
                          int valueDifference) {
    int max_idx = 0, min_idx = 0;
    for (int j = indexDifference; j < nums.size(); j++) {
      int i = j - indexDifference;
      if (nums[i] > nums[max_idx]) {
        max_idx = i;
      } else if (nums[i] < nums[min_idx]) {
        min_idx = i;
      }
      if (nums[max_idx] - nums[j] >= valueDifference) {
        return {max_idx, j};
      }
      if (nums[j] - nums[min_idx] >= valueDifference) {
        return {min_idx, j};
      }
    }
    return {-1, -1};
  }
};