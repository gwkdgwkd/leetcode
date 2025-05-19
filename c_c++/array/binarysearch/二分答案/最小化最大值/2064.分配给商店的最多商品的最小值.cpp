/*
给一个整数n，表示有n间零售商店。
总共有m种产品，每种产品的数目用一个下标从0开始的整数数组quantities表示，
其中quantities[i]表示第i种商品的数目。
需要将所有商品分配到零售商店，并遵守这些规则：
一间商店至多只能有一种商品，但一间商店拥有的商品数目可以为任意件。
分配后，每间商店都会被分配一定数目的商品（可能为0件）。
用x表示所有商店中分配商品数目的最大值，希望x越小越好。
也就是说，想最小化分配给任意商店商品数目的最大值。请返回最小的可能的x。

示例1：
输入：n = 6, quantities = [11,6]
输出：3
解释：一种最优方案为：
     11件种类为0的商品被分配到前4间商店，分配数目分别为：2，3，3，3。
     6件种类为1的商品被分配到另外2间商店，分配数目分别为：3，3。
     分配给所有商店的最大商品数目为max(2, 3, 3, 3, 3, 3) = 3。

示例2：
输入：n = 7, quantities = [15,10,10]
输出：5
解释：一种最优方案为：
     15件种类为0的商品被分配到前3间商店，分配数目为：5，5，5。
     10件种类为1的商品被分配到接下来2间商店，数目为：5，5。
     10件种类为2的商品被分配到最后2间商店，数目为：5，5。
     分配给所有商店的最大商品数目为max(5, 5, 5, 5, 5, 5, 5) = 5。

示例3：
输入：n = 1, quantities = [100000]
输出：100000
解释：唯一一种最优方案为：
     所有100000件商品0都分配到唯一的商店中。
     分配给所有商店的最大商品数目为max(100000) = 100000。


提示：
m == quantities.length
1 <= m <= n <= 105
1 <= quantities[i] <= 10^5
*/

class Solution {
 public:
  int minimizedMaximum(int n, vector<int>& quantities) {
    auto check = [&](int m) {
      int cnt = 0;
      for (int i = 0; i < quantities.size(); ++i) {
        // 每份最多有m个，quantities[i]要分成几份（不够m的，也算一份）：
        cnt += (quantities[i] - 1) / m + 1;  // 向上取整
        if (cnt > n) {
          return false;
        }
      }
      return true;
    };

    int left = 1;
    int right = *max_element(quantities.begin(), quantities.end());
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};