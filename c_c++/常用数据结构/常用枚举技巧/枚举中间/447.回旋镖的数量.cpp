/*
给定平面上n对互不相同的点points，其中points[i] = [xi, yi]。
回旋镖是由点 (i, j, k)表示的元组，
其中i和j之间的欧式距离和i和k之间的欧式距离相等（需要考虑元组的顺序）。
返回平面上所有回旋镖的数量。

示例1：
输入：points = [[0,0],[1,0],[2,0]]
输出：2
解释：两个回旋镖为[[1,0],[0,0],[2,0]]和[[1,0],[2,0],[0,0]]

示例2：
输入：points = [[1,1],[2,2],[3,3]]
输出：2

示例3：
输入：points = [[1,1]]
输出：0


提示：
n == points.length
1 <= n <= 500
points[i].length == 2
-10^4 <= xi, yi <= 10^4
所有点都互不相同
*/

class Solution {
 public:
  int numberOfBoomerangs(vector<vector<int>>& points) {
    int ans = 0;
    unordered_map<int, int> cnt;
    for (auto& p1 : points) {
      cnt.clear();
      for (auto& p2 : points) {
        int d2 = (p1[0] - p2[0]) * (p1[0] - p2[0]) +
                 (p1[1] - p2[1]) * (p1[1] - p2[1]);
        // 以p1为中间点，以p2为任意一边的点，在加1之前看先前有多少个这个距离的点，
        // 那左端点就可以有多少个选择，又因为考虑左右顺序，
        // 所以cnt*2就是当前以p1为中间点且以p2为任意一端点可以组成的回旋镖数。
        ans += cnt[d2]++ * 2;
      }
    }
    return ans;
  }
};