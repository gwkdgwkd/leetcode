/*
给定N个人的出生年份和死亡年份，第i个人的出生年份为birth[i]，
死亡年份为death[i]，实现一个方法以计算生存人数最多的年份。

你可以假设所有人都出生于1900年至2000年（含1900和2000）之间。
如果一个人在某一年的任意时期处于生存状态，那么他应该被纳入那一年的统计中。
例如，生于1908年、死于1909年的人应当被列入1908年和1909年的计数。

如果有多个年份生存人数相同且均为最大值，输出其中最小的年份。

示例：
输入：
birth = {1900, 1901, 1950}
death = {1948, 1951, 2000}
输出： 1901

提示：
0 < birth.length == death.length <= 10000
birth[i] <= death[i]
*/

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) < (b) ? (a) : (b))
#define BASE_YEAR 1900
#define MAX_LEN 102  // 实际大小是101
int maxAliveYear(int* birth, int birthSize, int* death, int deathSize) {
  int* years = (int*)calloc(MAX_LEN, sizeof(int));

  for (int i = 0; i < birthSize; i++) {
    years[birth[i] - BASE_YEAR]++;
    // 对于2000，实际不用减，但是数组长度多了1个，所以这里不用判断：
    years[death[i] - BASE_YEAR + 1]--;
  }

  int sum = 0;
  int max = 0;
  int max_year;
  for (int i = 0; i < MAX_LEN; i++) {
    sum += years[i];

    if (sum > max) {
      max = sum;
      max_year = i + BASE_YEAR;
    }
  }

  return max_year;
}

class Solution {
  static const int kBaseYear = 1900;
  static const int kMaxYear = 2000;
  static const int kLen = 101;

 public:
  int maxAliveYear(vector<int>& birth, vector<int>& death) {
    vector<int> nums(kLen, 0);

    for (int i = 0; i < birth.size(); ++i) {
      nums[birth[i] - kBaseYear]++;
      if (death[i] < kMaxYear) {
        nums[death[i] - kBaseYear + 1]--;
      }
    }

    int m = nums[0];
    int year;
    for (int i = 1; i < kLen; ++i) {
      nums[i] += nums[i - 1];
      if (nums[i] > m) {
        m = nums[i];
        year = i;
      }
    }

    return kBaseYear + year;
  }
};