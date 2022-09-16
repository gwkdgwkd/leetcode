/*
丑数就是只包含质因数2、3和5的正整数。
给你一个整数n，请你判断n是否为丑数。
如果是，返回true；否则，返回false。

示例1：
输入：n = 6
输出：true
解释：6 = 2 × 3

示例2：
输入：n = 1
输出：true
解释：1没有质因数，因此它的全部质因数是{2, 3, 5}的空集。
     习惯上将其视作第一个丑数。

示例3：
输入：n = 14
输出：false
解释：14不是丑数，因为它包含了另外一个质因数7。

提示：-2^31 <= n <= 2^31-1
*/

class Solution {
 public:
  bool isUgly(int n) {
    if (n <= 0) {
      return false;
    }
    vector<int> factors = {2, 3, 5};
    for (int factor : factors) {
      while (n % factor == 0) {
        n /= factor;
      }
    }
    return n == 1;
  }
};