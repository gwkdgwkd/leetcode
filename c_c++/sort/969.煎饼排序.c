/*
给你一个整数数组arr，请使用煎饼翻转完成对数组的排序。
一次煎饼翻转的执行过程如下：
选择一个整数k，1 <= k <= arr.length
反转子数组arr[0...k-1]（下标从0开始）
例如，arr=[3,2,1,4]，选择k=3进行一次煎饼翻转，反转子数组[3,2,1]，得到arr=[1,2,3,4]。
以数组形式返回能使arr有序的煎饼翻转操作所对应的k值序列。
任何将数组排序且翻转次数在10 * arr.length范围内的有效答案都将被判断为正确。

示例1：
输入：[3,2,4,1]
输出：[1,2,4,3]
解释：
我们执行4次煎饼翻转，k值分别为4，2，4和3。
初始状态arr = [3, 2, 4, 1]
第一次翻转后（k = 4）：arr = [1, 4, 2, 3]
第二次翻转后（k = 2）：arr = [4, 1, 2, 3]
第三次翻转后（k = 4）：arr = [3, 2, 1, 4]
第四次翻转后（k = 3）：arr = [1, 2, 3, 4]，此时已完成排序。

示例2：
输入：[1,2,3]
输出：[]
解释：
输入已经排序，因此不需要翻转任何内容。
请注意，其他可能的答案，如[3，3]，也将被判断为正确。

提示：
1 <= arr.length <= 100
1 <= arr[i] <= arr.length
arr中的所有整数互不相同（即arr是从1到arr.length整数的一个排列）
*/

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