int findMax(int* arr, int end) {
  int res = 0;
  for (int i = 1; i <= end; ++i) {
    if (arr[res] < arr[i]) {
      res = i;
    }
  }
  return res;
}
void reversal(int* arr, int left, int right) {
  while (left < right) {
    int tmp = arr[left];
    arr[left] = arr[right];
    arr[right] = tmp;
    ++left;
    --right;
  }

  return;
}
int* pancakeSort(int* arr, int arrSize, int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * arrSize * 2);
  *returnSize = 0;
  for (int i = arrSize - 1; i >= 0; --i) {
    int maxIndex = findMax(arr, i);  // 找大最大的元素
    if (maxIndex == i) {
      continue;
    }
    if (maxIndex > 0) {
      // 先把最大的翻到最上面
      reversal(arr, 0, maxIndex);
      res[(*returnSize)++] = maxIndex + 1;
    }
    // 再把最大的翻到最底下
    reversal(arr, 0, i);
    res[(*returnSize)++] = i + 1;
  }

  return res;
}