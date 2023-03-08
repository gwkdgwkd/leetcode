/*
给你一个32位的有符号整数x，返回将x中的数字部分反转后的结果。
如果反转后整数超过32位的有符号整数的范围[-2^31,2^31-1]，就返回0。
假设环境不允许存储64位整数（有符号或无符号）。

示例1：
输入：x = 123
输出：321

示例2：
输入：x = -123
输出：-321

示例3：
输入：x = 120
输出：21

示例4：
输入：x = 0
输出：0

提示： -2^31 <= x <= 2^31 - 1
*/

int reverse(int x) {
  int ret = 0;
  while (x) {
    if (ret < INT_MIN / 10 || ret > INT_MAX / 10) {
      return 0;
    }
    int n = x % 10;
    x = x / 10;
    ret = ret * 10 + n;
  }

  return ret;
}

class Solution {
 public:
  int reverse(int x) {
    int ans = 0;
    while (x) {
      if (ans < INT_MIN / 10 || ans > INT_MAX / 10) {
        return 0;
      }
      ans = ans * 10 + x % 10;
      x = x / 10;
    }

    return ans;
  }
};