/*
假设是一家合金制造公司的老板，公司使用多种金属来制造合金。
现在共有n种不同类型的金属可以使用，并且可以使用k台机器来制造合金。
每台机器都需要特定数量的每种金属来创建合金。
对于第i台机器而言，创建合金需要composition[i][j]份j类型金属。
最初，拥有stock[i]份i类型金属，而每购入一份i类型金属需要花费cost[i]的金钱。
给整数n、k、budget，下标从1开始的二维数组composition，
两个下标从1开始的数组stock和cost，请在预算不超过budget金钱的前提下，最大化公司制造合金的数量。
所有合金都需要由同一台机器制造。返回公司可以制造的最大合金数。

示例1：
输入：n = 3, k = 2, budget = 15,
     composition = [[1,1,1],[1,1,10]], stock = [0,0,0], cost = [1,2,3]
输出：2
解释：最优的方法是使用第1台机器来制造合金。
     要想制造2份合金，我们需要购买：
     2份第1类金属。
     2份第2类金属。
     2份第3类金属。
     总共需要2 * 1 + 2 * 2 + 2 * 3 = 12的金钱，小于等于预算15。
     注意，我们最开始时候没有任何一类金属，所以必须买齐所有需要的金属。
     可以证明在示例条件下最多可以制造2份合金。

示例2：
输入：n = 3, k = 2, budget = 15,
     composition = [[1,1,1],[1,1,10]], stock = [0,0,100], cost = [1,2,3]
输出：5
解释：最优的方法是使用第2台机器来制造合金。
     要想制造5份合金，我们需要购买：
     5份第1类金属。
     5份第2类金属。
     0份第3类金属。
     总共需要5 * 1 + 5 * 2 + 0 * 3 = 15的金钱，小于等于预算15。
     可以证明在示例条件下最多可以制造5份合金。

示例3：

输入：n = 2, k = 3, budget = 10,
     composition = [[2,1],[1,2],[1,1]], stock = [1,1], cost = [5,5]
输出：2
解释：最优的方法是使用第3台机器来制造合金。
     要想制造2份合金，我们需要购买：
     1份第1类金属。
     1份第2类金属。
     总共需要1 * 5 + 1 * 5 = 10的金钱，小于等于预算10。
     可以证明在示例条件下最多可以制造2份合金。


提示：
1 <= n, k <= 100
0 <= budget <= 10^8
composition.length == k
composition[i].length == n
1 <= composition[i][j] <= 100
stock.length == cost.length == n
0 <= stock[i] <= 10^8
1 <= cost[i] <= 100
*/

class Solution {
 public:
  int maxNumberOfAlloys(int n, int, int budget,
                        vector<vector<int>>& composition, vector<int>& stock,
                        vector<int>& cost) {
    int ans = 0;
    int mx = ranges::min(stock) + budget;
    for (auto& comp : composition) {
      auto check = [&](long long num) -> bool {
        long long money = 0;
        for (int i = 0; i < n; i++) {
          if (stock[i] < comp[i] * num) {
            money += (comp[i] * num - stock[i]) * cost[i];
            if (money > budget) {
              return false;
            }
          }
        }

        return true;
      };

      int left = ans, right = mx + 1;
      while (left + 1 < right) {  // 开区间写法
        int mid = left + (right - left) / 2;
        (check(mid) ? left : right) = mid;
      }
      ans = left;
    }

    return ans;
  }
};

class Solution {
 public:
  int maxNumberOfAlloys(int n, int k, int budget,
                        vector<vector<int>>& composition, vector<int>& stock,
                        vector<int>& cost) {
    int left = 1, right = 2e8, ans = 0;
    while (left <= right) {
      int mid = (left + right) / 2;
      bool valid = false;
      for (int i = 0; i < k; ++i) {
        long long spend = 0;
        for (int j = 0; j < n; ++j) {
          spend +=
              max(static_cast<long long>(composition[i][j]) * mid - stock[j],
                  0LL) *
              cost[j];
        }
        if (spend <= budget) {
          valid = true;
          break;
        }
      }
      if (valid) {
        ans = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return ans;
  }
};

class Solution {
 public:
  int maxNumberOfAlloys(int n, int k, int budget,
                        vector<vector<int>>& composition, vector<int>& stock,
                        vector<int>& cost) {
    auto check = [&](int cnt) {
      for (int i = 0; i < k; ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
          sum += max(static_cast<long long>(composition[i][j]) * cnt - stock[j],
                     0LL) *
                 cost[j];
        }
        if (sum <= budget) {
          return true;
        }
      }
      return false;
    };

    int left = 1;
    int right = *min_element(stock.begin(), stock.end()) + budget;
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