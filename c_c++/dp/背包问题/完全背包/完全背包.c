#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 完全背包和01背包问题唯⼀不同的地⽅就是，每种物品有⽆限件。

int test1(int *weight, int *value, int size, int bagweight) {
  int dp[size][bagweight + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = weight[0]; i <= bagweight; ++i) {
    // 初始化与01背包不同，对于第一个物品，要尽量装，直到装不下时，才是dp中需要的值
    dp[0][i] = value[0] * (i / weight[0]);
  }

  for (int i = 1; i < size; ++i) {
    for (int j = 0; j <= bagweight; ++j) {
      if (j < weight[i]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        // 递推公式与01背包不同，选择当前物品i时：
        // 01背包要在不包括当前物品且重量为j-weight[i]的基础上，加上value[i]。
        // dp[i][j] = MAX(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
        // 完全背包要在包括当前物品且重量为j-weight[i]的基础上，加上value[i]。
        dp[i][j] = MAX(dp[i - 1][j], dp[i][j - weight[i]] + value[i]);
        // 01背包依赖dp[i-1][j]和dp[i-1][j-weight[i]]，即上和左上，所以一维dp的内层循环需要从右向左。
        // 完全背包依赖dp[i-1][j]和dp[i][j-weight[i]]，即上和左，所以一维dp的内层循环需要从左向右。
      }
    }
  }

  // for (int i = 0; i < size; ++i) {
  //   for (int j = 0; j <= bagweight; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // 0   0   0   0  35
  // 0  15  30  45  60
  // 0  15  30  46  61

  return dp[size - 1][bagweight];
}

int test2(int *weight, int *value, int size, int bagweight) {
  int dp[bagweight + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 0; i < size; ++i) {
    // 01背包内嵌的循环是从⼤到⼩遍历，为了保证每个物品仅被添加⼀次。
    // for (int j = bagweight; j >= weight[i]; --j) {
    // ⽽完全背包的物品是可以添加多次的，所以要从⼩到⼤去遍历，即：
    for (int j = weight[i]; j <= bagweight; ++j) {
      dp[j] = MAX(dp[j], dp[j - weight[i]] + value[i]);
    }

    // for (int j = 0; j <= bagweight; ++j) {
    //   printf("%3d ", dp[j]);
    // }
    // printf("\n");
  }
  // 0   0   0   0  35
  // 0  15  30  45  60
  // 0  15  30  46  61

  // 01背包中⼆维dp数组的两个for遍历的先后循序是可以颠倒了，
  // ⼀维dp数组的两个for循环先后循序⼀定是先遍历物品，再遍历背包容量。
  // 在完全背包中，对于⼀维dp数组来说，其实两个for循环嵌套顺序同样⽆所谓！
  // 因为dp[j]是根据下标j之前所对应的dp[j]计算出来的。
  // 只要保证下标j之前的dp[j]都是经过计算的就可以了。
  // for (int j = 0; j <= bagweight; ++j) {
  //   for (int i = 0; i < size; ++i) {
  //     if (j >= weight[i]) {
  //       dp[j] = MAX(dp[j], dp[j - weight[i]] + value[i]);
  //     }
  //   }
  // }

  return dp[bagweight];
}

#define SIZE 3
int main() {
  int weight[SIZE] = {4, 1, 3};
  int value[SIZE] = {35, 15, 46};
  int bagweight = 4;

  printf("%d\n", test1(weight, value, SIZE, bagweight));  // 61
  printf("%d\n", test2(weight, value, SIZE, bagweight));  // 61

  return 0;
}
