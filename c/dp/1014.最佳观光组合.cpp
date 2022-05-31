/*
给你一个正整数数组values，其中values[i]表示第i个观光景点的评分，并且两个景点i和j之间的距离为j-i。
一对景点（i < j）组成的观光组合的得分为values[i] + values[j] + i - j，
也就是景点的评分之和减去它们两者之间的距离。
返回一对观光景点能取得的最高分。

示例1：
输入：values = [8,1,5,2,6]
输出：11
解释：i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11

示例2：
输入：values = [1,2]
输出：2

提示：
2 <= values.length <= 5 * 10^4
1 <= values[i] <= 1000
*/

// 遍历，超出时间限制
int maxScoreSightseeingPair(int* values, int valuesSize) {
  int max = 0;
  for (int i = 0; i < valuesSize; ++i) {
    for (int j = i + 1; j < valuesSize; ++j) {
      max = fmax(max, values[i] + values[j] + i - j);
    }
  }

  return max;
}

// 官方题解
int maxScoreSightseeingPair(int* values, int valuesSize) {
  int ans = 0, mx = values[0] + 0;
  for (int j = 1; j < valuesSize; ++j) {
    ans = fmax(ans, mx + values[j] - j);
    // 边遍历边维护
    mx = fmax(mx, values[j] + j);
  }
  return ans;
}

class Solution {
 public:
  int maxScoreSightseeingPair(vector<int>& values) {
    int ans = 0, mx = values[0] + 0;
    for (int j = 1; j < values.size(); ++j) {
      ans = max(ans, mx + values[j] - j);
      // 边遍历边维护
      mx = max(mx, values[j] + j);
    }
    return ans;
  }
};
