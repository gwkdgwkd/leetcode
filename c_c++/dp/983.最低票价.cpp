/*
在一个火车旅行很受欢迎的国度，提前一年计划了一些火车旅行。
在接下来的一年，要旅行的日子将以名为days的数组给出，每一项是一个从1到365的整数。

火车票有三种不同的销售方式 ：
一张为期一天的通行证售价为costs[0]美元；
一张为期七天的通行证售价为costs[1]美元；
一张为期三十天的通行证售价为costs[2]美元。
通行证允许数天无限制的旅行。
例如，如果我们在第2天获得一张为期7天的通行证，那么我们可以连着旅行7天：
第2天、第3天、第4天、第5天、第6天、第7天和第8天。
返回想要完成在给定的列表days中列出的每一天的旅行所需要的最低消费。

示例1：
输入：days = [1,4,6,7,8,20], costs = [2,7,15]
输出：11
解释：
例如，这里有一种购买通行证的方法，可以让你完成你的旅行计划：
在第1天，花了costs[0]=$2买了一张为期1天的通行证，在1天生效。
在第3天，花了costs[1]=$7买了一张为期7天的通行证，在第3,4,...,9天生效。
在第20天，花了costs[0]=$2买了一张为期1天的通行证，在第20天生效。
总共花了$11，并完成了你计划的每一天旅行。

示例2：
输入：days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
输出：17
解释：
例如，这里有一种购买通行证的方法，可以让你完成你的旅行计划：
在第1天，你花了costs[2]=$15买了一张为期30天的通行证，它将在第1,2,...,30天生效。
在第31天，你花了costs[0] = $2买了一张为期1天的通行证，它将在第31天生效。
你总共花了$17，并完成了你计划的每一天旅行。

提示：
1 <= days.length <= 365
1 <= days[i] <= 365
days按顺序严格递增
costs.length == 3
1 <= costs[i] <= 1000
*/

// 动态规划
int mincostTickets(int* days, int daysSize, int* costs, int costsSize) {
  int dp[366] = {0};
  int index = 0;

  for (int i = 1; i <= 365; i++) {
    if (i == days[index]) {  // 第i天有出行计划
      dp[i] = dp[i - 1] + costs[0];
      dp[i] = dp[i] < (dp[(i >= 7 ? (i - 7) : 0)] + costs[1])
                  ? dp[i]
                  : (dp[(i >= 7 ? (i - 7) : 0)] + costs[1]);
      dp[i] = dp[i] < (dp[(i >= 30 ? (i - 30) : 0)] + costs[2])
                  ? dp[i]
                  : (dp[(i >= 30 ? (i - 30) : 0)] + costs[2]);
      if (index < daysSize - 1) {  // 之后还有出行计划
        index++;
      } else {
        return dp[i];  // 之后没有出行计划就直接返回，后面就不用计算了
      }
    } else {
      dp[i] = dp[i - 1];
    }
  }
  return dp[days[daysSize - 1]];
}

class Solution {
 public:
  int mincostTickets(vector<int>& days, vector<int>& costs) {
    int dp[366] = {0};
    int index = 0;

    for (int i = 1; i <= 365; ++i) {
      if (i == days[index]) {
        dp[i] = dp[i - 1] + costs[0];
        if (i >= 7) {
          dp[i] = min(dp[i], dp[i - 7] + costs[1]);
        } else {
          dp[i] = min(dp[i], costs[1]);
        }
        if (i >= 30) {
          dp[i] = min(dp[i], dp[i - 30] + costs[2]);
        } else {
          dp[i] = min(dp[i], costs[2]);
        }

        if (index++ == days.size() - 1) {
          return dp[i];
        }
      } else {
        dp[i] = dp[i - 1];
      }
    }
    return dp[days[days.size() - 1]];
  }
};
