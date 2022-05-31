/*
给你一个整数数组nums和一个整数k，请你返回其中出现频率前k高的元素。你可以按任意顺序返回答案。

示例1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例2:
输入: nums = [1], k = 1
输出: [1]

提示：
1 <= nums.length <= 10^5
k的取值范围是[1, 数组中不相同的元素的个数]
题目数据保证答案唯一，换句话说，数组中前k个高频元素的集合是唯一的

进阶：你所设计算法的时间复杂度 必须优于O(nlogn) ，其中n是数组大小。
*/

// 剑指OfferII060出现频率最高的k个数字

// 哈希表+快速排序
// 1.直接第一次循环遍历数组，然后将没有数值都保存到hash表中，保存每一个数组出现的频率
// 2.对hash表进行一次快排，按照从大到小的顺序排序
// 3.取前k个值，就是想要的结果
typedef struct {
  int key;
  int freq;
  UT_hash_handle hh;
} MyHash;
MyHash *g_head = NULL;
MyHash *GetNumFreq(int num) {
  MyHash *tmp = NULL;
  HASH_FIND_INT(g_head, &num, tmp);
  return tmp;
}
void AddNumFreq(int num) {
  MyHash *tmp = NULL;
  tmp = GetNumFreq(num);
  if (tmp == NULL) {
    tmp = (MyHash *)malloc(sizeof(MyHash));
    tmp->key = num;
    tmp->freq = 1;
    HASH_ADD_INT(g_head, key, tmp);
  } else {
    (tmp->freq)++;
  }
}
// 降序排列
int TopkCmp(MyHash *a, MyHash *b) { return a->freq < b->freq ? 1 : -1; }
int *topKFrequent(int *nums, int numsSize, int k, int *returnSize) {
  g_head = NULL;

  for (int i = 0; i < numsSize; i++) {
    AddNumFreq(nums[i]);
  }
  int *result = (int *)malloc(sizeof(int) * k);
  int cnt = 0;
  HASH_SORT(g_head, TopkCmp);
  MyHash *curr = NULL;
  MyHash *next = NULL;
  HASH_ITER(hh, g_head, curr, next) {
    result[cnt++] = curr->key;
    if (cnt == k) break;
  }

  *returnSize = k;
  return result;
}

// 基于最小堆（k个数）算法
#define MAX_ARR_SIZE 100001
typedef struct {
  int key;
  int freq;
  UT_hash_handle hh;
} MyHash;
MyHash *g_head = NULL;
MyHash *GetNumFreq(int num) {
  MyHash *tmp = NULL;
  HASH_FIND_INT(g_head, &num, tmp);
  return tmp;
}
void AddNumFreq(int num) {
  MyHash *tmp = NULL;
  tmp = GetNumFreq(num);
  if (tmp == NULL) {
    tmp = (MyHash *)malloc(sizeof(MyHash));
    tmp->key = num;
    tmp->freq = 1;
    HASH_ADD_INT(g_head, key, tmp);
  } else {
    (tmp->freq)++;
  }
}
typedef int(MyCmp)(const void *a, const void *b);
// 小顶堆
int HeapCmp(const void *a, const void *b) {
  int left = *(int *)a;
  int right = *(int *)b;
  return GetNumFreq(left)->freq < GetNumFreq(right)->freq ? -1 : 1;
}
void Swap(int *arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}
void AdjustHeap(int *arr, int i, int arrSize, MyCmp cmp) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int min = i;
  if (left < arrSize && cmp(&arr[i], &arr[left]) > 0) {
    min = left;
  }
  if (right < arrSize && cmp(&arr[min], &arr[right]) > 0) {
    min = right;
  }
  if (i != min) {
    Swap(arr, i, min);
    AdjustHeap(arr, min, arrSize, cmp);
  }
}
void SiftUp(int *arr, int i, MyCmp cmp) {
  if (i == 0) return;
  int parent = (i + 1) / 2 - 1;
  if (i != parent) {
    if (cmp(&arr[parent], &arr[i]) > 0) {  //  if (arr[parent] > arr[i]) {
      Swap(arr, i, parent);
      SiftUp(arr, parent, cmp);
    }
  }
}
int *topKFrequent(int *nums, int numsSize, int k, int *returnSize) {
  g_head = NULL;

  for (int i = 0; i < numsSize; i++) {
    AddNumFreq(nums[i]);
  }
  int *result = (int *)malloc(sizeof(int) * k);
  int heapcnt = 0;
  int heap[MAX_ARR_SIZE] = {0};
  MyHash *curr = NULL;
  MyHash *next = NULL;
  HASH_ITER(hh, g_head, curr, next) {
    if (heapcnt < k) {
      // 将数直接放到堆里
      heap[heapcnt++] = curr->key;
      SiftUp(heap, heapcnt - 1, HeapCmp);
    } else {
      // 需要比较堆顶元素和要放进去的元素的频率大小
      if (GetNumFreq(heap[0])->freq < curr->freq) {
        heap[0] = curr->key;
        AdjustHeap(heap, 0, k, HeapCmp);
      }
    }
  }

  for (int i = 0; i < k; i++) {
    result[i] = heap[i];
  }

  *returnSize = k;
  return result;
}