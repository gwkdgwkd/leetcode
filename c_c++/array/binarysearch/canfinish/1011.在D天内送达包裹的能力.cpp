/*
传送带上的包裹必须在days天内从一个港口运送到另一个港口。
传送带上的第i个包裹的重量为weights[i]。
每一天，我们都会按给出重量（weights）的顺序往传送带上装载包裹。
我们装载的重量不会超过船的最大运载重量。
返回能在days天内将传送带上的所有包裹送达的船的最低运载能力。

示例1：
输入：weights = [1,2,3,4,5,6,7,8,9,10], days = 5
输出：15
解释：
船舶最低载重15就能够在5天内送达所有包裹，如下所示：
第1天：1, 2, 3, 4, 5
第2天：6, 7
第3天：8
第4天：9
第5天：10
请注意，货物必须按照给定的顺序装运，
因此使用载重能力为14的船舶并将包装分成(2,3,4,5),
(1,6,7),(8),(9),(10)是不允许的。

示例2：
输入：weights = [3,2,2,4,1,4], days = 3
输出：6
解释：
船舶最低载重6就能够在3天内送达所有包裹，如下所示：
第1天：3, 2
第2天：2, 4
第3天：1, 4

示例3：
输入：weights = [1,2,3,1,1], days = 4
输出：3
解释：
第1天：1
第2天：2
第3天：3
第4天：1, 1

提示：
1 <= days <= weights.length <= 5 * 10^4
1 <= weights[i] <= 500
*/

// 二分查找
bool canFinish(int* weights, int weightsSize, int days, int weight) {
  int dsum = 1;
  int tmp = 0;

  for (int i = 0; i < weightsSize; ++i) {
    if (weight - tmp >= weights[i]) {
      tmp += weights[i];
    } else {
      dsum++;
      tmp = weights[i];
    }
  }

  return dsum <= days;
}
int shipWithinDays(int* weights, int weightsSize, int days) {
  int left = 0;
  int right = 0;
  for (int i = 0; i < weightsSize; ++i) {
    left = fmax(left, weights[i]);
    right += weights[i];
  }

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (canFinish(weights, weightsSize, days, mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
}

class Solution {
 public:
  bool canFinish(vector<int>& weights, int days, int weight) {
    int sum = 1;
    int tmp = 0;
    for (const auto& i : weights) {
      if (weight - tmp >= i) {
        tmp += i;
      } else {
        ++sum;
        tmp = i;
      }
    }

    return sum <= days;
  }
  int shipWithinDays(vector<int>& weights, int days) {
    int left = 0;
    int right = 0;
    for (const auto& i : weights) {
      left = max(left, i);
      right += i;
    }

    while (left < right) {  // 左闭右开区间，left==right不合理
      int mid = left + (right - left) / 2;
      if (canFinish(weights, days, mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};

class Solution {
 public:
  int shipWithinDays(vector<int>& weights, int days) {
    auto canFinish = [&weights, &days](int weight_max) {
      int d = 1;
      int tmp = 0;
      for (auto weight : weights) {
        if (tmp + weight <= weight_max) {
          tmp += weight;
        } else {
          ++d;
          tmp = weight;
        }
      }
      return d <= days;
    };

    int left = 0;
    int right = 0;
    for (auto weight : weights) {
      left = max(weight, left);
      right += weight;
    }

    while (left <= right) {  // 左闭右闭区间，left==right合理
      int mid = left + (right - left) / 2;
      if (canFinish(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};