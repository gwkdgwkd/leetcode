/*
在X轴上有一些奖品。给一个整数数组prizePositions，它按照非递减顺序排列，
其中prizePositions[i]是第i件奖品的位置。
数轴上一个位置可能会有多件奖品。再给你一个整数k。
可以同时选择两个端点为整数的线段。每个线段的长度都必须是k。
可以获得位置在任一线段上的所有奖品（包括线段的两个端点）。注意，两个线段可能会有相交。
比方说k = 2，可以选择线段[1, 3]和[2, 4]，
可以获得满足1<=prizePositions[i]<=3或者2<=prizePositions[i]<= 4的所有奖品i。
请返回在选择两个最优线段的前提下，可以获得的最多奖品数目。

示例1：
输入：prizePositions = [1,1,2,2,3,3,5], k = 2
输出：7
解释：这个例子中，可以选择线段[1, 3]和[3, 5]，获得7个奖品。

示例2：
输入：prizePositions = [1,2,3,4], k = 0
输出：2
解释：这个例子中，一个选择是选择线段[3, 3]和[4, 4]，获得2个奖品。


提示：
1 <= prizePositions.length <= 10^5
1 <= prizePositions[i] <= 10^9
0 <= k <= 10^9
prizePositions有序非递减。
*/

class Solution {
 public:
  int maximizeWin(vector<int>& prizePositions, int k) {
    int n = prizePositions.size();
    if (k * 2 + 1 >= prizePositions[n - 1] - prizePositions[0]) {
      return n;
    }

    int ans = 0, mx = 0, left = 0, right = 0;
    for (int mid = 0; mid < n; mid++) {
      // 把prizePositions[mid]视作第二条线段的左端点，计算第二条线段可以覆盖的最大奖品下标
      while (right < n && prizePositions[right] - prizePositions[mid] <= k) {
        right++;
      }
      // 循环结束后，right-1是第二条线段可以覆盖的最大奖品下标
      ans = max(ans, mx + right - mid);
      // 把prizePositions[mid]视作第一条线段的右端点，计算第一条线段可以覆盖的最小奖品下标
      while (prizePositions[mid] - prizePositions[left] > k) {
        left++;
      }
      // 循环结束后，left是第一条线段可以覆盖的最小奖品下标
      mx = max(mx, mid - left + 1);
    }
    return ans;
  }
};

class Solution {
 public:
  int maximizeWin(vector<int>& prizePositions, int k) {
    int n = prizePositions.size();
    if (k * 2 + 1 >= prizePositions[n - 1] - prizePositions[0]) {
      return n;
    }
    int ans = 0, left = 0;
    vector<int> mx(n + 1);
    for (int right = 0; right < n; right++) {
      while (prizePositions[right] - prizePositions[left] > k) {
        left++;
      }
      ans = max(ans, mx[left] + right - left + 1);
      mx[right + 1] = max(mx[right], right - left + 1);
    }
    return ans;
  }
};