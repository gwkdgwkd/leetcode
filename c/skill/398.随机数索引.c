/*
给定一个可能含有重复元素的整数数组，要求随机输出给定的数字的索引。您可以假设给定的数字一定存在于数组中。

注意：
数组大小可能非常大。使用太多额外空间的解决方案将不会通过测试。

示例:
int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

pick(3)应该返回索引2,3或者4。每个索引的返回概率应该相等。
solution.pick(3);

pick(1)应该返回0。因为只有nums[0]等于1。
solution.pick(1);
*/

typedef struct {
  int* nums;
  int size;
} Solution;
Solution* solutionCreate(int* nums, int numsSize) {
  Solution* obj = (Solution*)malloc(sizeof(Solution));
  obj->nums = nums;
  obj->size = numsSize;
  return obj;
}
int solutionPick(Solution* obj, int target) {
  int count = 0;
  int ret = -1;
  for (int i = 0; i < obj->size; ++i) {
    if (target == obj->nums[i]) {
      if (!(rand() % ++count)) ret = i;
    }
  }
  return ret;
}
void solutionFree(Solution* obj) {
  obj->nums = NULL;
  free(obj);
}