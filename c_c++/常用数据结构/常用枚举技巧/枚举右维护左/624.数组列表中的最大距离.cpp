/*
给定m个数组，每个数组都已经按照升序排好序了。
现在需要从两个不同的数组中选择两个整数（每个数组选一个）并且计算它们的距离。
两个整数a和b之间的距离定义为它们差的绝对值|a-b|。
返回最大距离。

示例1：
输入：[[1,2,3],[4,5],[1,2,3]]
输出：4
解释：一种得到答案4的方法是从第一个数组或者第三个数组中选择1，同时从第二个数组中选择5。

示例2：
输入：arrays = [[1],[1]]
输出：0


提示：
m == arrays.length
2 <= m <= 10^5
1 <= arrays[i].length <= 500
-10^4 <= arrays[i][j] <= 10^4
arrays[i]以升序排序。
所有数组中最多有10^5个整数。
*/

class Solution {
 public:
  int maxDistance(vector<vector<int>>& arrays) {
    int ans = 0;
    int mx = INT_MIN / 2;  // 防止减法溢出
    int mn = INT_MAX / 2;
    for (auto a : arrays) {
      int tmp = max(a.back() - mn, mx - a.front());
      ans = max(ans, tmp);  // 防止最大最小在同一组
      mx = max(mx, a.back());
      mn = min(mn, a.front());
    }
    return ans;
  }
};