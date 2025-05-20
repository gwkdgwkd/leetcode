/*
给定一个长度为n的整数数组nums和一个二维数组queries，其中queries[i]=[li,ri]。
对于每个查询queries[i]：
在nums的下标范围[li,ri]内选择一个下标。
将选中的每个下标对应的元素值减1。
零数组是指所有元素都等于0的数组。
如果在按顺序处理所有查询后，可以将nums转换为零数组，则返回true，否则返回false。

示例1：
输入：nums = [1,0,1], queries = [[0,2]]
输出：true
解释：对于i = 0：
     选择下标子集[0, 2]并将这些下标处的值减1。
     数组将变为[0, 0, 0]，这是一个零数组。

示例2：
输入：nums = [4,3,2,1], queries = [[1,3],[0,2]]
输出：false
解释：对于i = 0：
        选择下标子集[1, 2, 3]并将这些下标处的值减1。
        数组将变为[4, 2, 1, 0]。
     对于i = 1：
        选择下标子集[0, 1, 2]并将这些下标处的值减1。
        数组将变为[3, 1, 0, 0]，这不是一个零数组。


提示：
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
1 <= queries.length <= 10^5
queries[i].length == 2
0 <= li <= ri < nums.length
*/

// 暴力，超时
class Solution {
 public:
  bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    int m = queries.size();
    for (int i = 0; i < m; ++i) {
      for (int j = queries[i][0]; j <= queries[i][1]; ++j) {
        nums[j]--;
      }
    }
    for (int i = 0; i < n; ++i) {
      if (nums[i] > 0) {
        return false;
      }
    }
    return true;
  }
};

class Solution {
 public:
  bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    int m = queries.size();
    vector<int> diff(n + 1);
    for (auto& q : queries) {
      diff[q[0]]++;
      diff[q[1] + 1]--;
    }

    int sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += diff[i];
      if (nums[i] > sum) {
        return false;
      }
    }
    return true;
  }
};