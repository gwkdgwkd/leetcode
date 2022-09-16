#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 二维dp
int test1(int *weight, int *value, int size, int bagweight) {
  // 1.确定dp数组以及下标的含义：
  //   dp[i][j]表示从下标为0到i的物品里任意取，
  //   放进容量为j的背包，价值和最大是多少。
  int dp[size][bagweight + 1];
  // 3.dp数组如何初始化：
  //   如果背包容量j为0的话，即dp[i][0]，
  //   无论是选取哪些物品，背包价值总和一定为0；
  memset(dp, 0, sizeof(dp));
  //   由状态转移方程可以看出，i是由i-1推导出来，
  //   那么i为0的时候就一定要初始化。
  //   dp[0][j]存放weight[0]物品的时候，
  //   各个容量的背包所能存放的最大价值。
  //   明显j<weight[0]的时候，dp[0][j]应该是0，
  //   因为背包容量比weight[0]重量还小。
  //   dp预先初始化为0了，所以这一步可以省略：
  //   for (int j = 0; j < weight[0]; ++j) {
  //     dp[0][j] = 0;
  //   }
  //   当j>=weight[0]时，dp[0][j]应该是value[0]，
  //   因为背包容量可以放下weight[0]的物品：
  for (int j = weight[0]; j <= bagweight; ++j) {
    dp[0][j] = value[0];
  }
  //   其他下标初始化什么数值都可以，因为都会被覆盖。
  //   一开始统一把dp数组初始化为0，更方便一些。

  // 4.确定遍历顺序：先遍历物品还是先遍历背包重量呢？
  //   其实都可以，但是先遍历物品更好理解。
  for (int i = 1; i < size; ++i) {          // 遍历物品
    for (int j = 0; j <= bagweight; ++j) {  // 遍历背包容量
      // 2.确定递推公式
      if (j < weight[i]) {
        // 由dp[i-1][j]推出，即背包容量为j，
        // 里面不放物品i的最大价值，此时dp[i][j]就是dp[i-1][j]：
        dp[i][j] = dp[i - 1][j];
      } else {
        // dp[i-1][j-weight[i]]：
        // 为背包容量为j-weight[i]的时候不放物品i的最大价值；
        // dp[i-1][j-weight[i]]+value[i]：
        // 就是背包放物品i得到的最大价值；
        dp[i][j] = MAX(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
      }
    }
  }
  /*
  // dp[i][j]依赖左上角方向（正左和正上），所以先遍历容量后遍历物品也可以：
  for (int j = 0; j <= bagweight; ++j) {  // 遍历背包容量
    for (int i = 1; i < size; ++i) {      // 遍历物品
      if (j < weight[i]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = MAX(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
      }
    }
  }
  */

  // 5.举例推导dp数组
  // for (int i = 0; i < size; ++i) {
  //   for (int j = 0; j <= bagweight; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  //   0  15  15  15  15
  //   0   0   0  20  35
  //   0   0   0   0  35

  return dp[size - 1][bagweight];
}

// dp数组降维，滚动数组
int test2(int *weight, int *value, int size, int bagweight) {
  // 对于背包问题其实状态都是可以压缩的。
  // 在使⽤⼆维数组的时候，递推公式：
  // dp[i][j]=max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
  // 其实可以发现如果把dp[i-1]那⼀层拷⻉到dp[i]上，表达式完全可以是：
  // dp[i][j]=max(dp[i][j],dp[i][j-weight[i]]+value[i]);
  // 与其把dp[i-1]这⼀层拷⻉到dp[i]上，不如只⽤⼀个⼀维数组了，
  // 只⽤dp[j]，这是⼀个滚动数组。
  // 需要满⾜的条件是上⼀层可以重复利⽤，直接拷⻉到当前层。
  // 1.确定dp数组的定义：在⼀维dp数组中，
  //   dp[j]表示容量为j的背包，所装的物品价值可以最⼤为dp[j]。
  int dp[bagweight + 1];
  // 3.⼀维dp数组如何初始化
  //   dp[j]表示：容量为j的背包，所装的物品价值可以最⼤为dp[j]，
  //   那么dp[0]就应该是0，因为背包容量为0所背的物品的最⼤价值就是0。
  //   递推公式是选取价值最⼤的数，
  //   如果价值都是正整数那么⾮0下标都初始化为0就可以了，
  //   如果价值有负数，那么⾮0下标就要初始化为负⽆穷。
  memset(dp, 0, sizeof(dp));  // 假设价值都为正数
  // memset(dp, 0x80, sizeof(dp));  // int的极小值
  // dp[0] = 0;
  // 把第一行都初始化了也可以，下面遍历时从1开始：
  // for (int i = weight[0]; i <= bagweight; ++i) {
  //   dp[i] = value[0];
  // }

  // 4.⼀维dp数组遍历顺序
  //   代码中是先遍历物品嵌套遍历背包容量，
  //   那可不可以先遍历背包容量嵌套遍历物品呢？不可以！
  for (int i = 0; i < size; ++i) {
    // ⼆维dp遍历的时候，背包容量是从⼩到⼤，
    // ⽽⼀维dp遍历的时候，背包是从⼤到⼩。
    // 倒叙遍历是为了保证物品i只被放⼊⼀次！
    for (int j = bagweight; j >= weight[i]; --j) {
      // 2.⼀维dp数组的递推公式，相对于⼆维dp数组的写法，
      //   就是把dp[i][j]中i的维度去掉了。
      dp[j] = MAX(dp[j], dp[j - weight[i]] + value[i]);
      // 对于j<weight，二维数组为dp[i][j]=dp[i-1][j];
      // 一维数组为dp[j]=dp[j];所以这个分支可以忽略不写。
    }

    // 5.举例推导dp数组
    // for (int j = 0; j <= bagweight; ++j) {
    //   printf("%3d ", dp[j]);
    // }
    // printf("\n");
  }

  // 0  15  15  15  15
  // 0  15  15  20  35
  // 0  15  15  20  35

  return dp[bagweight];
}

#define SIZE 3
int main() {
  int weight[SIZE] = {1, 3, 4};
  int value[SIZE] = {15, 20, 30};
  int bagweight = 4;

  printf("%d\n", test1(weight, value, SIZE, bagweight));  // 35
  printf("%d\n", test2(weight, value, SIZE, bagweight));  // 35

  return 0;
}
