/*
输入一个正整数target，输出所有和为target的连续正整数序列（至少含有两个数）。
序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

示例1：
输入：target = 9
输出：[[2,3,4],[4,5]]

示例2：
输入：target = 15
输出：[[1,2,3,4,5],[4,5,6],[7,8]]

限制：1 <= target <= 10^5
*/

// 双指针，移动过程好像滑动窗口
int **findContinuousSequence(int target, int *returnSize,
                             int **returnColumnSizes) {
  *returnSize = 0;
  int **res = (int **)malloc(sizeof(int *) * 5000);
  *returnColumnSizes = (int *)malloc(sizeof(int) * 5000);

  int left = 1;
  int right = 1;
  int sum = 0;
  while (left <= target / 2) {
    if (sum < target) {
      sum += right;
      ++right;
    } else if (sum > target) {
      sum -= left;
      ++left;
    } else {
      int len = right - left;
      (*returnColumnSizes)[*returnSize] = len;
      res[*returnSize] = (int *)malloc(sizeof(int) * len);
      for (int i = 0; i < len; ++i) {
        res[*returnSize][i] = left + i;
      }
      (*returnSize)++;
      sum -= left;
      ++left;
    }
  }
  return res;
}

class Solution {
 public:
  vector<vector<int>> findContinuousSequence(int target) {
    int left = 1;
    int right = 1;
    int sum = 0;

    vector<vector<int>> res;
    while (left <= target / 2) {
      if (sum < target) {
        sum += right++;
      } else if (sum > target) {
        sum -= left++;
      } else {
        int len = right - left;
        vector<int> v(len);
        for (int i = 0; i < len; ++i) {
          v[i] = i + left;
        }
        res.emplace_back(v);
        sum -= left++;
      }
    }

    return res;
  }
};