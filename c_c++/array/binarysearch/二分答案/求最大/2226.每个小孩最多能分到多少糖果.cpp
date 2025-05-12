/*
给一个下标从0开始的整数数组candies。
数组中的每个元素表示大小为candies[i]的一堆糖果。
可以将每堆糖果分成任意数量的子堆，但无法再将两堆合并到一起。
另给你一个整数k。需要将这些糖果分配给k个小孩，使每个小孩分到相同数量的糖果。
每个小孩可以拿走至多一堆糖果，有些糖果可能会不被分配。
返回每个小孩可以拿走的最大糖果数目。

示例1：
输入：candies = [5,8,6], k = 3
输出：5
解释：可以将candies[1]分成大小分别为5和3的两堆，然后把candies[2]分成大小分别为5和1的两堆。
     现在就有五堆大小分别为5、5、3、5和1的糖果。可以把3堆大小为5的糖果分给3个小孩。
     可以证明无法让每个小孩得到超过5颗糖果。

示例2：
输入：candies = [2,5], k = 11
输出：0
解释：总共有11个小孩，但只有7颗糖果，但如果要分配糖果的话，必须保证每个小孩至少能得到1颗糖果。
     因此，最后每个小孩都没有得到糖果，答案是0。


提示：
1 <= candies.length <= 10^5
1 <= candies[i] <= 10^7
1 <= k <= 10^12
*/

class Solution {
 public:
  int maximumCandies(vector<int>& candies, long long k) {
    auto check = [&candies, &k](int num) {
      long long sum = 0;
      for (int c : candies) {
        sum += c / num;
      }
      return sum >= k;
    };

    int left = 1;
    int right = *max_element(candies.begin(), candies.end());
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};

class Solution {
 public:
  int maximumCandies(vector<int>& candies, long long k) {
    // 判断每个小孩分到 i 个糖果时是否可以满足要求
    auto check = [&](int i) -> bool {
      long long res = 0;
      for (int c : candies) {
        res += c / i;
      }
      return res >= k;
    };

    // 二分查找
    int l = 1;
    int r = 1 + *max_element(candies.begin(), candies.end());
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l - 1;
  }
};

class Solution {
 public:
  int maximumCandies(vector<int>& candies, long long k) {
    auto check = [&](int low) -> bool {
      long long sum = 0;
      for (int c : candies) {
        sum += c / low;
      }

      return sum >= k;
    };

    long long avg = reduce(candies.begin(), candies.end(), 0LL) / k;
    int left = 0, right = min((long long)ranges::max(candies), avg) + 1;
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      (check(mid) ? left : right) = mid;
    }

    return left;
  }
};
