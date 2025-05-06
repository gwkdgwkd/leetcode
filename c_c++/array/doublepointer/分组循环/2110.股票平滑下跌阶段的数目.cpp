/*
给一个整数数组prices，表示一支股票的历史每日股价，
其中prices[i]是这支股票第i天的价格。
一个平滑下降的阶段定义为：对于连续一天或者多天，
每日股价都比前一日股价恰好少1，这个阶段第一天的股价没有限制。
请返回平滑下降阶段的数目。

示例1：
输入：prices = [3,2,1,4]
输出：7
解释：总共有7个平滑下降阶段：
     [3], [2], [1], [4], [3,2], [2,1]和[3,2,1]
     注意，仅一天按照定义也是平滑下降阶段。

示例2：
输入：prices = [8,6,7,7]
输出：4
解释：总共有4个连续平滑下降阶段：[8], [6], [7]和[7]
     由于8 - 6 ≠ 1，所以[8,6]不是平滑下降阶段。

示例3：
输入：prices = [1]
输出：1
解释：总共有1个平滑下降阶段：[1]


提示：
1 <= prices.length <= 10^5
1 <= prices[i] <= 10^5
*/

// 滑动窗口
class Solution {
 public:
  long long getDescentPeriods(vector<int>& prices) {
    int n = prices.size();
    long long ans = 0;
    int left = 0;
    int right = 0;
    while (right < n) {
      if (prices[right] != (prices[left] - right + left)) {
        left = right;
      }
      ans += right - left + 1;
      ++right;
    }
    return ans;
  }
};

// 分组循环
class Solution {
 public:
  long long getDescentPeriods(vector<int>& prices) {
    int right = 0, len = prices.size();
    long long ans = 0;
    while (right < len) {
      int left = right;
      right++;
      while (right < len && prices[right] - prices[right - 1] == -1) {
        right++;
      }
      ans += (long long)(right - left + 1) * (long long)(right - left) / 2;
    }
    return ans;
  }
};

// 动态规划
class Solution {
 public:
  long long getDescentPeriods(vector<int>& prices) {
    int n = prices.size();
    long long res = 1;  // 平滑下降阶段的总数，初值为dp[0]
    int prev = 1;  // 上一个元素为结尾的平滑下降阶段的总数，初值为dp[0]
    // 从1开始遍历数组，按照递推式更新prev以及总数res
    for (int i = 1; i < n; ++i) {
      if (prices[i] == prices[i - 1] - 1) {
        ++prev;
      } else {
        prev = 1;
      }
      res += prev;
    }
    return res;
  }
};