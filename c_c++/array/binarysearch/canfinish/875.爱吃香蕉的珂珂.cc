/*
珂珂喜欢吃香蕉，这里有N堆香蕉，第i堆中有piles[i]根香蕉。
警卫已经离开了，将在H小时后回来。
珂珂可以决定她吃香蕉的速度K（单位：根/小时）。
每个小时，她将会选择一堆香蕉，从中吃掉K根。
如果这堆香蕉少于K根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。
珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
返回她可以在H小时内吃掉所有香蕉的最小速度K（K为整数）。

示例1：
输入: piles = [3,6,7,11], H = 8
输出: 4

示例2：
输入: piles = [30,11,23,4,20], H = 5
输出: 30

示例3：
输入: piles = [30,11,23,4,20], H = 6
输出: 23

提示：
1 <= piles.length <= 10^4
piles.length <= H <= 10^9
1 <= piles[i] <= 10^9
*/

// 剑指OfferII073狒狒吃香蕉

// 二分查找
bool canFinish(int* piles, int pilesSize, int speed, int h) {
  int sum = 0;
  for (int i = 0; i < pilesSize; ++i) {
    sum += (piles[i] + speed - 1) / speed;  // 向上取整
  }

  return sum <= h;
}
int minEatingSpeed(int* piles, int pilesSize, int h) {
  int left = 1;   // 最小速度每小时吃1根
  int right = 1;  // 最大速度是piles中最大值
  for (int i = 0; i < pilesSize; ++i) {
    right = fmax(right, piles[i]);
  }

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (canFinish(piles, pilesSize, mid, h)) {  // 找到或在左边
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
}