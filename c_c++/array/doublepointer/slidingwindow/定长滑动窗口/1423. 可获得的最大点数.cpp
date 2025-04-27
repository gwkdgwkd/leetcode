/*
几张卡牌排成一行，每张卡牌都有一个对应的点数。点数由整数数组cardPoints给出。
每次行动，可以从行的开头或者末尾拿一张卡牌，最终必须正好拿k张卡牌。
的点数就是你拿到手中的所有卡牌的点数之和。
给一个整数数组cardPoints和整数k，请返回可以获得的最大点数。

示例1：
输入：cardPoints = [1,2,3,4,5,6,1], k = 3
输出：12
解释：第一次行动，不管拿哪张牌，的点数总是1。
     但是，先拿最右边的卡牌将会最大化的可获得点数。
     最优策略是拿右边的三张牌，最终点数为1 + 6 + 5 = 12。

示例2：
输入：cardPoints = [2,2,2], k = 2
输出：4
解释：无论你拿起哪两张卡牌，可获得的点数总是4。

示例3：
输入：cardPoints = [9,7,7,9,7,7,9], k = 7
输出：55
解释：必须拿起所有卡牌，可以获得的点数为所有卡牌的点数之和。

示例4：
输入：cardPoints = [1,1000,1], k = 1
输出：1
解释：无法拿到中间那张卡牌，所以可以获得的最大点数为1。

示例5：
输入：cardPoints = [1,79,80,1,1,1,200,1], k = 3
输出：202


提示：
1 <= cardPoints.length <= 10^5
1 <= cardPoints[i] <= 10^4
1 <= k <= cardPoints.length
*/

/*
逆向思维
拿走k张，剩下n−k张，这里n是cardPoints的长度。
由于拿走的点数和+剩下的点数和=所有点数和=常数，
所以为了最大化拿走的点数和，应当最小化剩下的点数和。
由于只能从开头或末尾拿牌，所以最后剩下的牌必然是连续的。
至此，问题变成：计算长为n−k的连续子数组和的最小值。
这可以用滑动窗口解决。
*/
class Solution {
  // 时间复杂度：O(n)，其中n为cardPoints的长度。
  // 空间复杂度：O(1)，仅用到若干额外变量。
 public:
  int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int all = accumulate(cardPoints.begin(), cardPoints.end(), 0);
    if (n == k) {
      return all;
    }
    k = n - k;

    int ans = INT_MAX, sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += cardPoints[i];
      if (i < k - 1) {
        continue;
      }
      ans = min(ans, sum);
      sum -= cardPoints[i - k + 1];
    }

    return all - ans;
  }
};

/*
正向思维
答案等于如下结果的最大值：
前k个数的和。
前k−1个数以及后1个数的和。
前k−2个数以及后2个数的和。
……
前2个数以及后k−2个数的和。
前1个数以及后k−1个数的和。
后k个数的和。
*/
class Solution {
 public:
  int maxScore(vector<int>& cardPoints, int k) {
    int s = reduce(cardPoints.begin(), cardPoints.begin() + k);
    int ans = s;
    for (int i = 1; i <= k; i++) {
      s += cardPoints[cardPoints.size() - i] - cardPoints[k - i];
      ans = max(ans, s);
    }
    return ans;
  }
};