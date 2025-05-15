/*
在探险营地间，小扣意外发现了一片城墙遗迹，在探索期间，却不巧遇到迁徙中的兽群向他迎面冲来。
情急之下小扣吹响了他的苍蓝笛，随着笛声响起，遗迹中的城墙逐渐发生了横向膨胀。
已知rampart[i]=[x,y]表示第i段城墙的初始所在区间。
当城墙发生膨胀时，将遵循以下规则：
所有的城墙会同时膨胀相等的长度；
每个城墙可以向左、向右或向两个方向膨胀。
小扣为了确保自身的安全，需要在所有城墙均无重叠的情况下，让城墙尽可能的膨胀。
请返回城墙可以膨胀的最大值。
注意：
初始情况下，所有城墙均不重叠，且rampart中的元素升序排列；
两侧的城墙可以向外无限膨胀。

示例1：
输入：rampart = [[0,3],[4,5],[7,9]]
输出：3
解释：rampart[0]向左侧膨胀3个单位；
     rampart[2]向右侧膨胀3个单位；
     rampart[1] 向左侧膨胀1个单位，向右膨胀2个单位。
     不存在膨胀更多的方案，返回3。

示例2：
输入：rampart = [[1,2],[5,8],[11,15],[18,25]]
输出：4


提示：
3 <= rampart.length <= 10^4
rampart[i].length == 2
0 <= rampart[i][0] < rampart[i][1] <= rampart[i+1][0] <= 10^8
*/

class Solution {
 public:
  int rampartDefensiveLine(vector<vector<int>>& rampart) {
    int n = rampart.size();
    auto check = [&](int m) -> bool {
      int pre_r = INT_MIN / 2;
      for (int i = 0; i + 1 < n; i++) {
        int l = rampart[i][0], r = rampart[i][1];
        int space = m - (l - pre_r);  // 向左膨胀后的剩余长度
        if (space > 0) {
          r += space;                   // 向右膨胀
          if (r > rampart[i + 1][0]) {  // 无法膨胀
            return false;
          }
        }
        pre_r = r;
      }
      return true;
    };

    int s = 0;
    for (int i = 0; i + 1 < n; i++) {
      s += rampart[i + 1][0] - rampart[i][1];
    }

    int left = 0, right = s / (n - 2) + 1;
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      (check(mid) ? left : right) = mid;
    }
    return left;
  }
};
