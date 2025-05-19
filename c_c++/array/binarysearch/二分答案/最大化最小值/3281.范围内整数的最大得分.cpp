/*
给一个整数数组start和一个整数d，代表n个区间[start[i], start[i] + d]。
需要选择n个整数，其中第i个整数必须属于第i个区间。
所选整数的得分定义为所选整数两两之间的最小绝对差。
返回所选整数的最大可能得分。

示例1：
输入：start = [6,0,3], d = 2
输出：4
解释：可以选择整数8, 0和4获得最大可能得分，得分为min(|8-0|,|8-4|,|0-4|)，等于4。

示例2：
输入：start = [2,6,13,13], d = 5
输出：5
解释：可以选择整数2,7,13和18获得最大可能得分，
     得分为min(|2-7|,|2-13|,|2-18|,|7-13|,|7-18|,|13-18|)，等于5。

提示：
2 <= start.length <= 10^5
0 <= start[i] <= 10^9
0 <= d <= 10^9
*/

class Solution {
 public:
  int maxPossibleScore(vector<int>& start, int d) {
    sort(start.begin(), start.end());
    int n = start.size();

    auto check = [&](int score) -> bool {
      long long x = LLONG_MIN;
      for (int s : start) {
        x = max(x + score, (long long)s);
        if (x > s + d) {
          return false;
        }
      }
      return true;
    };

    int left = 1;
    int right = (start[n - 1] + d - start[0]) / (n - 1) + 1;
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