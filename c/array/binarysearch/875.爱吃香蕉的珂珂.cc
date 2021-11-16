// 二分查找
bool canFinish(int* piles, int pilesSize, int speed, int h) {
  int sum = 0;
  for (int i = 0; i < pilesSize; ++i) {
    sum += (piles[i] + speed - 1) / speed;  // 向上取整
  }

  return sum <= h;
}
int minEatingSpeed(int* piles, int pilesSize, int h) {
  int left = 1;
  int right = 1;
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