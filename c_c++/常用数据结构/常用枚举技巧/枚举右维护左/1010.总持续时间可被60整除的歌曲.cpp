/*
在歌曲列表中，第i首歌曲的持续时间为time[i]秒。
返回其总持续时间（以秒为单位）可被60整除的歌曲对的数量。
形式上，我们希望下标数字i和j满足i<j且有(time[i]+time[j])%60==0。

示例1：
输入：time = [30,20,150,100,40]
输出：3
解释：这三对的总持续时间可被60整除：
     (time[0] = 30, time[2] = 150): 总持续时间180
     (time[1] = 20, time[3] = 100): 总持续时间120
     (time[1] = 20, time[4] = 40):  总持续时间60

示例2：
输入：time = [60,60,60]
输出：3
解释：所有三对的总持续时间都是120，可以被60整除。


提示：
1 <= time.length <= 6 * 10^4
1 <= time[i] <= 500
*/

class Solution {
 public:
  int numPairsDivisibleBy60(vector<int> &time) {
    // 如果time[i]=1，那么需要知道左边有多少个模60是59的数。
    // 如果time[i]=62，那么需要知道左边有多少个模60是58的数。
    // 一般地，对于time[i]，需要知道左边有多少个模60是60−time[i]%60的数。
    // 特别地，如果time[i]模60是0，那么需要知道左边有多少个模60也是0的数。
    // 这两种情况可以合并为：累加左边(60−time[i]%60)%60的出现次数。

    int ans = 0, cnt[60]{};
    for (int t : time) {
      // 先查询cnt，再更新cnt，因为题目要求i<j
      // 如果先更新，再查询，就把i=j的情况也考虑进去了
      ans += cnt[(60 - t % 60) % 60];
      cnt[t % 60]++;
    }
    return ans;
  }
};
