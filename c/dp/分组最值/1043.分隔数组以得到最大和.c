/*
 * @lc app=leetcode.cn id=1043 lang=c
 *
 * [1043] 分隔数组以得到最大和
 */

// @lc code=start

// 动态规划
// 「将数组分割为m段，求……」是动态规划题目常见的问法。
int maxSumAfterPartitioning(int* arr, int arrSize, int k) {
  // dp[i]：数组的前i个数即nums[0,1...i−1]，被切了Y−1刀，分割成Y个数组，满足每个数组的个数最大值不超过K，每个数组的值变成最大值，分割后的最大和。
  int dp[arrSize + 1];
  memset(dp, 0, sizeof(dp));
  // dp[0] = 0;

  for (int i = 1; i <= arrSize; ++i) {
    int tempMax = arr[i - 1];
    // printf("%d: %d\n", i - 1, tempMax);
    for (int j = 1; j <= k; ++j) {
      // printf("  %d: ", j);
      if (i >= j) {
        // printf("[%d %d]", tempMax, arr[i - j]);
        tempMax = fmax(tempMax, arr[i - j]);
        // printf("%d, [%d %d]", tempMax, dp[i], dp[i - j] + tempMax * j);
        dp[i] = fmax(dp[i], dp[i - j] + tempMax * j);
        // printf("%d", dp[i]);
      }
      printf("\n");
    }
  }

  // for (int i = 0; i <= arrSize; ++i) {
  //   printf("%d ", dp[i]);
  // }
  // printf("\n");
  // [1,15,7,9,2,5,10]
  // 0: 1
  //   1: [1 1]1, [0 1]1
  //   2:
  //   3:
  // 1: 15
  //   1: [15 15]15, [0 16]16
  //   2: [15 1]15, [16 30]30
  //   3:
  // 2: 7
  //   1: [7 7]7, [0 37]37
  //   2: [7 15]15, [37 31]37
  //   3: [15 1]15, [37 45]45
  // 3: 9
  //   1: [9 9]9, [0 54]54
  //   2: [9 7]9, [54 48]54
  //   3: [9 15]15, [54 46]54
  // 4: 2
  //   1: [2 2]2, [0 56]56
  //   2: [2 9]9, [56 63]63
  //   3: [9 7]9, [63 57]63
  // 5: 5
  //   1: [5 5]5, [0 68]68
  //   2: [5 2]5, [68 64]68
  //   3: [5 9]9, [68 72]72
  // 6: 10
  //   1: [10 10]10, [0 82]82
  //   2: [10 5]10, [82 83]83
  //   3: [10 2]10, [83 84]84
  // 0 1 30 45 54 63 72 84

  return dp[arrSize];
}

// @lc code=end
