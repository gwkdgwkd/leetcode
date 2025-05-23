/*
给一棵n个节点的无向树，节点从0到n-1编号。
树以长度为n-1下标从0开始的二维整数数组edges的形式给你，
其中edges[i]=[ui,vi]表示树中节点ui和vi之间有一条边。
同时给一个正整数k和一个长度为n下标从0开始的非负整数数组nums，其中nums[i]表示节点i的价值。
Alice想最大化树中所有节点价值之和。
为了实现这一目标，Alice可以执行以下操作任意次（包括0次）：
选择连接节点u和v的边[u,v]，并将它们的值更新为：
nums[u] = nums[u] XOR k
nums[v] = nums[v] XOR k
请返回Alice通过执行以上操作任意次后，可以得到所有节点价值之和的最大值。

示例1：
输入：nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
输出：6
解释：Alice可以通过一次操作得到最大价值和6：
     选择边[0,2]。nums[0]和nums[2]都变为：1 XOR 3 = 2，
     数组nums变为：[1,2,1] -> [2,2,2]。
     所有节点价值之和为2 + 2 + 2 = 6。6是可以得到最大的价值之和。

示例2：
输入：nums = [2,3], k = 7, edges = [[0,1]]
输出：9
解释：Alice可以通过一次操作得到最大和9：选择边[0,1]。
     nums[0]变为：2 XOR 7 = 5，
     nums[1]变为：3 XOR 7 = 4，数组nums变为：[2,3] -> [5,4]。
     所有节点价值之和为5 + 4 = 9。9是可以得到最大的价值之和。

示例3：
输入：nums = [7,7,7,7,7,7], k = 3, edges = [[0,1],[0,2],[0,3],[0,4],[0,5]]
输出：42
解释：Alice不需要执行任何操作，就可以得到最大价值之和42。


提示：
2 <= n == nums.length <= 2 * 10^4
1 <= k <= 10^9
0 <= nums[i] <= 10^9
edges.length == n - 1
edges[i].length == 2
0 <= edges[i][0], edges[i][1] <= n - 1
输入保证edges构成一棵合法的树。
*/

// 树形 DP
class Solution {
 public:
  long long maximumValueSum(vector<int> &nums, int k,
                            vector<vector<int>> &edges) {
    int n = nums.size();
    vector<vector<int>> g(n);
    for (auto &e : edges) {
      int x = e[0], y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }

    function<pair<long long, long long>(int, int)> dfs =
        [&](int x, int fa) -> pair<long long, long long> {
      long long f0 = 0, f1 = LLONG_MIN;  // f[x][0]和f[x][1]
      for (auto &y : g[x]) {
        if (y != fa) {
          auto [r0, r1] = dfs(y, x);
          long long t = max(f1 + r0, f0 + r1);
          f0 = max(f0 + r0, f1 + r1);
          f1 = t;
        }
      }
      return {max(f0 + nums[x], f1 + (nums[x] ^ k)),
              max(f1 + nums[x], f0 + (nums[x] ^ k))};
    };
    return dfs(0, -1).first;
  }
};

// 结论 + 状态机 DP
class Solution {
 public:
  long long maximumValueSum(vector<int> &nums, int k,
                            vector<vector<int>> &edges) {
    long long f0 = 0, f1 = LLONG_MIN;
    for (int x : nums) {
      long long t = max(f1 + x, f0 + (x ^ k));
      f0 = max(f0 + x, f1 + (x ^ k));
      f1 = t;
    }
    return f0;
  }
};