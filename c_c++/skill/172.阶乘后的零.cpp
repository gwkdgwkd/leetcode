/*
给定一个整数n，返回n!结果中尾随零的数量。
提示n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1

示例1：
输入：n = 3
输出：0
解释：3! = 6，不含尾随0

示例2：
输入：n = 5
输出：1
解释：5! = 120，有一个尾随0

示例3：
输入：n = 0
输出：0

提示：0 <= n <= 10^4

进阶：你可以设计并实现对数时间复杂度的算法来解决此问题吗？
*/

int trailingZeroes(int n) {
  int res = 0;
  for (int d = n; d / 5 > 0; d = d / 5) {
    res += d / 5;
  }
  return res;
}

// 思路：
// 1.末尾的0怎么来的，两个数相乘末尾有0，则这两个数中必有因子2和5；
// 2.问题转换为：N!最多可以分解出多少个因子2和5，
//   由于每个偶数都能分解出因子2，即因子2肯定比因子5多；
// 3.问题转换为：N!最多可以分解出多少个因子5。
class Solution {
 public:
  int trailingZeroes(int n) {
    int ans = 0;
    while (n) {
      n /= 5;
      ans += n;
    }

    return ans;
  }
};