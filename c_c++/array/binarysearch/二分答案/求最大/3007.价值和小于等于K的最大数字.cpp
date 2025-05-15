/*
给一个整数k和一个整数x。
整数num的价值是它的二进制表示中在x，2x，3x等位置处的数目（从最低有效位开始）。
下面的表格包含了如何计算价值的例子。
x	num	Binary Representation	Price
1	13	    000001101	        3
2	13	    000001101	        1
2	233	    011101001	        3
3	13	    000001101	        1
3	362	    101101010	        2
num的累加价值是从1到num的数字的总价值。如果num的累加价值小于或等于k则被认为是廉价的。
请返回最大的廉价数字。

示例1：
输入：k = 9, x = 1
输出：6
解释：由下表所示，6是最大的廉价数字。
     x	num	Binary Representation	Price	Accumulated Price
     1	1	001	                    1	    1
     1	2	010	                    1	    2
     1	3	011	                    2	    4
     1	4	100	                    1	    5
     1	5	101	                    2	    7
     1	6	110	                    2	    9
     1	7	111	                    3	    12

示例2：
输入：k = 7, x = 2
输出：9
解释：由下表所示，9是最大的廉价数字。
     x	num	Binary Representation	Price	Accumulated Price
     2	1	0001	                0	    0
     2	2	0010	                1	    1
     2	3	0011	                1	    2
     2	4	0100	                0	    2
     2	5	0101	                0	    2
     2	6	0110	                1	    3
     2	7	0111	                1	    4
     2	8	1000	                1	    5
     2	9	1001	                1	    6
     2	10	1010	                2	    8



提示：
1 <= k <= 10^15
1 <= x <= 8
*/

// 二分答案 + 数学公式
class Solution {
 public:
  long long findMaximumNumber(long long k, int x) {
    auto check = [&](long long num) {
      long long res = 0;
      // 统计[1,num]中的第x,2x,3x,...个比特位上的1的个数
      // 注意比特位从0开始，不是从1开始，所以要减一
      for (int i = x - 1; num >> i; i += x) {
        long long n = num >> i;
        res += n >> 1 << i;
        if (n & 1) {
          long long mask = (1LL << i) - 1;
          res += (num & mask) + 1;
        }
      }
      return res <= k;
    };

    // long long left = 0, right = (k + 1) << x;
    // while (left + 1 < right) {
    //     long long mid = left + (right - left) / 2;
    //     (check(mid) ? left : right) = mid;
    // }
    // return left;

    long long left = 0, right = (k + 1) << x;
    while (left <= right) {
      long long mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};

// 二分答案 + 数位DP

// 二分查找
class Solution {
 public:
  long long findMaximumNumber(long long k, int x) {
    long long l = 1, r = (k + 1) << x;
    while (l < r) {
      long long m = (l + r + 1) / 2;
      if (accumulatedPrice(x, m) > k) {
        r = m - 1;
      } else {
        l = m;
      }
    }
    return l;
  }

  long long accumulatedBitPrice(int x, long long num) {
    long long period = 1LL << x;
    long long res = period / 2 * (num / period);
    if (num % period >= period / 2) {
      res += num % period - (period / 2 - 1);
    }
    return res;
  }

  long long accumulatedPrice(int x, long long num) {
    long long res = 0;
    int length = 64 - __builtin_clzll(num);
    for (int i = x; i <= length; i += x) {
      res += accumulatedBitPrice(i, num);
    }
    return res;
  }
};