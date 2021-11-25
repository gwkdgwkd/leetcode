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