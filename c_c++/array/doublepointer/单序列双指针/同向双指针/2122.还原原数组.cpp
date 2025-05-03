/*
Alice有一个下标从0开始的数组arr，由n个正整数组成。
她会选择一个任意的正整数k并按下述方式创建两个下标从0开始的新整数数组lower和higher：
对每个满足0 <= i < n的下标i，lower[i] = arr[i] - k
对每个满足0 <= i < n的下标i，higher[i] = arr[i] + k
不幸地是，Alice丢失了全部三个数组。
但是，她记住了在数组lower和higher中出现的整数，但不知道每个整数属于哪个数组。
请帮助Alice还原原数组。
给你一个由2n个整数组成的整数数组nums，其中恰好n个整数出现在lower，
剩下的出现在higher，还原并返回原数组arr。如果出现答案不唯一的情况，返回任一有效数组。
注意：生成的测试用例保证存在至少一个有效数组arr。

示例1：
输入：nums = [2,10,6,4,8,12]
输出：[3,7,11]
解释：如果arr = [3,7,11]且k = 1，那么lower = [2,6,10]且higher = [4,8,12]。
     组合lower和higher得到[2,6,10,4,8,12]，这是nums的一个排列。
     另一个有效的数组是arr = [5,7,9]且k = 3。
     在这种情况下，lower = [2,4,6]且higher = [8,10,12]。

示例2：
输入：nums = [1,1,3,3]
输出：[2,2]
解释：如果arr = [2,2]且k = 1，那么lower = [1,1]且higher = [3,3] 。
     组合lower和higher得到[1,1,3,3]，这是nums的一个排列。
     注意，数组不能是[1,3]，因为在这种情况下，获得[1,1,3,3]唯一可行的方案是k=0。
     这种方案是无效的，k必须是一个正整数。

示例3：
输入：nums = [5,435]
输出：[220]
解释：唯一可行的组合是arr = [220]且k = 215。
     在这种情况下，lower = [5]且higher = [435]。


提示：
2 * n == nums.length
1 <= n <= 1000
1 <= nums[i] <= 10^9
生成的测试用例保证存在至少一个有效数组arr
*/

class Solution {
 public:
  vector<int> recoverArray(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();

    // 当arr有序时，最小的那个元素arr[0]一定是属于lower的
    for (int i = 0; i < n; ++i) {
      if (nums[i] == nums[0] || (nums[i] - nums[0]) % 2) {
        continue;
      }

      vector<int> used(n);
      used[0] = used[i] = true;
      int k = (nums[i] - nums[0]) / 2;
      vector<int> ans;
      ans.push_back(nums[0] + k);

      int left = 0;
      int right = i;
      for (int j = 2; j + j <= n; ++j) {
        while (used[left]) {
          ++left;
        }
        while (right < n &&
               (used[right] || nums[right] - nums[left] != k * 2)) {
          ++right;
        }
        if (right == n) {
          break;
        }
        ans.push_back(nums[left] + k);
        used[left] = used[right] = true;
      }
      if (ans.size() == n / 2) {
        return ans;
      }
    }
    return {};
  }
};