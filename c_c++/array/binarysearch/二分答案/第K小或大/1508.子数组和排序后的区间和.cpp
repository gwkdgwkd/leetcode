/*
给一个数组nums，它包含n个正整数。
需要计算所有非空连续子数组的和，并将它们按升序排序，
得到一个新的包含n * (n + 1) / 2个数字的数组。
请返回在新数组中下标为left到right（下标从1开始）的所有数字和（包括左右端点）。
由于答案可能很大，请将它对10^9+7取模后返回。

示例1：
输入：nums = [1,2,3,4], n = 4, left = 1, right = 5
输出：13
解释：所有的子数组和为1, 3, 6, 10, 2, 5, 9, 3, 7, 4。
     将它们升序排序后，我们得到新的数组[1, 2, 3, 3, 4, 5, 6, 7, 9, 10]。
     下标从le = 1到ri = 5的和为1 + 2 + 3 + 3 + 4 = 13。

示例2：
输入：nums = [1,2,3,4], n = 4, left = 3, right = 4
输出：6
解释：给定数组与示例1一样，所以新数组为[1, 2, 3, 3, 4, 5, 6, 7, 9, 10]。
     下标从le = 3到ri = 4的和为3 + 3 = 6。

示例3：
输入：nums = [1,2,3,4], n = 4, left = 1, right = 10
输出：50


提示：
1 <= nums.length <= 10^3
nums.length == n
1 <= nums[i] <= 100
1 <= left <= right <= n * (n + 1) / 2
*/

class Solution {
 public:
  int rangeSum(vector<int>& nums, int n, int left, int right) {
    const int MODULO = 1000000007;
    int sumsLength = n * (n + 1) / 2;
    auto sums = vector<int>(sumsLength);
    int index = 0;
    for (int i = 0; i < n; i++) {
      int sum = 0;
      for (int j = i; j < n; j++) {
        sum += nums[j];
        sums[index++] = sum;
      }
    }
    sort(sums.begin(), sums.end());
    int ans = 0;
    for (int i = left - 1; i < right; i++) {
      ans = (ans + sums[i]) % MODULO;
    }
    return ans;
  }
};

class Solution {
 public:
  static constexpr int MODULO = 1000000007;

  int rangeSum(vector<int>& nums, int n, int left, int right) {
    vector<int> prefixSums = vector<int>(n + 1);
    prefixSums[0] = 0;
    for (int i = 0; i < n; i++) {
      prefixSums[i + 1] = prefixSums[i] + nums[i];
    }
    vector<int> prefixPrefixSums = vector<int>(n + 1);
    prefixPrefixSums[0] = 0;
    for (int i = 0; i < n; i++) {
      prefixPrefixSums[i + 1] = prefixPrefixSums[i] + prefixSums[i + 1];
    }
    return (getSum(prefixSums, prefixPrefixSums, n, right) -
            getSum(prefixSums, prefixPrefixSums, n, left - 1)) %
           MODULO;
  }

  int getSum(vector<int>& prefixSums, vector<int>& prefixPrefixSums, int n,
             int k) {
    int num = getKth(prefixSums, n, k);
    int sum = 0;
    int count = 0;
    for (int i = 0, j = 1; i < n; i++) {
      while (j <= n && prefixSums[j] - prefixSums[i] < num) {
        j++;
      }
      j--;
      sum +=
          prefixPrefixSums[j] - prefixPrefixSums[i] - prefixSums[i] * (j - i);
      sum %= MODULO;
      count += j - i;
    }
    sum += num * (k - count);
    return sum;
  }

  int getKth(vector<int>& prefixSums, int n, int k) {
    int low = 0, high = prefixSums[n];
    while (low < high) {
      int mid = (high - low) / 2 + low;
      int count = getCount(prefixSums, n, mid);
      if (count < k) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    return low;
  }

  int getCount(vector<int>& prefixSums, int n, int x) {
    int count = 0;
    for (int i = 0, j = 1; i < n; i++) {
      while (j <= n && prefixSums[j] - prefixSums[i] <= x) {
        j++;
      }
      j--;
      count += j - i;
    }
    return count;
  }
};