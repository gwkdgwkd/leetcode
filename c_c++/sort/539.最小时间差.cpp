/*
给定一个24小时制（小时:分钟"HH:MM"）的时间列表，
找出列表中任意两个时间的最小时间差并以分钟数表示。

示例1：
输入：timePoints = ["23:59","00:00"]
输出：1

示例2：
输入：timePoints = ["00:00","23:59","00:00"]
输出：0

提示：
2 <= timePoints.length <= 2 * 10^4
timePoints[i]格式为"HH:MM"
*/

// 剑指OfferII035最小时间差

int getMinutes(const char *t) {
  return ((t[0] - '0') * 10 + (t[1] - '0')) * 60 + (t[3] - '0') * 10 +
         (t[4] - '0');
}
int cmp(const void *pa, const void *pb) {
  return strcmp(*(char **)pa, *(char **)pb);
}
int findMinDifference(char **timePoints, int timePointsSize) {
  qsort(timePoints, timePointsSize, sizeof(char *), cmp);
  int ans = 1440;
  int t0Minutes = getMinutes(timePoints[0]);
  int preMinutes = t0Minutes;
  for (int i = 1; i < timePointsSize; ++i) {
    int minutes = getMinutes(timePoints[i]);
    ans = fmin(ans, minutes - preMinutes);  // 相邻时间的时间差
    preMinutes = minutes;
  }
  ans = fmin(ans, t0Minutes + 1440 - preMinutes);  // 首尾时间的时间差
  return ans;
}

class Solution {
  int getMinutes(string &t) {
    return (int(t[0] - '0') * 10 + int(t[1] - '0')) * 60 +
           int(t[3] - '0') * 10 + int(t[4] - '0');
  }

 public:
  int findMinDifference(vector<string> &timePoints) {
    sort(timePoints.begin(), timePoints.end());
    int ans = INT_MAX;
    int t0Minutes = getMinutes(timePoints[0]);
    int preMinutes = t0Minutes;
    for (int i = 1; i < timePoints.size(); ++i) {
      int minutes = getMinutes(timePoints[i]);
      ans = min(ans, minutes - preMinutes);  // 相邻时间的时间差
      preMinutes = minutes;
    }
    ans = min(ans, t0Minutes + 1440 - preMinutes);  // 首尾时间的时间差
    return ans;
  }
};