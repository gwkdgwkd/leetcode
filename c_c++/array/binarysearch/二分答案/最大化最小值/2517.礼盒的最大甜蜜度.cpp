/*
给一个正整数数组price，其中price[i]表示第i类糖果的价格，另给你一个正整数k。
商店组合k类不同糖果打包成礼盒出售。礼盒的甜蜜度是礼盒中任意两种糖果价格绝对差的最小值。
返回礼盒的最大甜蜜度。

示例1：
输入：price = [13,5,1,8,21,2], k = 3
输出：8
解释：选出价格分别为[13,5,21]的三类糖果。
     礼盒的甜蜜度为min(|13 - 5|,|13 - 21|,|5 - 21|) = min(8, 8, 16) = 8。
     可以证明能够取得的最大甜蜜度就是8。

示例2：
输入：price = [1,3,1], k = 2
输出：2
解释：选出价格分别为[1,3]的两类糖果。
     礼盒的甜蜜度为 min(|1 - 3|) = min(2) = 2。
     可以证明能够取得的最大甜蜜度就是2。

示例3：
输入：price = [7,7,7,7], k = 2
输出：0
解释：从现有的糖果中任选两类糖果，甜蜜度都会是0。


提示：
2 <= k <= price.length <= 10^5
1 <= price[i] <= 10^9
*/

class Solution {
 public:
  int maximumTastiness(vector<int>& price, int k) {
    int n = price.size();
    sort(price.begin(), price.end());

    auto check = [&](int diff) -> bool {
      int cnt = 0;
      int prev = INT_MIN >> 1;
      for (int i = 0; i < n; ++i) {
        if (price[i] - prev >= diff) {
          ++cnt;
          prev = price[i];
        }
      }
      return cnt >= k;
    };

    int left = 0;
    int right = price[n - 1] - price[0];
    // int right = (price[n - 1] - price[0]) / (k - 1);
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

class Solution {
 public:
  int maximumTastiness(vector<int>& price, int k) {
    int n = price.size();
    sort(price.begin(), price.end());
    int left = 0, right = price[n - 1] - price[0];
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (check(price, k, mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left;
  }

  bool check(const vector<int>& price, int k, int tastiness) {
    int prev = INT_MIN >> 1;
    int cnt = 0;
    for (int p : price) {
      if (p - prev >= tastiness) {
        cnt++;
        prev = p;
      }
    }
    return cnt >= k;
  }
};
