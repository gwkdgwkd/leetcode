/*
给你一个整数n，
请你在无限的整数序列[1,2,3,4,5,6,7,8,9,10,11,...]中，
找出并返回第n位上的数字。

示例1：
输入：n = 3
输出：3

示例2：
输入：n = 11
输出：0
解释：第11位数字在序列1,2,3,4,5,6,7,8,9,10,11...里是0，
     它是10的一部分。

提示：1 <= n <= 2^31 - 1
*/

// 剑指Offer44数字序列中某一位的数字

// 具体规律为：
// 数字区间 [1,9], [10, 99], [100, 999],
// 数字个数  9*1    90*2     900*3
// 数字起始  1      10       100

int findNthDigit(int n) {
  int idx = 1;
  long base = 9;

  // 将n逐渐减小，每次相减为9，90，900...
  while (n > idx * base) {
    n -= idx * base;
    base *= 10;
    idx++;
  }
  n--;
  int cnt = n / idx;  // 求距离1，10，100，1000...的距离
  int res = n % idx;  // 求出对应数字的对应位数

  char str[12];  // 输出到字符串,并输出对应位置的数字
  sprintf(str, "%d", base / 9 + cnt);

  return str[res] - '0';
}

// 通过补0每个数字字符宽度都补成当前位数k，
// 那么返回第n/k个数的第n%k位即可, 前面补0后n要右移对应的长度。
// k为3时，序列为000001002003004005006007008009010011...
class Solution {
 public:
  int findNthDigit(long n) {
    int k = 1;
    while (k * pow(10, k) < n) {
      n += pow(10, k);
      k += 1;
    }
    return to_string(n / k)[n % k] - '0';
  }
};

class Solution {
 public:
  int findNthDigit(long n) {
    // 首先从1-9这个区间开始，判断n位数所在的数字区间
    long base = 9;  // 定义当前位数的最大的数字
    int bit = 1;    // 定义当前位数

    // 这里判断直到n落入某个数字区间中：
    while (n > base * bit) {
      n -= base * bit;  // 进入到下一个区间
      bit++;            // 进位
      base *= 10;       // 下一个区间的最大数字
    }

    // pow(10,bit-1)表示当前数字区间的最开始的数字；
    // 这里n/bit获取的是包括第一个数字开始往后走多少个数字，
    // 本来应该是n/bit-1的，但是不-1的话，
    // 待会求余的结果就是当前数字的第几位，
    // 但如果求余结果为0的话，说明还不到下一个数字，
    // 因此为0应该为上一个数字的最后一位。
    int num = pow(10, bit - 1) + n / bit;
    int idx = n % bit;  // 获取目标位是当前数字num的第几位，索引+1

    if (idx != 0) {
      return std::to_string(num)[idx - 1] - '0';
    } else {
      return std::to_string(num - 1).back() - '0';
    }
  }
};