/*
在代号为C-137的地球上，Rick发现如果他将两个球放在他新发明的篮子里，
它们之间会形成特殊形式的磁力。
Rick有n个空的篮子，第i个篮子的位置在position[i]，
Morty想把m个球放到这些篮子里，使得任意两球间最小磁力最大。
已知两个球如果分别位于x和y，那么它们之间的磁力为|x - y|。
给一个整数数组position和一个整数m，请返回最大化的最小磁力。

示例1：
输入：position = [1,2,3,4,7], m = 3
输出：3
解释：将3个球分别放入位于1，4和7的三个篮子，两球间的磁力分别为[3, 3, 6]。
     最小磁力为3。我们没办法让最小磁力大于3。

示例2：
输入：position = [5,4,3,2,1,1000000000], m = 2
输出：999999999
解释：我们使用位于1和1000000000的篮子时最小磁力最大。


提示：
n == position.length
2 <= n <= 10^5
1 <= position[i] <= 10^9
所有position中的整数互不相同。
2 <= m <= position.length
*/

// 同[2517.礼盒的最大甜蜜度]

class Solution {
 public:
  int maxDistance(vector<int>& position, int m) {
    int n = position.size();
    sort(position.begin(), position.end());

    auto check = [&](int d) {
      int cnt = 1;
      int pre = position[0];
      for (int i = 1; i < n; ++i) {
        if (position[i] - pre >= d) {
          pre = position[i];
          ++cnt;
        }
      }
      return cnt >= m;
    };

    int left = 0;
    int right = position[n - 1] - position[0];
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