/*
给一个整数数组bloomDay，以及两个整数m和k。
现需要制作m束花。制作花束时，需要使用花园中相邻的k朵花。
花园中有n朵花，第i朵花会在bloomDay[i]时盛开，恰好可以用于一束花中。
请返回从花园中摘m束花需要等待的最少的天数。如果不能摘到m束花则返回-1。

示例1：
输入：bloomDay = [1,10,3,10,2], m = 3, k = 1
输出：3
解释：让我们一起观察这三天的花开过程，x表示花开，而_表示花还未开。
     现在需要制作3束花，每束只需要1朵。
     1天后：[x, _, _, _, _]   // 只能制作1束花
     2天后：[x, _, _, _, x]   // 只能制作2束花
     3天后：[x, _, x, _, x]   // 可以制作3束花，答案为3

示例2：
输入：bloomDay = [1,10,3,10,2], m = 3, k = 2
输出：-1
解释：要制作3束花，每束需要2朵花，也就是一共需要6朵花。
     而花园中只有5朵花，无法满足制作要求，返回-1。

示例3：
输入：bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
输出：12
解释：要制作2束花，每束需要3朵。花园在7天后和12天后的情况如下：
     7天后：[x, x, x, x, _, x, x]
     可以用前3朵盛开的花制作第一束花。但不能使用后3朵盛开的花，因为它们不相邻。
     12天后：[x, x, x, x, x, x, x]
     显然，我们可以用不同的方式制作两束花。

示例4：
输入：bloomDay = [1000000000,1000000000], m = 1, k = 1
输出：1000000000
解释：需要等1000000000天才能采到花来制作花束。

示例5：
输入：bloomDay = [1,10,2,9,3,8,4,7,5,6], m = 4, k = 2
输出：9


提示：
bloomDay.length == n
1 <= n <= 10^5
1 <= bloomDay[i] <= 10^9
1 <= m <= 10^6
1 <= k <= n
*/

class Solution {
 public:
  int minDays(vector<int>& bloomDay, int m, int k) {
    if (m > bloomDay.size() / k) {
      return -1;
    }

    auto check = [&](int d) {
      int n = bloomDay.size();
      int c = 0;
      int sum = 0;
      for (int i = 0; i < n; ++i) {
        if (bloomDay[i] <= d) {
          ++c;
          if (c == k) {
            ++sum;
            c = 0;
          }
        } else {
          c = 0;
        }
      }
      return sum >= m;
    };

    int left = *min_element(bloomDay.begin(), bloomDay.end());
    int right = *max_element(bloomDay.begin(), bloomDay.end());
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};