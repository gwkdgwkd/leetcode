/*
有一些球形气球贴在一堵用XY平面表示的墙面上。
墙面上的气球记录在整数数组points，
其中points[i]=[xstart,xend]表示水平直径在xstart和xend之间的气球。
你不知道气球的确切y坐标。
一支弓箭可以沿着x轴从不同点完全垂直地射出。
在坐标x处射出一支箭，若有一个气球的直径的开始和结束坐标为xstart，xend，
且满足xstart ≤ x ≤ xend，则该气球会被引爆。
可以射出的弓箭的数量没有限制。弓箭一旦被射出之后，可以无限地前进。
给你一个数组points，返回引爆所有气球所必须射出的最小弓箭数。

示例1：
输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用2支箭来爆破:
在x = 6处射出箭，击破气球[2,8]和[1,6]。
在x = 11处发射箭，击破气球[10,16]和[7,12]。

示例2：
输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要4支箭。

示例3：
输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
在x = 2处发射箭，击破气球[1,2]和[2,3]。
在x = 4处射出箭，击破气球[3,4]和[4,5]。

提示:
1 <= points.length <= 10^5
points[i].length == 2
-2^31 <= xstart < xend <= 2^31 - 1
*/

// 贪心算法
int cmp(const void *a, const void *b) {
  // [[-2147483646,-2147483645],[2147483646,2147483647]],signed integer overflow
  // return (*(int **)a)[0] - (*(int **)b)[0];
  return ((*((int **)a))[0] > (*((int **)b))[0]);
}
int findMinArrowShots(int **points, int pointsSize, int *pointsColSize) {
  if (pointsSize == 0) return 0;
  qsort(points, pointsSize, sizeof(int *), cmp);

  int res = 1;
  for (int i = 1; i < pointsSize; ++i) {
    if (points[i][0] > points[i - 1][1]) {
      ++res;
    } else {
      points[i][1] = fmin(points[i][1], points[i - 1][1]);
    }
  }

  return res;
}

// 贪心算法，写法与435类似
int cmp(const void *a, const void *b) {
  return ((*((int **)a))[1] > (*((int **)b))[1]);
}
int findMinArrowShots(int **points, int pointsSize, int *pointsColSize) {
  if (pointsSize == 0) return 0;
  qsort(points, pointsSize, sizeof(int *), cmp);

  int count = 1;           // 记录非交叉区间的个数
  int end = points[0][1];  // 记录区间分割点
  for (int i = 1; i < pointsSize; ++i) {
    // [1,2]和[2,3]算重叠，所以使用<：
    if (end < points[i][0]) {
      end = points[i][1];
      ++count;
    }
  }

  return count;
}

class Solution {
 public:
  int findMinArrowShots(vector<vector<int>> &points) {
    sort(points.begin(), points.end(),
         [](const auto &x, const auto &y) { return x[1] < y[1]; });

    int count = 1;
    int right = points[0][1];
    for (int i = 1; i < points.size(); ++i) {
      if (right < points[i][0]) {
        ++count;
        right = points[i][1];
      }
    }

    return count;
  }
};