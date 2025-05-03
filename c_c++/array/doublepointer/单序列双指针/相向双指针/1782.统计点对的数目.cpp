/*
给一个无向图，无向图由整数n，表示图中节点的数目，和edges组成，
其中edges[i] = [ui, vi]表示ui和vi之间有一条无向边。
同时给你一个代表查询的整数数组queries。
第j个查询的答案是满足如下条件的点对(a, b)的数目：
a < b
cnt是与a或者b相连的边的数目，且cnt严格大于queries[j]。

请返回一个数组answers，
其中answers.length == queries.length且answers[j]是第j个查询的答案。
请注意，图中可能会有多重边。

示例1：
输入：n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
输出：[6,5]
解释：每个点对中，与至少一个点相连的边的数目如上图所示。
     answers[0] = 6。所有的点对(a,b)中边数和都大于2，故有6个；
     answers[1] = 5。所有的点对(a,b)中除了(3,4)边数等于3，
     其它点对边数和都大于3，故有5个。

示例2：
输入：n = 5,
     edges = [[1,5],[1,5],[3,4],[2,5],[1,3],[5,1],[2,3],[2,5]],
     queries = [1,2,3,4,5]
输出：[10,10,9,8,6]


提示：
2 <= n <= 2 * 10^4
1 <= edges.length <= 10^5
1 <= ui, vi <= n
ui != vi
1 <= queries.length <= 20
0 <= queries[j] < edges.length
*/

class Solution {
 public:
  vector<int> countPairs(int n, vector<vector<int>> &edges,
                         vector<int> &queries) {
    vector<int> deg(n + 1);
    unordered_map<int, int> cnt_e;
    for (auto &e : edges) {
      int x = e[0], y = e[1];
      if (x > y) swap(x, y);
      deg[x]++;
      deg[y]++;
      cnt_e[x << 16 | y]++;
    }

    // 统计deg中元素的出现次数
    unordered_map<int, int> cnt_deg;
    for (int i = 1; i <= n; i++) cnt_deg[deg[i]]++;
    // 2)
    int max_deg = *max_element(deg.begin() + 1, deg.end());
    int k = max_deg * 2 + 2;
    vector<int> cnts(k);

    for (auto [deg1, c1] : cnt_deg) {
      for (auto [deg2, c2] : cnt_deg) {
        if (deg1 < deg2) {
          cnts[deg1 + deg2] += c1 * c2;
        } else if (deg1 == deg2) {
          cnts[deg1 + deg2] += c1 * (c1 - 1) / 2;
        }
      }
    }

    // 3)
    for (auto [key, c] : cnt_e) {
      int s = deg[key >> 16] + deg[key & 0xffff];
      cnts[s]--;
      cnts[s - c]++;
    }

    // 4) 计算cnts的后缀和
    for (int i = k - 1; i > 0; i--) cnts[i - 1] += cnts[i];
    for (int &q : queries) q = cnts[min(q + 1, k - 1)];

    return queries;
  }
};