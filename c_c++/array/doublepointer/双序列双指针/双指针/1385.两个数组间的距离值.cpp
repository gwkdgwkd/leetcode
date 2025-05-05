/*
给两个整数数组arr1，arr2和一个整数d，请返回两个数组之间的距离值。
距离值定义为符合此距离要求的元素数目：
对于元素arr1[i]，不存在任何元素arr2[j]满足|arr1[i]-arr2[j]| <= d。

示例1：
输入：arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
输出：2
解释：对于arr1[0]=4我们有：
     |4-10|=6 > d=2
     |4-9|=5 > d=2
     |4-1|=3 > d=2
     |4-8|=4 > d=2
     所以arr1[0]=4符合距离要求

     对于arr1[1]=5我们有：
     |5-10|=5 > d=2
     |5-9|=4 > d=2
     |5-1|=4 > d=2
     |5-8|=3 > d=2
     所以arr1[1]=5也符合距离要求

     对于arr1[2]=8我们有：
     |8-10|=2 <= d=2
     |8-9|=1 <= d=2
     |8-1|=7 > d=2
     |8-8|=0 <= d=2
     存在距离小于等于2的情况，不符合距离要求
     故而只有arr1[0]=4和arr1[1]=5两个符合距离要求，距离值为2

示例2：
输入：arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
输出：2

示例3：
输入：arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
输出：1


提示：
1 <= arr1.length, arr2.length <= 500
-10^3 <= arr1[i], arr2[j] <= 10^3
0 <= d <= 100
*/

// 暴力还是双指针？
class Solution {
 public:
  int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
    int n = arr1.size();
    int m = arr2.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int j = 0;
      while (j < m) {
        if (abs(arr1[i] - arr2[j]) <= d) {
          break;
        }
        ++j;
      }
      if (j == m) {
        ++ans;
      }
    }
    return ans;
  }
};

// 排序+双指针
class Solution {
 public:
  int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
    ranges::sort(arr1);
    ranges::sort(arr2);
    int ans = 0, j = 0;

    // 遍历arr1​，设x=arr1​[i]，
    // 同时用另一个指针j维护最小的满足arr2​[j]≥x−d的数的下标。
    // 如果发现arr2​[j]>x+d，那么arr2​没有在[x−d,x+d]中的数，答案加一。
    for (int x : arr1) {
      while (j < arr2.size() && arr2[j] < x - d) {
        j++;
      }
      if (j == arr2.size() || arr2[j] > x + d) {
        ans++;
      }
    }
    return ans;
  }
};

// 排序+二分查找
class Solution {
 public:
  int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
    ranges::sort(arr2);
    int ans = 0;

    // 遍历arr1​，设x=arr1​[i]，在arr2​中二分查找≥x−d的最小的数y。
    // 如果y不存在，或者y>x+d，那么说明arr2​没有在[x−d,x+d]中的数，答案加一。
    for (int x : arr1) {
      auto it = ranges::lower_bound(arr2, x - d);
      if (it == arr2.end() || *it > x + d) {
        ans++;
      }
    }
    return ans;
  }
};
