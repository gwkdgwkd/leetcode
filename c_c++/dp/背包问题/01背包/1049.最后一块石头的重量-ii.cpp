/*
有一堆石头，用整数数组stones表示。其中stones[i]表示第i块石头的重量。
每一回合，从中选出任意两块石头，然后将它们一起粉碎。
假设石头的重量分别为x和y，且x <= y。那么粉碎的可能结果如下：
如果x == y，那么两块石头都会被完全粉碎；
如果x != y，那么重量为x的石头将会完全粉碎，而重量为y的石头新重量为y-x。
最后，最多只会剩下一块石头。返回此石头最小的可能重量。如果没有石头剩下，就返回0。

示例1：
输入：stones = [2,7,4,1,8,1]
输出：1
解释：
组合2和4，得到2，所以数组转化为[2,7,1,8,1]，
组合7和8，得到1，所以数组转化为[2,1,1,1]，
组合2和1，得到1，所以数组转化为[1,1,1]，
组合1和1，得到0，所以数组转化为[1]，这就是最优值。

示例2：
输入：stones = [31,26,33,21,40]
输出：5

提示：
1 <= stones.length <= 30
1 <= stones[i] <= 100
*/

// 动态规划，0-1背包问题
int lastStoneWeightII(int* stones, int stonesSize) {
  int sum = 0;
  for (int i = 0; i < stonesSize; ++i) {
    sum += stones[i];
  }
  int target = sum / 2;  // 想到这个是难点
  int dp[stonesSize + 1][target + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= stonesSize; ++i) {
    for (int j = 0; j <= target; ++j) {
      if (stones[i - 1] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] =
            fmax(dp[i - 1][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
      }
    }
  }

  // for(int i = 0; i <= stonesSize; ++i) {
  //   for(int j = 0; j <= target; ++j) {
  //       printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }

  return sum - 2 * dp[stonesSize][target];
}

// 动态规划，使用01背包的方式计算
int lastStoneWeightII(int* stones, int stonesSize) {
  if (stonesSize == 0) {
    return 0;
  }
  if (stonesSize == 1) {
    return stones[0];
  }

  int sum = 0;
  for (int i = 0; i < stonesSize; ++i) {
    sum += stones[i];
  }
  int target = sum / 2;  // target向下取整，所以是下面的sum2

  int dp[target + 1];  // dp[i]背包容量为i时能选取的最大石头的大小和
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < stonesSize; ++i) {
    for (int j = target; j >= stones[i]; --j) {
      dp[j] = fmax(dp[j], dp[j - stones[i]] + stones[i]);
    }
  }

  // 可以把这堆石头分成大小差不多的两堆石头，分别为sum1和sum2，答案是abs(sum1-sum2)。
  // 知道sum1，就知道了sum2=sum-sum1。
  // abs((sum-sum1)-sum1)就是最后答案，也就是sum-2*dp[target]
  return sum - 2 * dp[target];
}

// 动态规划
int lastStoneWeightII(int* stones, int stonesSize) {
  int sum = 0;
  for (int i = 0; i < stonesSize; ++i) {
    sum += stones[i];
  }

  int target = sum / 2;

  int dp[stonesSize][target + 1];
  memset(dp, 0, sizeof(dp));
  for (int j = stones[0]; j <= target; ++j) {
    dp[0][j] = stones[0];
  }

  for (int i = 1; i < stonesSize; ++i) {
    for (int j = 0; j <= target; ++j) {
      if (stones[i] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = fmax(dp[i - 1][j], dp[i - 1][j - stones[i]] + stones[i]);
      }
    }
  }

  return sum - 2 * dp[stonesSize - 1][target];
}

int lastStoneWeightII(int* stones, int stonesSize) {
  int sum = 0;
  for (int i = 0; i < stonesSize; ++i) {
    sum += stones[i];
  }

  int target = sum / 2;

  int dp[target + 1];
  memset(dp, 0, sizeof(dp));
  // 初始化第一行
  for (int j = stones[0]; j <= target; ++j) {
    dp[j] = stones[0];
  }

  // 第一行已经初始化，从第一行开始遍历
  for (int i = 1; i < stonesSize; ++i) {
    for (int j = target; j >= stones[i]; --j) {
      dp[j] = fmax(dp[j], dp[j - stones[i]] + stones[i]);
    }
  }

  return sum - 2 * dp[target];
}

class Solution {
 public:
  int lastStoneWeightII(vector<int>& stones) {
    int sum = accumulate(stones.begin(), stones.end(), 0);
    int target = sum / 2;

    vector<int> dp(target + 1, 0);
    for (int i = 0; i < stones.size(); ++i) {
      for (int j = target; j >= stones[i]; --j) {
        dp[j] = fmax(dp[j], dp[j - stones[i]] + stones[i]);
      }
    }

    return sum - 2 * dp[target];
  }
};
