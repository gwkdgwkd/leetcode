/*
给一个由n个整数组成的数组nums，请找出k的最大值，
使得存在两个相邻且长度为k的严格递增。
具体来说，需要检查是否存在从下标a和b(a<b)开始的两个子数组，并满足下述全部条件：
这两个子数组nums[a..a+k-1]和nums[b..b+k-1]都是严格递增的。
这两个子数组必须是相邻的，即b = a + k。
返回k的最大可能值。
子数组是数组中的一个连续非空的元素序列。

示例1：
输入：nums = [2,5,7,8,9,2,3,4,3,1]
输出：3
解释：从下标2开始的子数组是[7, 8, 9]，它是严格递增的。
     从下标5开始的子数组是[2, 3, 4]，它也是严格递增的。
     这两个子数组是相邻的，因此3是满足题目条件的最大k值。

示例2：
输入：nums = [1,2,3,4,4,4,4,5,6,7]
输出：2
解释：从下标0开始的子数组是[1, 2]，它是严格递增的。
     从下标2开始的子数组是[3, 4]，它也是严格递增的。
     这两个子数组是相邻的，因此2是满足题目条件的最大k值。


提示：
2 <= nums.length <= 2 * 10^5
-10^9 <= nums[i] <= 10^9
*/

class Solution {
 public:
  int maxIncreasingSubarrays(vector<int>& nums) {
    int ans = 0;
    int pre_cnt = 0;
    int cnt = 0;
    for (int i = 0; i < nums.size(); ++i) {
      ++cnt;
      if (i == nums.size() - 1 || nums[i] >= nums[i + 1]) {
        // 答案有两种情况：
        // 两个子数组属于同一个严格递增段，那么k最大是cnt​/2。
        // 两个子数组分别属于一对相邻的严格递增段，那么k最大是min(preCnt,cnt)。
        ans = max(ans, max(cnt / 2, min(pre_cnt, cnt)));
        // ans = max({ans, cnt/2, min(pre_cnt, cnt)});
        pre_cnt = cnt;
        cnt = 0;
      }
    }
    return ans;
  }
};