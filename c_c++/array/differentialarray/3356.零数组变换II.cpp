/*
给一个长度为n的整数数组nums和一个二维数组queries，其中queries[i]=[li,ri,vali]。
每个queries[i]表示在nums上执行以下操作：
将nums中[li,ri]范围内的每个下标对应元素的值最多减少vali。
每个下标的减少的数值可以独立选择。
零数组是指所有元素都等于0的数组。
返回k可以取到的最小非负值，使得在顺序处理前k个查询后，nums变成零数组。
如果不存在这样的k，则返回-1。

示例1：
输入：nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
输出：2
解释：对于i = 0（l = 0, r = 2, val = 1）：
        在下标[0, 1, 2]处分别减少[1, 0, 1]。
        数组将变为[1, 0, 1]。
     对于i = 1（l = 0, r = 2, val = 1）：
        在下标[0, 1, 2]处分别减少[1, 0, 1]。
        数组将变为[0, 0, 0]，这是一个零数组。因此，k的最小值为2。

示例2：
输入：nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
输出：-1
解释：对于i = 0（l = 1, r = 3, val = 2）：
        在下标[1, 2, 3]处分别减少[2, 2, 1]。
        数组将变为[4, 1, 0, 0]。
     对于i = 1（l = 0, r = 2, val = 1）：
        在下标[0, 1, 2]处分别减少[1, 1, 0]。
        数组将变为[3, 0, 0, 0]，这不是一个零数组。


提示：
1 <= nums.length <= 10^5
0 <= nums[i] <= 5 * 10^5
1 <= queries.length <= 10^5
queries[i].length == 3
0 <= li <= ri < nums.length
1 <= vali <= 5
*/

// 二分答案+差分数组
class Solution {
  // 问题变成：能否用前k个询问（下标从0到k−1）把nums的所有元素都变成≤0？

 public:
  int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    int m = queries.size();

    auto check = [&](int k) -> bool {
      vector<int> diff(n + 1, 0);
      for (int i = 0; i < k; ++i) {
        diff[queries[i][0]] += queries[i][2];
        diff[queries[i][1] + 1] -= queries[i][2];
      }

      int sum = 0;
      for (int i = 0; i < n; ++i) {
        sum += diff[i];       // sum就是k次操作后，能减少的最大值
        if (nums[i] > sum) {  // 表示nums[i]k次操作后，不能变成0
          return false;
        }
      }
      return true;
    };

    int left = 0;
    int right = m;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left <= m ? left : -1;

    // int left = -1, right = m + 1;
    // while (left + 1 < right) {
    //     int mid = (left + right) / 2;
    //     (check(mid) ? right : left) = mid;
    // }
    // return right <= m ? right : -1;
  }
};

// Lazy 线段树

// 双指针+差分数组