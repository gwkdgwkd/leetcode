/*
 * @lc app=leetcode.cn id=1014 lang=c
 *
 * [1014] 最佳观光组合
 */

// @lc code=start

/*
// 遍历，超出时间限制
int maxScoreSightseeingPair(int* values, int valuesSize){
    int max = 0;
    for(int i = 0; i < valuesSize; ++i) {
        for(int j = i + 1; j < valuesSize; ++j) {
            max = fmax(max, values[i] + values[j] + i - j);
        }
    }

    return max;
}
*/

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

// @lc code=end
