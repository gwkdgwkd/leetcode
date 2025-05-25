/*
给一个n个节点的无向图，节点编号为0到n - 1。
给一个下标从0开始的整数数组scores，其中scores[i]是第i个节点的分数。
同时给一个二维整数数组edges，其中edges[i]=[ai,bi]，表示节点ai和bi之间有一条无向边。
一个合法的节点序列如果满足以下条件，我们称它是合法的：
序列中每相邻节点之间有边相连。
序列中没有节点出现超过一次。
节点序列的分数定义为序列中节点分数之和 。
请返回一个长度为4的合法节点序列的最大分数。如果不存在这样的序列，请返回-1。

示例1：
输入：scores = [5,2,9,8,4], edges = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
输出：24
解释：上图为输入的图，节点序列为[0,1,2,3]。
     节点序列的分数为5 + 2 + 9 + 8 = 24。
     观察可知，没有其他节点序列得分和超过24。
     注意节点序列[3,1,2,0]和[1,0,2,3]也是合法的，且分数为24。
     序列[0,3,2,4]不是合法的，因为没有边连接节点0和3。

示例2：
输入：scores = [9,20,6,4,11,12], edges = [[0,3],[5,3],[2,4],[1,3]]
输出：-1
解释：上图为输入的图。没有长度为4的合法序列，所以我们返回-1。


提示：
n == scores.length
4 <= n <= 5 * 10^4
1 <= scores[i] <= 10^8
0 <= edges.length <= 5 * 10^4
edges[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
不会有重边。
*/

class Solution {
 public:
  int maximumScore(vector<int> &scores, vector<vector<int>> &edges) {
    int n = scores.size();
    vector<vector<pair<int, int>>> g(n);
    for (auto &e : edges) {
      int x = e[0], y = e[1];
      // -scores[y]是为了方便排序，不用写自定义的比较函数
      g[x].emplace_back(-scores[y], y);
      g[y].emplace_back(-scores[x], x);
    }

    for (auto &vs : g)
      if (vs.size() > 3) {
        nth_element(vs.begin(), vs.begin() + 3, vs.end());
        vs.resize(3);
      }

    int ans = -1;
    for (auto &e : edges) {
      int x = e[0], y = e[1];
      for (auto &[score_a, a] : g[x])
        for (auto &[score_b, b] : g[y])
          if (a != y && b != x && a != b)
            ans = max(ans, -score_a + scores[x] + scores[y] - score_b);
    }

    return ans;
  }
};