/*
给一个整数数组hours，表示以小时为单位的时间，返回一个整数，
表示满足i<j且hours[i]+hours[j]构成整天的下标对i,j的数目。
整天定义为时间持续时间是24小时的整数倍。
例如，1天是24小时，2天是48小时，3天是72小时，以此类推。

示例1：
输入：hours = [12,12,30,24,24]
输出：2
解释：构成整天的下标对分别是(0,1)和(3, 4)。

示例2：
输入：hours = [72,48,24,3]
输出：3
解释：构成整天的下标对分别是(0, 1)、(0, 2)和(1, 2)。


提示：
1 <= hours.length <= 5 * 10^5
1 <= hours[i] <= 10^9
*/

class Solution {
 public:
  long long countCompleteDayPairs(vector<int>& hours) {
    long long cnt[24]{};
    long long ans = 0;
    for (auto h : hours) {
      ans += cnt[(24 - h % 24) % 24];
      cnt[h % 24]++;
    }
    return ans;
  }
};