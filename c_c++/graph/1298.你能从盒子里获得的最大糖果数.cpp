/*
给n个盒子，每个盒子的格式为[status, candies, keys, containedBoxes]，其中：
状态字status[i]：整数，如果box[i]是开的，那么是1，否则是0。
糖果数candies[i]:整数，表示box[i]中糖果的数目。
钥匙keys[i]：
数组，表示打开box[i]后，可以得到一些盒子的钥匙，每个元素分别为该钥匙对应盒子的下标。
内含的盒子containedBoxes[i]：整数，表示放在box[i]里的盒子所对应的下标。
给一个整数数组initialBoxes，包含你最初拥有的盒子。
可以拿走每个已打开盒子里的所有糖果，并且可以使用其中的钥匙去开启新的盒子，
并且可以使用在其中发现的其他盒子。
请按照上述规则，返回可以获得糖果的最大数目。

示例1：
输入：status = [1,0,1,0],
     candies = [7,5,4,100],
     keys = [[],[],[1],[]],
     containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
输出：16
解释：一开始有盒子0 。将获得它里面的7个糖果和盒子1和2。
     盒子1目前状态是关闭的，而且还没有对应它的钥匙。
     所以将会打开盒子2，并得到里面的4个糖果和盒子1的钥匙。
     在盒子1中，会获得5个糖果和盒子3，但是没法获得盒子3的钥匙，所以盒子3会保持关闭状态。
     总共可以获得的糖果数目 = 7 + 4 + 5 = 16个。

示例2：
输入：status = [1,0,0,0,0,0],
     candies = [1,1,1,1,1,1],
     keys =[[1,2,3,4,5],[],[],[],[],[]],
     containedBoxes = [[1,2,3,4,5],[],[],[],[],[]],
     initialBoxes = [0]
输出：6
解释：一开始拥有盒子0。打开它你可以找到盒子1,2,3,4,5和它们对应的钥匙。
     打开这些盒子，将获得所有盒子的糖果，所以总糖果数为6个。

示例3：
输入：status = [1,1,1],
     candies = [100,1,100],
     keys = [[],[0,2],[]],
     containedBoxes = [[],[],[]],
     initialBoxes = [1]
输出：1

示例4：
输入：status = [1],
     candies = [100],
     keys = [[]],
     containedBoxes = [[]],
     initialBoxes = []
输出：0

示例5：
输入：status = [1,1,1],
     candies = [2,3,2],
     keys = [[],[],[]],
     containedBoxes =[[],[],[]],
     initialBoxes = [2,1,0]
输出：7


提示：
1 <= status.length <= 1000
status.length == candies.length == keys.length == containedBoxes.length == n
status[i]要么是0要么是1。
1 <= candies[i] <= 1000
0 <= keys[i].length <= status.length
0 <= keys[i][j] < status.length
keys[i]中的值都是互不相同的。
0 <= containedBoxes[i].length <= status.length
0 <= containedBoxes[i][j] < status.length
containedBoxes[i]中的值都是互不相同的。
每个盒子最多被一个盒子包含。
0 <= initialBoxes.length <= status.length
0 <= initialBoxes[i] < status.length
*/

class Solution {
 public:
  int maxCandies(vector<int>& status, vector<int>& candies,
                 vector<vector<int>>& keys, vector<vector<int>>& containedBoxes,
                 vector<int>& initialBoxes) {
    int ans = 0;
    auto& has_key = status;  // 把开着的盒子当作有钥匙
    vector<uint8_t> has_box(status.size());
    for (int x : initialBoxes) {
      has_box[x] = true;
    }

    auto dfs = [&](this auto&& dfs, int x) -> void {
      ans += candies[x];
      has_box[x] = false;  // 避免找到钥匙后重新访问开着的盒子

      // 找到钥匙，打开盒子（说明我们先找到盒子，然后找到钥匙）
      for (int y : keys[x]) {
        has_key[y] = true;
        if (has_box[y]) {
          dfs(y);
        }
      }

      // 找到盒子，使用钥匙（说明我们先找到钥匙，然后找到盒子）
      for (int y : containedBoxes[x]) {
        has_box[y] = true;
        if (has_key[y]) {
          dfs(y);
        }
      }
    };

    for (int x : initialBoxes) {
      if (has_key[x] && has_box[x]) {  // 注意dfs中会修改has_box
        dfs(x);
      }
    }
    return ans;
  }
};
