/*
给一个长度为n的数组points和一个整数m。
同时有另外一个长度为n的数组gameScore，其中gameScore[i]表示第i个游戏得到的分数。
一开始对于所有的i都有gameScore[i] == 0。
开始于下标-1处，该下标在数组以外（在下标0前面一个位置）。
可以执行至多m次操作，每一次操作中，可以执行以下两个操作之一：
将下标增加1，同时将points[i]添加到gameScore[i]。
将下标减少1，同时将points[i]添加到gameScore[i]。
注意，在第一次移动以后，下标必须始终保持在数组范围以内。
请返回至多m次操作以后，gameScore里面最小值最大为多少。

示例1：
输入：points = [2,4], m = 3
输出：4
解释：一开始，下标i = -1且gameScore = [0, 0].
     移动	下标	gameScore
     增加i	 0	    [2, 0]
     增加i	 1 	    [2, 4]
     减少i	 0	    [4, 4]
     gameScore中的最小值为4，这是所有方案中可以得到的最大值，所以返回4。

示例2：
输入：points = [1,2,3], m = 5
输出：2
解释：一开始，下标i = -1且gameScore = [0, 0, 0]。
     移动   下标    gameScore
     增加i	0	    [1, 0, 0]
     增加i	1	    [1, 2, 0]
     减少i	0	    [2, 2, 0]
     增加i	1	    [2, 4, 0]
     增加i	2	    [2, 4, 3]
     gameScore中的最小值为2，这是所有方案中可以得到的最大值，所以返回2。


提示：
2 <= n == points.length <= 5 * 10^4
1 <= points[i] <= 10^6
1 <= m <= 10^9
*/

class Solution {
 public:
  long long maxScore(vector<int>& points, int m) {
    auto check = [&](long long low) -> bool {
      int n = points.size(), rem = m, pre = 0;
      for (int i = 0; i < n; i++) {
        int k = (low - 1) / points[i] + 1 - pre;  // 还需要操作的次数
        if (i == n - 1 && k <= 0) {  // 最后一个数已经满足要求
          break;
        }
        k = max(k, 1);     // 至少要走 步
        rem -= k * 2 - 1;  // 左右横跳
        if (rem < 0) {
          return false;
        }
        pre = k - 1;  // 右边那个数顺带操作了k-1次
      }
      return true;
    };

    long long left = 0;
    long long right = 1LL * (m + 1) / 2 * ranges::min(points) + 1;
    while (left + 1 < right) {
      long long mid = left + (right - left) / 2;
      (check(mid) ? left : right) = mid;
    }
    return left;
  }
};
