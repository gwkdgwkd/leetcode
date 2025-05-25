/*
给一个整数数组arr，以及a、b 、c三个整数。请你统计其中好三元组的数量。
如果三元组(arr[i], arr[j], arr[k])满足下列全部条件，则认为它是一个好三元组。
0 <= i < j < k < arr.length
|arr[i] - arr[j]| <= a
|arr[j] - arr[k]| <= b
|arr[i] - arr[k]| <= c
其中|x|表示x的绝对值。
返回好三元组的数量。

示例1：
输入：arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
输出：4
解释：一共有4个好三元组：[(3,0,1), (3,0,1), (3,1,1), (0,1,1)]。

示例2：
输入：arr = [1,1,2,2,3], a = 0, b = 0, c = 1
输出：0
解释：不存在满足所有条件的三元组。


提示：
3 <= arr.length <= 100
0 <= arr[i] <= 1000
0 <= a, b, c <= 1000
*/

// 暴力
class Solution {
 public:
  int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
    int n = arr.size();
    int ans = 0;
    for (int j = 1; j < n - 1; ++j) {
      for (int i = 0; i < j; ++i) {
        for (int k = j + 1; k < n; ++k) {
          if (abs(arr[i] - arr[j]) <= a && abs(arr[j] - arr[k]) <= b &&
              abs(arr[i] - arr[k]) <= c) {
            ++ans;
          }
        }
      }
    }
    return ans;
  }
};

// 前缀和
class Solution {
 public:
  int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
    int n = arr.size(), mx = ranges::max(arr), ans = 0;
    vector<int> s(mx + 2);  // cnt 数组的前缀和
    for (int j = 0; j < arr.size(); j++) {
      int y = arr[j];
      for (int k = j + 1; k < arr.size(); k++) {
        int z = arr[k];
        if (abs(y - z) > b) {
          continue;
        }
        int l = max({y - a, z - c, 0});
        int r = min({y + a, z + c, mx});
        ans += max(s[r + 1] - s[l], 0);  // 如果 l > r + 1，s[r + 1] -
        s[l] 可能是负数
      }
      for (int v = y + 1; v < mx + 2; v++) {
        s[v]++;  // 把 y 加到 cnt 数组中，更新所有受到影响的前缀和
      }
    }
    return ans;
  }
};

// 排序 + 枚举中间 + 三指针
class Solution {
 public:
  int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
    vector<int> idx(arr.size());
    ranges::iota(idx, 0);
    ranges::sort(idx, {}, [&](int i) { return arr[i]; });

    int ans = 0;
    for (int j : idx) {
      int y = arr[j];
      vector<int> left, right;
      for (int i : idx) {
        if (i < j && abs(arr[i] - y) <= a) {
          left.push_back(arr[i]);
        }
      }
      for (int k : idx) {
        if (k > j && abs(arr[k] - y) <= b) {
          right.push_back(arr[k]);
        }
      }

      int k1 = 0, k2 = 0;
      for (int x : left) {
        while (k2 < right.size() && right[k2] <= x + c) {
          k2++;
        }
        while (k1 < right.size() && right[k1] < x - c) {
          k1++;
        }
        ans += k2 - k1;
      }
    }
    return ans;
  }
};