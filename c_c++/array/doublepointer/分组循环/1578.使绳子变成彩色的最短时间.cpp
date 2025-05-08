/*
Alice把n个气球排列在一根绳子上。
给一个下标从0开始的字符串colors，其中colors[i]是第i个气球的颜色。
Alice想要把绳子装扮成五颜六色的，
且她不希望两个连续的气球涂着相同的颜色，所以她喊来Bob帮忙。
Bob可以从绳子上移除一些气球使绳子变成彩色。
给你一个下标从0开始的整数数组neededTime，
其中neededTime[i]是Bob从绳子上移除第i个气球需要的时间（以秒为单位）。
返回Bob使绳子变成彩色需要的最少时间。

示例1：
输入：colors = "abaac", neededTime = [1,2,3,4,5]
输出：3
解释：'a'是蓝色，'b'是红色且'c'是绿色。
     Bob可以移除下标2的蓝色气球。这将花费3秒。
     移除后，不存在两个连续的气球涂着相同的颜色。总时间=3。

示例2：
输入：colors = "abc", neededTime = [1,2,3]
输出：0
解释：绳子已经是彩色的，Bob不需要从绳子上移除任何气球。

示例3：
输入：colors = "aabaa", neededTime = [1,2,3,4,1]
输出：2
解释：Bob会移除下标0和下标4处的气球。这两个气球各需要1秒来移除。
     移除后，不存在两个连续的气球涂着相同的颜色。总时间=1+1=2。


提示：
n == colors.length == neededTime.length
1 <= n <= 10^5
1 <= neededTime[i] <= 10^4
colors 仅由小写英文字母组成
*/

class Solution {
 public:
  int minCost(string colors, vector<int>& neededTime) {
    int n = colors.size();
    int maxTime = 0;
    int sum = 0;
    int ans = 0;
    int left = 0;
    int right = 0;
    while (right < n) {
      if (right > 0 && colors[right] != colors[right - 1]) {
        if (right - left > 1) {
          sum -= maxTime;
          ans += sum;
        }
        sum = maxTime = 0;
        left = right;
      }
      sum += neededTime[right];
      maxTime = max(maxTime, neededTime[right]);
      ++right;
    }
    if (right - left > 1) {
      sum -= maxTime;
      ans += sum;
    }
    return ans;
  }
};