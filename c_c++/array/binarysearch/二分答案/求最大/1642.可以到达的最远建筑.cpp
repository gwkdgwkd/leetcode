/*
给一个整数数组heights，表示建筑物的高度。另有一些砖块bricks和梯子ladders。
从建筑物0开始旅程，不断向后面的建筑物移动，期间可能会用到砖块或梯子。
当从建筑物i移动到建筑物i+1（下标从0开始）时：
如果当前建筑物的高度大于或等于下一建筑物的高度，则不需要梯子或砖块；
如果当前建筑的高度小于下一个建筑的高度，可以使用一架梯子或(h[i+1]-h[i])个砖块
如果以最佳方式使用给定的梯子和砖块，返回可以到达的最远建筑物的下标（下标从0开始）。

示例1：
输入：heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
输出：4
解释：从建筑物0出发，可以按此方案完成旅程：
     不使用砖块或梯子到达建筑物1，因为4 >= 2
     使用5个砖块到达建筑物2。必须使用砖块或梯子，因为2 < 7
     不使用砖块或梯子到达建筑物3，因为7 >= 6
     使用唯一的梯子到达建筑物4。
     必须使用砖块或梯子，因为6 < 9无法越过建筑物4，因为没有更多砖块或梯子。

示例2：
输入：heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
输出：7

示例3：
输入：heights = [14,3,19,3], bricks = 17, ladders = 0
输出：3


提示：
1 <= heights.length <= 10^5
1 <= heights[i] <= 10^6
0 <= bricks <= 10^9
0 <= ladders <= heights.length
*/

// 二分答案
class Solution {
 public:
  int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    int n = heights.size();
    vector<int> diff(n, 0);
    for (int i = 1; i < n; ++i) {
      if (heights[i] > heights[i - 1]) {
        diff[i] = heights[i] - heights[i - 1];
      }
    }
    auto check = [&](int index) {
      int l = ladders;
      vector<int> d(diff.begin(), diff.begin() + index + 1);
      sort(d.begin(), d.end());
      int cnt = 0;
      for (int i = d.size() - 1; i >= 0; --i) {
        if (l-- > 0) {
          continue;
        }
        cnt += d[i];
      }
      return cnt <= bricks;
    };

    int left = 1;
    int right = heights.size() - 1;  // 没有减一，导致错误
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};

// 反悔堆