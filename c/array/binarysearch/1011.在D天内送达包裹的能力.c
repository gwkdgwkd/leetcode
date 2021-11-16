// 二分查找
bool canFinish(int* weights, int weightsSize, int days, int weight) {
  int dsum = 1;
  int tmp = 0;

  for (int i = 0; i < weightsSize; ++i) {
    if (weight - tmp >= weights[i]) {
      tmp += weights[i];
    } else {
      dsum++;
      tmp = weights[i];
    }
  }

  return dsum <= days;
}
int shipWithinDays(int* weights, int weightsSize, int days) {
  int left = 0;
  int right = 0;
  for (int i = 0; i < weightsSize; ++i) {
    left = fmax(left, weights[i]);
    right += weights[i];
  }

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (canFinish(weights, weightsSize, days, mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
}