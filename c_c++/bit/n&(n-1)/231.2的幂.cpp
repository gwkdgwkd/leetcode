/*
给你一个整数n，请你判断该整数是否是2的幂次方。
如果是，返回true；否则，返回false。
如果存在一个整数x使得n == 2^x，则认为n是2的幂次方。

示例1：
输入：n = 1
输出：true
解释：20 = 1

示例2：
输入：n = 16
输出：true
解释：24 = 16

示例3：
输入：n = 3
输出：false

示例4：
输入：n = 4
输出：true

示例5：
输入：n = 5
输出：false

提示：-2^31 <= n <= 2^31 - 1
*/

// 一个数如果是2的指数，那么它的二进制表示一定只含有一个1：
// 2^0 = 1 = 0b0001
// 2^1 = 2 = 0b0010
// 2^2 = 4 = 0b0100
bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }

class Solution {
 public:
  bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }
};