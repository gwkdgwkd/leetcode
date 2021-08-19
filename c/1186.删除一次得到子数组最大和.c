/*
 * @lc app=leetcode.cn id=1186 lang=c
 *
 * [1186] 删除一次得到子数组最大和
 */

// @lc code=start

// dp[][0]：没删除过元素
// dp[][1]：删除过元素
// dp[i][0] = max(arr[i], dp[i-1][0] + arr[i])
// dp[i][1] = max(dp[i-1][0], dp[i-1][1] + arr[i])
int max(int a, int b) { return a > b ? a : b; }
int maximumSum(int* arr, int arrSize) {
  int a, b, res;
  a = 0;         // 删除过
  b = arr[0];    // 没删除过
  res = arr[0];  // 记录最大值
  for (int i = 1; i < arrSize; i++) {
    // printf("%d %d %d\n", a, b, res);
    a = max(a + arr[i], b);
    b = max(b + arr[i], arr[i]);
    res = max(res, a);
    res = max(res, b);
  }
  return res;
}

// @lc code=end
