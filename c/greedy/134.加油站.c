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
  // 情况二：rest[i] = gas[i]-cost[i]为一天剩下的油，i从0开始计算累加到最后一站，如果累加没有出现负数，说明从0出发，油就没有断过，那么0就是起点。
  // 情况三：如果累加的最小值是负数，汽车就要从非0节点出发，从后向前，看哪个节点能这个负数填平，能把这个负数填平的节点就是出发节点。
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
  // i从0开始累加rest[i]，和记为curSum，一旦curSum小于零，说明[0, i]区间都不能作为起始位置，起始位置从i+1算起，再从0计算curSum。
  for (int i = 0; i < gasSize; i++) {
    curSum += gas[i] - cost[i];
    totalSum += gas[i] - cost[i];
    if (curSum < 0) {  // 当前累加rest[i]和 curSum一旦小于0
      start = i + 1;   // 起始位置更新为i+1
      curSum = 0;      // curSum从0开始
    }
  }
  if (totalSum < 0) return -1;  // 说明怎么走都不可能跑一圈了
  return start;
}