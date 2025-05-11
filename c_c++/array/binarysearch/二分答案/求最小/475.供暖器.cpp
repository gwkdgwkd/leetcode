/*
冬季已经来临。设计一个有固定加热半径的供暖器向所有房屋供暖。
在加热器的加热半径范围内的每个房屋都可以获得供暖。
现在，给出位于一条水平线上的房屋houses和供暖器heaters的位置，
请找出并返回可以覆盖所有房屋的最小加热半径。
注意：所有供暖器heaters都遵循半径标准，加热的半径也一样。

示例1:
输入: houses = [1,2,3], heaters = [2]
输出: 1
解释:
仅在位置2上有一个供暖器。如果我们将加热半径设为1，那么所有房屋就都能得到供暖。

示例2:
输入: houses = [1,2,3,4], heaters = [1,4]
输出: 1
解释:
在位置1,4上有两个供暖器。我们需要将加热半径设为1，这样所有房屋就都能得到供暖。

示例3：
输入：houses = [1,5], heaters = [2]
输出：3


提示：
1 <= houses.length, heaters.length <= 3 * 10^4
1 <= houses[i], heaters[i] <= 10^9
*/

class Solution {
 public:
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    auto check = [&houses, &heaters](int r) {
      int j = 0;  // 为啥写这里？
      for (int i = 0; i < houses.size(); ++i) {
        // int j = 0;  // 这里怎么会超时呢？
        while (j < heaters.size() &&
               (houses[i] < heaters[j] - r || houses[i] > heaters[j] + r)) {
          ++j;
        }
        if (j == heaters.size()) {
          return false;
        }
      }
      return true;
    };

    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());
    int left = 0;
    int right = max(heaters[heaters.size() - 1] - houses[0],
                    houses[houses.size() - 1] - heaters[0]);
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

// 排序 + 二分查找
class Solution {
 public:
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    int ans = 0;
    sort(heaters.begin(), heaters.end());
    for (int house : houses) {
      int j =
          upper_bound(heaters.begin(), heaters.end(), house) - heaters.begin();
      int i = j - 1;
      int rightDistance = j >= heaters.size() ? INT_MAX : heaters[j] - house;
      int leftDistance = i < 0 ? INT_MAX : house - heaters[i];
      int curDistance = min(leftDistance, rightDistance);
      ans = max(ans, curDistance);
    }
    return ans;
  }
};