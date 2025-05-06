/*
给一个从0开始的排列nums（下标也从0开始）。
请构建一个同样长度的数组ans，其中，对于每个i（0 <= i < nums.length），
都满足ans[i] = nums[nums[i]]。返回构建好的数组ans。
从0开始的排列nums是一个由[0,nums.length - 1]的不同整数组成的数组。

示例 1：
输入：nums = [0,2,1,5,3,4]
输出：[0,1,2,4,5,3]
解释：数组ans构建如下：
     ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]],
            nums[nums[3]], nums[nums[4]], nums[nums[5]]]
         = [nums[0], nums[2], nums[1], nums[5], nums[3], nums[4]]
         = [0,1,2,4,5,3]

示例2：
输入：nums = [5,0,1,2,3,4]
输出：[4,5,0,1,2,3]
解释：数组ans构建如下：
     ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]],
            nums[nums[3]], nums[nums[4]], nums[nums[5]]]
         = [nums[5], nums[0], nums[1], nums[2], nums[3], nums[4]]
         = [4,5,0,1,2,3]


提示：
1 <= nums.length <= 1000
0 <= nums[i] < nums.length
nums中的元素互不相同

进阶：能在不使用额外空间的情况下解决此问题吗（即 O(1) 内存）？
*/

class Solution {
 public:
  vector<int> buildArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);

    for (int i = 0; i < n; ++i) {
      ans[i] = (nums[nums[i]]);
    }
    return ans;
  }
};

class Solution {
  // 时间复杂度：O(n)，其中n是nums的长度，虽然写了个二重循环，
  //           但每个数都恰好标记成负数一次，所以总循环次数是O(n)的。
  // 空间复杂度：O(1)。

 public:
  vector<int> buildArray(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
      int x = nums[i];
      if (x < 0) {  // 已搬家
        continue;
      }
      int cur = i;
      while (nums[cur] != i) {
        int nxt = nums[cur];
        nums[cur] = ~nums[nxt];  // 把下一个数搬过来，同时做标记（取反）
        cur = nxt;
      }
      nums[cur] = ~x;  // 对于这一组的最后一个数，把起点x=nums[i]搬过来
    }

    for (int i = 0; i < nums.size(); i++) {
      nums[i] = ~nums[i];  // 复原
    }
    return nums;
  }
};