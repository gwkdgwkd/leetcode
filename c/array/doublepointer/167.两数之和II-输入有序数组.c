// 双指针
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
  int left = 0;
  int right = numbersSize - 1;

  int* res = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;
  while (left < right) {
    int sum = numbers[left] + numbers[right];
    if (sum == target) {
      res[0] = left + 1;
      res[1] = right + 1;
      return res;
    } else if (sum < target) {
      left++;
    } else if (sum > target) {
      right--;
    }
  }

  return res;
}