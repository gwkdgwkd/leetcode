/*
给一组多米诺骨牌dominoes。
形式上，dominoes[i] = [a, b]与dominoes[j] = [c, d]等价，
当且仅当(a == c且b == d)或者(a == d且b == c)。
即一张骨牌可以通过旋转0度或180度得到另一张多米诺骨牌。
在0 <= i < j < dominoes.length的前提下，
找出满足dominoes[i]和dominoes[j]等价的骨牌对(i, j)的数量。

示例1：
输入：dominoes = [[1,2],[2,1],[3,4],[5,6]]
输出：1

示例2：
输入：dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
输出：3


提示：
1 <= dominoes.length <= 4 * 10^4
dominoes[i].length == 2
1 <= dominoes[i][j] <= 9
*/

// 暴力法，超时
class Solution {
 public:
  int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    int n = dominoes.size();
    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if ((dominoes[i][0] == dominoes[j][0] &&
             dominoes[i][1] == dominoes[j][1]) ||
            (dominoes[i][0] == dominoes[j][1] &&
             dominoes[i][1] == dominoes[j][0])) {
          ++ans;
        }
      }
    }
    return ans;
  }
};

class Solution {
 public:
  int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    int n = dominoes.size();
    int ans = 0;
    int cnt[100]{};
    for (int i = 0; i < n; ++i) {
      int t;
      if (dominoes[i][0] < dominoes[i][1]) {
        t = dominoes[i][0] * 10 + dominoes[i][1];
      } else {
        t = dominoes[i][1] * 10 + dominoes[i][0];
      }
      ans += cnt[t];  // 当前的dominoes与cnt中的每个都可以组成一对
      cnt[t]++;
    }

    return ans;
  }
};