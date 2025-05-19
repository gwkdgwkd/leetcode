/*
给两个数组arr1和arr2，它们一开始都是空的。
需要往它们中添加正整数，使它们满足以下条件：
arr1包含uniqueCnt1个互不相同的正整数，每个整数都不能被divisor1整除。
arr2包含uniqueCnt2个互不相同的正整数，每个整数都不能被divisor2整除。
arr1和arr2中的元素互不相同。
给divisor1，divisor2，uniqueCnt1和uniqueCnt2，请返回两个数组中最大元素的最小值。

示例1：
输入：divisor1 = 2, divisor2 = 7, uniqueCnt1 = 1, uniqueCnt2 = 3
输出：4
解释：我们可以把前4个自然数划分到arr1和arr2中。
     arr1 = [1]和arr2 = [2,3,4]。
     可以看出两个数组都满足条件。
     最大值是4，所以返回4。

示例2：
输入：divisor1 = 3, divisor2 = 5, uniqueCnt1 = 2, uniqueCnt2 = 1
输出：3
解释：arr1 = [1,2]和arr2 = [3]满足所有条件。
     最大值是3，所以返回3。

示例3：
输入：divisor1 = 2, divisor2 = 4, uniqueCnt1 = 8, uniqueCnt2 = 2
输出：15
解释：最终数组为arr1 = [1,3,5,7,9,11,13,15]和arr2 = [2,6]。
     上述方案是满足所有条件的最优解。


提示：
2 <= divisor1, divisor2 <= 10^5
1 <= uniqueCnt1, uniqueCnt2 < 10^9
2 <= uniqueCnt1 + uniqueCnt2 <= 10^9
*/

class Solution {
 public:
  int minimizeSet(int d1, int d2, int n, int m) {
    int l = n + m, r = INT_MAX;
    while (l < r) {
      int mid = l + ((r - l) >> 1);
      if (check(mid, d1, d2, n, m)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }

  bool check(int v, int d1, int d2, int n, int m) {
    long c1 = v / d1;
    long c2 = v / d2;
    long cc = v / lcm(d1, d2);
    c1 -= cc;
    c2 -= cc;
    v -= cc;
    if (c1 > m) {
      v -= (c1 - m);
    }
    if (c2 > n) {
      v -= (c2 - n);
    }
    return v >= (n + m);
  }

  int gcd(int a, int b) { return b != 0 ? gcd(b, a % b) : a; }
  long lcm(long a, long b) { return a * b / gcd(a, b); }
};