/*
如何得到一个数据流中的中位数？
如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
例如，
[2,3,4]的中位数是3
[2,3]的中位数是(2 + 3) / 2 = 2.5
设计一个支持以下两种操作的数据结构：
void addNum(int num) 从数据流中添加一个整数到数据结构中。
double findMedian() 返回目前所有元素的中位数。

示例1：
输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]

示例2：
输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]

限制：最多会对addNum、findMedian进行50000次调用。

注意：本题与95题相同
*/

#define LEN 50000
typedef struct {
  int maxHeap[LEN];
  int minHeap[LEN];
  int maxLen, minLen;
} MedianFinder;
MedianFinder* medianFinderCreate() {
  MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
  if (mf == NULL) return NULL;
  mf->minLen = 0;
  mf->maxLen = 0;
  return mf;
}
static bool greater(int a, int b) { return a > b; }
static bool less(int a, int b) { return a < b; }
static void swap(int* array, int i, int j) {
  int tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}
static void heapify_todown(int* array, int i, int len, bool (*cmp)(int, int)) {
  while (i <= len) {
    int target = i;
    if (2 * i <= len && cmp(array[2 * i], array[target])) target = 2 * i;
    if (2 * i + 1 <= len && cmp(array[2 * i + 1], array[target]))
      target = 2 * i + 1;
    if (i == target) break;
    swap(array, i, target);
    i = target;
  }
}
static void heapify_toup(int* array, int i, bool (*cmp)(int, int)) {
  while (i > 0) {
    if (i / 2 > 0 && cmp(array[i], array[i / 2])) {
      swap(array, i, i / 2);
      i = i / 2;
    } else {
      break;
    }
  }
}
void medianFinderAddNum(MedianFinder* obj, int num) {
  if (obj->maxLen < 1 || num <= obj->maxHeap[1]) {
    obj->maxHeap[++(obj->maxLen)] = num;
    heapify_toup(obj->maxHeap, obj->maxLen, greater);
  } else {
    obj->minHeap[++(obj->minLen)] = num;
    heapify_toup(obj->minHeap, obj->minLen, less);
  }
  if ((obj->maxLen + obj->minLen) % 2 == 0 && obj->maxLen != obj->minLen) {
    int *fromHeap = obj->maxHeap, *toHeap = obj->minHeap,
        *fromLen = &(obj->maxLen), *toLen = &(obj->minLen);
    if (obj->maxLen < obj->minLen) {
      fromHeap = obj->minHeap;
      toHeap = obj->maxHeap;
      fromLen = &(obj->minLen);
      toLen = &(obj->maxLen);
    }
    while (*fromLen != *toLen) {
      int val = fromHeap[1];
      fromHeap[1] = fromHeap[(*fromLen)--];
      heapify_todown(fromHeap, 1, *fromLen,
                     fromHeap == obj->maxHeap ? greater : less);
      toHeap[++(*toLen)] = val;
      heapify_toup(toHeap, *toLen, toHeap == obj->maxHeap ? greater : less);
    }
  }
}
double medianFinderFindMedian(MedianFinder* obj) {
  if (obj->maxLen + obj->minLen == 0) return 0;
  if ((obj->maxLen + obj->minLen) % 2) {
    return obj->maxLen > obj->minLen ? obj->maxHeap[1] : obj->minHeap[1];
  }
  return (double)(obj->maxHeap[1] + obj->minHeap[1]) / 2;
}
void medianFinderFree(MedianFinder* obj) { free(obj); }