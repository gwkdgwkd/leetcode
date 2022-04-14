/*
给你一个整数数组nums，设计算法来打乱一个没有重复元素的数组。
打乱后，数组的所有排列应该是等可能的。
实现Solution class:
Solution(int[] nums) 使用整数数组nums初始化对象
int[] reset() 重设数组到它的初始状态并返回
int[] shuffle() 返回数组随机打乱后的结果

示例1：
输入
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
输出
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]
解释
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();
打乱数组[1,2,3]并返回结果。任何[1,2,3]的排列返回的概率应该相同。例如，返回[3, 1, 2]
solution.reset();
重设数组到它的初始状态[1, 2, 3]。返回[1, 2, 3]
solution.shuffle();
随机返回数组[1, 2, 3]打乱后的结果。例如，返回[1, 3, 2]

提示：
1 <= nums.length <= 200
-10^6 <= nums[i] <= 10^6
nums中的所有元素都是唯一的
最多可以调用5 * 10^4次reset和shuffle
*/

typedef struct {
  int* array;
  int* origin;
  int size;
} Solution;
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  return;
}
int randomInt(int min, int max) {
  int ret = rand() % (max - min + 1) + min;
  return ret;
}
Solution* solutionCreate(int* nums, int numsSize) {
  Solution* new = malloc(sizeof(Solution));
  new->size = numsSize;
  new->array = malloc(sizeof(int) * numsSize);
  new->origin = malloc(sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; i++) {
    new->array[i] = nums[i];
    new->origin[i] = nums[i];
  }
  return new;
}
int* solutionReset(Solution* obj, int* retSize) {
  *retSize = obj->size;
  for (int i = 0; i < *retSize; i++) {
    obj->array[i] = obj->origin[i];
  }
  return obj->array;
}
int* solutionShuffle(Solution* obj, int* retSize) {
  *retSize = obj->size;
  int swapIndex;
  // 用srand(time(NULL))的话不能得到全排列的“均匀”随机数，所以不用
  // srand(time(NULL));
  for (int i = 0; i < *retSize; i++) {
    swapIndex = randomInt(i, *retSize - 1);
    swap(&(obj->array[i]), &(obj->array[swapIndex]));
  }
  return obj->array;
}
void solutionFree(Solution* obj) {
  free(obj->array);
  free(obj->origin);
  free(obj);
  return;
}