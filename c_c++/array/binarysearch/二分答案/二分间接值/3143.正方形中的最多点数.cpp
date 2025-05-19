/*
给一个二维数组points和一个字符串s，其中points[i]表示第i个点的坐标，s[i]表示第i个点的标签。
如果一个正方形的中心在(0,0)，所有边都平行于坐标轴，
且正方形内不存在标签相同的两个点，那么我们称这个正方形是合法的。
请返回合法正方形中可以包含的最多点数。
注意：如果一个点位于正方形的边上或者在边以内，则认为该点位于正方形内。正方形的边长可以为零。

示例1：
输入：points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
输出：2
解释：边长为4的正方形包含两个点points[0]和points[1]。

示例2：
输入：points = [[1,1],[-2,-2],[-2,2]], s = "abb"
输出：1
解释：边长为2的正方形包含1个点points[0]。

示例3：
输入：points = [[1,1],[-1,-1],[2,-2]], s = "ccd"
输出：0
解释：任何正方形都无法只包含points[0]和points[1]中的一个点，所以合法正方形中都不包含任何点。


提示：
1 <= s.length, points.length <= 10^5
points[i].length == 2
-10^9 <= points[i][0], points[i][1] <= 10^9
s.length == points.length
points 中的点坐标互不相同。
s只包含小写英文字母。
*/

// 二分间接值，二分的不是答案，而是一个和答案有关的值（间接值）。
class Solution {
 public:
  int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
    int n = points.size();
    auto check = [&](int l) {
      int hash[26]{};
      for (int i = 0; i < n; ++i) {
        if (abs(points[i][0]) <= l && abs(points[i][1]) <= l) {
          if (++hash[s[i] - 'a'] > 1) {
            return false;
          }
        }
      }
      return true;
    };

    int left = 0;
    int right = 1'000'000'001;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (abs(points[i][0]) <= right && abs(points[i][1]) <= right) {
        ++ans;
      }
    }
    return ans;
  }
};

// 维护次小距离的最小值
class Solution {
 public:
  int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
    int min_d[26], min2 = INT_MAX;
    ranges::fill(min_d, INT_MAX);
    for (int i = 0; i < points.size(); i++) {
      int d = max(abs(points[i][0]), abs(points[i][1]));
      char c = s[i] - 'a';
      if (d < min_d[c]) {
        // d是目前最小的，那么min_d[c]是次小的
        min2 = min(min2, min_d[c]);
        min_d[c] = d;
      } else {
        // d可能是次小的
        min2 = min(min2, d);
      }
    }
    int ans = 0;
    for (int d : min_d) {
      ans += d < min2;
    }
    return ans;
  }
};
