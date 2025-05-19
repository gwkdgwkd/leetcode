/*
给两个整数m和n。构造一个mxn的网格，其中每个单元格最开始是白色。
请用红、绿、蓝三种颜色为每个单元格涂色。所有单元格都需要被涂色。
涂色方案需要满足：不存在相邻两个单元格颜色相同的情况。返回网格涂色的方法数。
因为答案可能非常大， 返回对10^9+7取余的结果。

示例1：
输入：m = 1, n = 1
输出：3
解释：如上图所示，存在三种可能的涂色方案。

示例2：
输入：m = 1, n = 2
输出：6
解释：如上图所示，存在六种可能的涂色方案。

示例3：
输入：m = 5, n = 5
输出：580986


提示：
1 <= m <= 5
1 <= n <= 1000
*/

class Solution {
 private:
  static constexpr int mod = 1000000007;

 public:
  int colorTheGrid(int m, int n) {
    // 哈希映射valid存储所有满足要求的对一行进行涂色的方案
    // 键表示mask，值表示mask的三进制串（以列表的形式存储）
    unordered_map<int, vector<int>> valid;

    // 在[0, 3^m)范围内枚举满足要求的mask
    int mask_end = pow(3, m);
    for (int mask = 0; mask < mask_end; ++mask) {
      vector<int> color;
      int mm = mask;
      for (int i = 0; i < m; ++i) {
        color.push_back(mm % 3);
        mm /= 3;
      }
      bool check = true;
      for (int i = 0; i < m - 1; ++i) {
        if (color[i] == color[i + 1]) {
          check = false;
          break;
        }
      }
      if (check) {
        valid[mask] = move(color);
      }
    }

    // 预处理所有的(mask1, mask2)二元组，满足mask1和mask2作为相邻行时，
    // 同一列上两个格子的颜色不同
    unordered_map<int, vector<int>> adjacent;
    for (const auto& [mask1, color1] : valid) {
      for (const auto& [mask2, color2] : valid) {
        bool check = true;
        for (int i = 0; i < m; ++i) {
          if (color1[i] == color2[i]) {
            check = false;
            break;
          }
        }
        if (check) {
          adjacent[mask1].push_back(mask2);
        }
      }
    }

    vector<int> f(mask_end);
    for (const auto& [mask, _] : valid) {
      f[mask] = 1;
    }
    for (int i = 1; i < n; ++i) {
      vector<int> g(mask_end);
      for (const auto& [mask2, _] : valid) {
        for (int mask1 : adjacent[mask2]) {
          g[mask2] += f[mask1];
          if (g[mask2] >= mod) {
            g[mask2] -= mod;
          }
        }
      }
      f = move(g);
    }

    int ans = 0;
    for (int num : f) {
      ans += num;
      if (ans >= mod) {
        ans -= mod;
      }
    }
    return ans;
  }
};
