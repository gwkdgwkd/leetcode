/*
给一个下标从0开始的正整数数组nums和一个正整数limit。
在一次操作中，可以选择任意两个下标i和j，
如果满足|nums[i]-nums[j]|<=limit，则交换nums[i]和nums[j]。
返回执行任意次操作后能得到的字典序最小的数组。
如果在数组a和数组b第一个不同的位置上，
数组a中的对应元素比数组b中的对应元素的字典序更小，则认为数组a就比数组b字典序更小。
例如，数组[2,10,3]比数组[10,2,3]字典序更小，下标0处是两个数组第一个不同的位置，且2<10。

示例1：
输入：nums = [1,5,3,9,8], limit = 2
输出：[1,3,5,8,9]
解释：执行2次操作：
     交换nums[1]和nums[2]。数组变为[1,3,5,9,8]。
     交换nums[3]和nums[4]。数组变为[1,3,5,8,9]。
     即便执行更多次操作，也无法得到字典序更小的数组。
     注意，执行不同的操作也可能会得到相同的结果。

示例2：
输入：nums = [1,7,6,18,2,1], limit = 3
输出：[1,6,7,18,1,2]
解释：执行3次操作：
     交换nums[1]和nums[2]。数组变为[1,6,7,18,2,1]。
     交换nums[0]和nums[4]。数组变为[2,6,7,18,1,1]。
     交换nums[0]和nums[5]。数组变为[1,6,7,18,1,2]。
     即便执行更多次操作，也无法得到字典序更小的数组。

示例3：
输入：nums = [1,7,28,19,10], limit = 3
输出：[1,7,28,19,10]
解释：[1,7,28,19,10]是字典序最小的数组，因为不管怎么选择下标都无法执行操作。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= limit <= 10^9
*/

// 排序+分组循环
class Solution {
 public:
  vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit) {
    int n = nums.size();
    vector<int> ids(n);
    iota(ids.begin(), ids.end(), 0);
    sort(ids.begin(), ids.end(),
         [&](int i, int j) { return nums[i] < nums[j]; });

    vector<int> ans(n);
    for (int i = 0; i < n;) {
      int st = i;
      for (i++; i < n && nums[ids[i]] - nums[ids[i - 1]] <= limit; i++)
        ;
      vector<int> subIds(ids.begin() + st, ids.begin() + i);
      sort(subIds.begin(), subIds.end());
      for (int j = 0; j < subIds.size(); j++) {
        ans[subIds[j]] = nums[ids[st + j]];
      }
    }
    return ans;
  }
};
