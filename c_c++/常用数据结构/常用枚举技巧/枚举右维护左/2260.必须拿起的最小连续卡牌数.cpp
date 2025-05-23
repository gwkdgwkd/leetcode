/*
给一个整数数组cards，其中cards[i]表示第i张卡牌的值。
如果两张卡牌的值相同，则认为这一对卡牌匹配。
返回必须拿起的最小连续卡牌数，以使在拿起的卡牌中有一对匹配的卡牌。
如果无法得到一对匹配的卡牌，返回-1。

示例1：
输入：cards = [3,4,2,3,4,7]
输出：4
解释：拿起卡牌[3,4,2,3]将会包含一对值为3的匹配卡牌。
     注意，拿起[4,2,3,4]也是最优方案。

示例2：
输入：cards = [1,0,5,3]
输出：-1
解释：无法找出含一对匹配卡牌的一组连续卡牌。


提示：
1 <= cards.length <= 10^5
0 <= cards[i] <= 10^6
*/

class Solution {
 public:
  int minimumCardPickup(vector<int>& cards) {
    int n = cards.size();
    unordered_map<int, int> pos;
    int ans = n + 1;
    for (int i = 0; i < n; ++i) {
      if (pos.find(cards[i]) != pos.end()) {
        ans = min(ans, i - pos[cards[i]] + 1);
      }
      pos[cards[i]] = i;
    }
    return ans == n + 1 ? -1 : ans;
  }
};
