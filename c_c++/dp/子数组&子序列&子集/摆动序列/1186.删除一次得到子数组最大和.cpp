/*
给你一个整数数组，
返回它的某个非空子数组（连续元素）在执行一次可选的删除操作后，
所能得到的最大元素总和。
换句话说，你可以从原数组中选出一个子数组，
并可以决定要不要从中删除一个元素（只能删一次哦），
（删除后）子数组中至少应当有一个元素，
然后该子数组（剩下）的元素总和是所有子数组之中最大的。
注意，删除一个元素后，子数组不能为空。

示例1：
输入：arr = [1,-2,0,3]
输出：4
解释：可以选出[1, -2, 0, 3]，然后删掉-2，
     这样得到[1, 0, 3]，和最大。

示例2：
输入：arr = [1,-2,-2,3]
输出：3
解释：我们直接选出[3]，这就是最大和。

示例3：
输入：arr = [-1,-1,-1,-1]
输出：-1
解释：最后得到的子数组不能为空，
     所以不能选择[-1]并从中删去-1来得到0。
     我们应该直接选择[-1]，或者选择[-1, -1]再从中删去一个-1。

提示：
1 <= arr.length <= 10^5
-10^4 <= arr[i] <= 10^4
*/

int maximumSum(int* arr, int arrSize) {
  int dp[arrSize][2];
  // dp[i][0]：以i结尾的子数组没有删除元素时的最大和
  // dp[i][1]：以i结尾的子数组删除过元素的最大和
  dp[0][0] = arr[0];   // 没删除过元素，最大和等于arr[0]
  dp[0][1] = 0;        // 只有一个元素，删除过，最大和为0
  int max = dp[0][0];  // 只有一个元素，不能删除，所以max=dp[0][0]

  for (int i = 1; i < arrSize; ++i) {
    // 没删除元素的的最大和等于下面2个中较大的：
    // 1.当前元素，当做子数组的第一个元素
    // 2.以nums[i-1]结尾的子数组加上当前元素nums[i]
    dp[i][0] = fmax(arr[i], dp[i - 1][0] + arr[i]);
    // 删除元素的的最大和等于下面2个中较大的：
    // 1.在以nums[i-1]结尾的元素中已经删除过了，当前元素被选择
    // 2.以nums[i-1]结尾的子数组中没有删除过，当前元素被删除
    dp[i][1] = fmax(dp[i - 1][1] + arr[i], dp[i - 1][0]);
    max = fmax(max, fmax(dp[i][0], dp[i][1]));
  }

  return max;
}

int maximumSum(int* arr, int arrSize) {
  int dp[2];
  dp[0] = arr[0];  // 没删除过
  dp[1] = 0;       // 删除过
  int max = dp[0];

  for (int i = 1; i < arrSize; ++i) {
    dp[1] = fmax(dp[1] + arr[i], dp[0]);   // 依赖dp[0]，先计算
    dp[0] = fmax(arr[i], dp[0] + arr[i]);  // 不依赖dp[i]
    max = fmax(max, fmax(dp[0], dp[1]));
  }

  return max;
}

class Solution {
 public:
  int maximumSum(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = arr[0];
    dp[0][1] = 0;
    int ans = dp[0][0];
    for (int i = 1; i < n; ++i) {
      dp[i][0] = max(dp[i - 1][0] + arr[i], arr[i]);
      dp[i][1] = max(dp[i - 1][1] + arr[i], dp[i - 1][0]);
      ans = max(ans, max(dp[i][0], dp[i][1]));
    }

    return ans;
  }
};
