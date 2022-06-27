/*
在一条环路上有n个加油站，其中第i个加油站有汽油gas[i]升。
你有一辆油箱容量无限的的汽车，从第i个加油站开往第i+1个加油站需要消耗汽油cost[i]升。
你从其中的一个加油站出发，开始时油箱为空。
给定两个整数数组gas和cost，如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回-1。
如果存在解，则保证它是唯一的。

示例1:
输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
输出: 3
解释:
从3号加油站(索引为3处)出发，可获得4升汽油。此时油箱= 0 + 4 = 4升汽油
开往4号加油站，此时油箱4 - 1 + 5 = 8升汽油
开往0号加油站，此时油箱8 - 2 + 1 = 7升汽油
开往1号加油站，此时油箱7 - 3 + 2 = 6升汽油
开往2号加油站，此时油箱6 - 4 + 3 = 5升汽油
开往3号加油站，你需要消耗5升汽油，正好足够你返回到3号加油站。
因此，3可为起始索引。

示例2:
输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从0号或1号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从2号加油站出发，可以获得4升汽油。此时油箱= 0 + 4 = 4升汽油，
开往0号加油站，此时油箱4 - 3 + 2 = 3升汽油，
开往1号加油站，此时油箱3 - 3 + 3 = 3升汽油，
你无法返回2号加油站，因为返程需要消耗4升汽油，但是你的油箱只有3升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。

提示:
gas.length == n
cost.length == n
1 <= n <= 10^5
0 <= gas[i], cost[i] <= 10^4
*/

// 暴力法
// 时间复杂度：O(n^2)
// 空间复杂度：O(n)
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
  for (int i = 0; i < costSize; ++i) {
    int rest = gas[i] - cost[i];
    int index = (i + 1) % costSize;
    while (rest > 0 && index != i) {
      rest += gas[index] - cost[index];
      index = (index + 1) % costSize;
    }
    if (rest >= 0 && index == i) {
      return i;
    }
  }
  return -1;
}

// 不认为这种方式是贪心算法，因为没有找出局部最优，而是直接从全局最优的角度上思考问题
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
  // 情况一：如果gas的总和小于cost总和，那么无论从哪里出发，一定是跑不了一圈的
  // 情况二：rest[i]=gas[i]-cost[i]为一天剩下的油，i从0开始计算累加到最后一站，
  //        如果累加没有出现负数，说明从0出发，油就没有断过，那么0就是起点。
  // 情况三：如果累加的最小值是负数，汽车就要从非0节点出发，从后向前，
  //        看哪个节点能这个负数填平，能把这个负数填平的节点就是出发节点。
  int curSum = 0;
  int min = INT_MAX;  // 从起点出发，油箱里的油量最小值
  for (int i = 0; i < gasSize; i++) {
    int rest = gas[i] - cost[i];
    curSum += rest;
    if (curSum < min) {
      min = curSum;
    }
  }
  if (curSum < 0) return -1;  // 情况1
  if (min >= 0)
    return 0;  // 情况2
               // 情况3
  for (int i = gasSize - 1; i >= 0; i--) {
    int rest = gas[i] - cost[i];
    min += rest;
    if (min >= 0) {
      return i;
    }
  }
  return -1;
}

// 贪心算法
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
  int curSum = 0;
  int totalSum = 0;
  int start = 0;
  // i从0开始累加rest[i]，和记为curSum，一旦curSum小于零，
  // 说明[0, i]区间都不能作为起始位置，起始位置从i+1算起，再从0计算curSum。
  for (int i = 0; i < gasSize; i++) {
    curSum += gas[i] - cost[i];
    totalSum += gas[i] - cost[i];
    if (curSum < 0) {  // 当前累加rest[i]和curSum一旦小于0
      start = i + 1;   // 起始位置更新为i+1
      curSum = 0;      // curSum从0开始
    }
  }
  if (totalSum < 0) return -1;  // 说明怎么走都不可能跑一圈了
  return start;
}