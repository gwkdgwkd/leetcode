/*
给一个n个节点的有向图，节点编号为0到n-1，每个节点至多有一条出边。
有向图用大小为n下标从0开始的数组edges表示，表示节点i有一条有向边指向edges[i]。
如果节点i没有出边，那么edges[i] == -1。
同时给两个节点node1和node2。
请返回一个从node1和node2都能到达节点的编号，
使节点node1和节点node2到这个节点的距离较大值最小化。
如果有多个答案，请返回最小的节点编号。如果答案不存在，返回-1。
注意edges可能包含环。

示例1：
输入：edges = [2,2,3,-1], node1 = 0, node2 = 1
输出：2
解释：从节点0到节点2的距离为1，从节点1到节点2的距离为1。
     两个距离的较大值为1。我们无法得到一个比1更小的较大值，所以我们返回节点2。

示例2：
输入：edges = [1,2,-1], node1 = 0, node2 = 2
输出：2
解释：节点0到节点2的距离为2，节点2到它自己的距离为0。
     两个距离的较大值为2。我们无法得到一个比2更小的较大值，所以我们返回节点2。


提示：
n == edges.length
2 <= n <= 10^5
-1 <= edges[i] < n
edges[i] != i
0 <= node1, node2 < n
*/

// 计算最短路
class Solution {
 public:
  int closestMeetingNode(vector<int>& edges, int node1, int node2) {
    int n = edges.size();

    auto calc_dis = [&](int x) {
      vector<int> dis(n, n);  // 初始化成n，表示无法到达或者尚未访问的节点
      // 从x出发，直到无路可走（x=-1）或者重复访问节点（dis[x]<n）
      for (int d = 0; x >= 0 && dis[x] == n; x = edges[x]) {
        dis[x] = d++;
      }
      return dis;
    };

    vector<int> dis1 = calc_dis(node1);
    vector<int> dis2 = calc_dis(node2);
    int min_dis = n, ans = -1;
    for (int i = 0; i < n; i++) {
      int d = max(dis1[i], dis2[i]);
      if (d < min_dis) {
        min_dis = d;
        ans = i;
      }
    }

    return ans;
  }
};

// 我吹过你吹过的晚风
class Solution {
 public:
  int closestMeetingNode(vector<int>& edges, int x, int y) {
    int n = edges.size();
    int ans = n;
    vector<int8_t> vis_x(n), vis_y(n);
    while (!vis_x[x] || !vis_y[y]) {  // x或y没有访问过
      vis_x[x] = vis_y[y] = true;     // 标记访问过
      if (vis_y[x]) {                 // 我吹过你吹过的晚风
        ans = x;
      }
      if (vis_x[y]) {
        ans = min(ans, y);  // 如果有多个答案，返回最小的节点编号
      }
      if (ans < n) {
        return ans;
      }

      if (edges[x] >= 0) {
        x = edges[x];  // 继续走
      }
      if (edges[y] >= 0) {
        y = edges[y];  // 继续走
      }
    }
    return -1;
  }
};
