/*
给一个整数数组nums和一个整数target。
请统计并返回nums中能满足其最小元素与最大元素的和小于或等于target的非空子序列的数目。
由于答案可能很大，请将结果对109 + 7取余后返回。

示例1：
输入：nums = [3,5,6,7], target = 9
输出：4
解释：有4个子序列满足该条件。
     [3] -> 最小元素 + 最大元素 <= target (3 + 3 <= 9)
     [3,5] -> (3 + 5 <= 9)
     [3,5,6] -> (3 + 6 <= 9)
     [3,6] -> (3 + 6 <= 9)

示例2：
输入：nums = [3,3,6,8], target = 10
输出：6
解释：有6个子序列满足该条件。（nums 中可以有重复数字）
     [3],[3],[3,3],[3,6],[3,6],[3,3,6]

示例3：
输入：nums = [2,3,3,4,6,7], target = 12
输出：61
解释：共有63个非空子序列，其中2个不满足条件（[6,7], [7]）
     有效序列总数为（63 - 2 = 61）


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= target <= 10^6
*/

class Solution {
  const int MOD = 1e9 + 7;

 public:
  int numSubseq(vector<int>& nums, int target) {
    int size = nums.size();
    sort(nums.begin(), nums.end());  // 排序数组
    vector<int> pow2(size + 1, 1);   // 预计算2的幂

    // 预计算2的幂
    for (int i = 1; i <= size; ++i) {
      pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    int result = 0;
    int left = 0, right = size - 1;

    // 双指针遍历
    while (left <= right) {
      if (nums[left] + nums[right] <= target) {
        // 计算子序列数目并累加
        result = (result + pow2[right - left]) % MOD;
        left++;
      } else {
        right--;
      }
    }

    return result;
  }
};