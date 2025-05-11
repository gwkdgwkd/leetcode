/*
给一个整数mountainHeight表示山的高度。
同时给一个整数数组workerTimes，表示工人们的工作时间（单位：秒）。
工人们需要同时进行工作以降低山的高度。对于工人i：
山的高度降低x，需要花费workerTimes[i]+workerTimes[i]*2+...+workerTimes[i]*x秒。
例如：
山的高度降低1，需要workerTimes[i]秒。
山的高度降低2，需要workerTimes[i] + workerTimes[i]*2秒，依此类推。
返回一个整数，表示工人们使山的高度降低到0所需的最少秒数。

示例1：
输入：mountainHeight = 4, workerTimes = [2,1,1]
输出：3
解释：将山的高度降低到0的一种方式是：
     工人0将高度降低1，花费workerTimes[0] = 2秒。
     工人1将高度降低2，花费workerTimes[1] + workerTimes[1] * 2 = 3秒。
     工人2将高度降低1，花费workerTimes[2] = 1秒。
     因为工人同时工作，所需的最少时间为max(2, 3, 1) = 3秒。

示例2：
输入：mountainHeight = 10, workerTimes = [3,2,2,4]
输出：12
解释：工人0将高度降低2，花费workerTimes[0]+workerTimes[0]*2=9秒。
     工人1将高度降低3，花费workerTimes[1]+workerTimes[1]*2+workerTimes[1]*3=12秒。
     工人2将高度降低3，花费workerTimes[2]+workerTimes[2]*2+workerTimes[2]*3=12秒。
     工人3将高度降低2，花费workerTimes[3]+workerTimes[3]*2=12秒。
     所需的最少时间为max(9, 12, 12, 12) = 12秒。

示例3：
输入：mountainHeight = 5, workerTimes = [1]
输出：15
解释：这个示例中只有一个工人，所以答案是：
     workerTimes[0]+workerTimes[0]*2+workerTimes[0]*3+
     workerTimes[0]*4+workerTimes[0]*5=15秒。


提示：
1 <= mountainHeight <= 10^5
1 <= workerTimes.length <= 10^4
1 <= workerTimes[i] <= 10^6
*/

class Solution {
 public:
  long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
    auto check = [&mountainHeight, &workerTimes](long long time) {
      int left_h = mountainHeight;
      for (int t : workerTimes) {
        left_h -= ((int)sqrt(time / t * 8 + 1) - 1) / 2;
        if (left_h <= 0) {
          return true;
        }
      }
      return false;
    };

    long long left = 1;
    int max_t = *max_element(workerTimes.begin(), workerTimes.end());
    int h = (mountainHeight - 1) / workerTimes.size() + 1;
    long long right = (long long)max_t * h * (h + 1) / 2;
    while (left <= right) {
      long long mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};