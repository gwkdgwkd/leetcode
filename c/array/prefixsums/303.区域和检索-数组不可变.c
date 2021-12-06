// 前缀和主要适用的场景是原始数组不会被修改的情况下，频繁查询某个区间的累加和。
typedef struct {
  int* pre;
} NumArray;
NumArray* numArrayCreate(int* nums, int numsSize) {
  NumArray* na = (NumArray*)malloc(sizeof(NumArray));
  na->pre = (int*)calloc(numsSize + 1, sizeof(int));

  // for(int i = 1; i < numsSize + 1; ++i) {
  //     na->pre[i] = na->pre[i - 1] + nums[i - 1];
  // }
  for (int i = 0; i < numsSize; i++) {
    na->pre[i + 1] = na->pre[i] + nums[i];
  }

  return na;
}
int numArraySumRange(NumArray* obj, int left, int right) {
  return obj->pre[right + 1] - obj->pre[left];  // 查询闭区间[left,right]累加和
}
void numArrayFree(NumArray* obj) {
  free(obj->pre);
  free(obj);
}