/*
下一个数。
给定一个正整数，
找出与其二进制表达式中1的个数相同且大小最接近的那两个数，
一个略大，一个略小。

示例1:
输入：num = 2（或者0b10）
输出：[4, 1] 或者（[0b100, 0b1]）

示例2:
输入：num = 1
输出：[2, -1]

提示:
num的范围在[1,2147483647]之间；
如果找不到前一个或者后一个满足条件的正数，那么输出-1。
*/

int cntbit(long n) {
  int cnt = 0;
  while (n > 0) {
    if (n & 1) cnt++;
    n = n >> 1;
  }

  return cnt;
}
int* findClosedNumbers(int num, int* returnSize) {
  int* res = malloc(sizeof(int) * 2);
  res[0] = res[1] = -1;
  *returnSize = 2;
  int bits = cntbit(num);
  long n;
  if (num == 2147483647) {
    return res;  // 特殊情况特殊考虑；
  } else if (num < 2147483647) {
    for (n = num + 1; n <= 2147483647; n++) {
      if (cntbit(n) == bits) {
        res[0] = n;
        break;
      }
    }
    for (n = num - 1; n >= 0; n--) {
      if (cntbit(n) == bits) {
        res[1] = n;
        break;
      }
    }
  }

  return res;
}

class Solution {
 public:
  int getNext(int num) {
    int c = num;
    int c0 = 0;
    int c1 = 0;

    // 从右往左找到第一个非零的位（即非拖尾的0）：
    while (((c & 1) == 0) && (c != 0)) {
      c0++;
      c >>= 1;
    }

    // 统计连续1的个数（拖尾连续的1）：
    while ((c & 1) == 1) {
      c1++;
      c >>= 1;
    }

    // 不存在的情况：
    if (c0 + c1 == 31 || c0 + c1 == 0) {
      return -1;
    }

    int p = c0 + c1;

    num |= (1 << p);             // 翻转最右非拖尾的0
    num &= ~((1 << p) - 1);      // 清除所有p的右侧位
    num |= (1 << (c1 - 1)) - 1;  // 在右侧插入(c1-1)个1
    return num;
  }

  int getPrev(int num) {
    int c = num;
    int c0 = 0;
    int c1 = 0;

    while (c & 1 == 1) {
      c1++;
      c >>= 1;
    }

    if (c == 0) return -1;

    while (((c & 1) == 0) && (c != 0)) {
      c0++;
      c >>= 1;
    }

    int p = c0 + c1;

    // 从位置p开始清零，这行代码力扣会报错：
    // num &= ((~0) << (p + 1));
    // 改用for循环从位置p开始清零：
    for (int i = 0; i < p + 1; ++i) {
      num &= (~(1 << i));
    }

    // 包括c1+1个1的序列：
    int mask = (1 << (c1 + 1)) - 1;
    num |= mask << (c0 - 1);

    return num;
  }

  vector<int> findClosedNumbers(int num) {
    int nextNum = getNext(num);
    int prevNum = getPrev(num);

    return {nextNum, prevNum};
  }
};
