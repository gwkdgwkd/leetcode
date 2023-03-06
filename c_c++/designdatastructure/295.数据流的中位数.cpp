/*
中位数是有序列表中间的数，如果列表长度是偶数，中位数则是中间两个数的平均值。
例如，
[2,3,4]的中位数是3
[2,3]的中位数是(2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：
void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。

示例：
addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

进阶:
如果数据流中所有整数都在0到100范围内，你将如何优化你的算法？
如果数据流中99%的整数都在0到100范围内，你将如何优化你的算法？
*/

// 剑指Offer41数据流中的中位数
// 面试题1720连续中值

// 两个堆
#define MAX 100000
typedef struct {
  int num;
  int* p;
} MedianFinder;
MedianFinder* strObj;
int bigHeap[MAX] = {0};
int smallHeap[MAX] = {0};
int bigSize;
int smallSize;
MedianFinder* medianFinderCreate() {
  strObj = malloc(sizeof(MedianFinder));
  strObj->num = 0;
  strObj->p = bigHeap;
  bigSize = 0;
  smallSize = 0;

  return strObj;
}
// flag：1 大根堆, -1 小根堆
void UpdataHeap(int* heap, int size, int flag) {
  int fatherIdx = size - 1;
  int childIdx;
  int originVal = heap[fatherIdx];

  while (fatherIdx >= 0) {
    childIdx = ((fatherIdx + 1) >> 1) - 1;
    // 需要判断是否存在子节点
    if (childIdx < 0 || originVal * flag < heap[childIdx] * flag) {
      break;
    }
    heap[fatherIdx] = heap[childIdx];
    fatherIdx = childIdx;
  }
  heap[fatherIdx] = originVal;

  return;
}
void BigHeap(int num) {
  bigHeap[bigSize++] = num;

  UpdataHeap(bigHeap, bigSize, 1);

  return;
}
void SmallHeap(int num) {
  smallHeap[smallSize++] = num;

  UpdataHeap(smallHeap, smallSize, -1);

  return;
}
// flag：1 大根堆, -1 小根堆
void AdjastHead(int index, int heapSize, int* heap, int flag) {
  int childIdx;
  int middle;
  int max;
  // 保存节点原始值，这里不要用index，heap中的内容后续会改变
  int originVal = heap[index];

  middle = heapSize >> 1;

  while (index < middle) {
    childIdx = 2 * index + 1;  // 左子节点
    max = heap[childIdx];
    // 需要判断是否存在右子节点
    if ((childIdx + 1 < heapSize) && (flag * max < flag * heap[childIdx + 1])) {
      childIdx = childIdx + 1;
      max = heap[childIdx];  // 选择左、右子节点大（小）值
    }

    if (flag * originVal > flag * max) {  // 满足大（小）根堆条件
      break;
    }

    heap[index] = heap[childIdx];
    index = childIdx;
  }
  heap[index] = originVal;

  return;
}
void DeleteBigHeapHead() {
  bigHeap[0] = bigHeap[--bigSize];  // 移除head后，将末元素移到head
  AdjastHead(0, bigSize, bigHeap, 1);

  return;
}
void DeleteSmallHeapHead() {
  smallHeap[0] = smallHeap[--smallSize];  // 移除head后，将末元素移到head
  AdjastHead(0, smallSize, smallHeap, -1);

  return;
}
void medianFinderAddNum(MedianFinder* obj, int num) {
  int i;

  // 1.每次增加元素如果大于小根堆最小元素，则加入小根堆；
  // 2.如果小根堆个数比大根堆个数多余1个，则将小根堆顶点移到大根堆
  if (smallSize == 0 || num > smallHeap[0]) {
    SmallHeap(num);
    if (smallSize > bigSize + 1) {
      BigHeap(smallHeap[0]);
      DeleteSmallHeapHead();
    }
  } else {
    BigHeap(num);
    if (bigSize > smallSize + 1) {
      SmallHeap(bigHeap[0]);
      DeleteBigHeapHead();
    }
  }

  obj->num = bigSize + smallSize;

  return;
}
double medianFinderFindMedian(MedianFinder* obj) {
  double temp;

  if (bigSize > smallSize) {
    temp = bigHeap[0];
  } else if (smallSize > bigSize) {
    temp = smallHeap[0];
  } else {
    temp = ((double)(bigHeap[0] + smallHeap[0])) / 2;
  }

  return temp;
}
void medianFinderFree(MedianFinder* obj) {
  free(strObj);
  memset(bigHeap, 0, MAX * sizeof(int));
}

// 双堆解法
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

class MedianFinder {
  priority_queue<int> bigTop;  // 默认，大顶堆
  // priority_queue<int,vector<int>,less<int>> bigTop; // 也可以
  priority_queue<int, vector<int>, greater<int>> smallTop;  // 小顶堆

 public:
  MedianFinder() {}
  void addNum(int num) {
    if (bigTop.empty() || num <= bigTop.top()) {
      bigTop.push(num);
      if (bigTop.size() - smallTop.size() > 1) {
        smallTop.push(bigTop.top());
        bigTop.pop();
      }
    } else {
      smallTop.push(num);
      if (smallTop.size() > bigTop.size()) {
        bigTop.push(smallTop.top());
        smallTop.pop();
      }
    }
  }
  double findMedian() {
    if (bigTop.size() > smallTop.size()) {
      return bigTop.top();
    }
    return (bigTop.top() + smallTop.top()) / 2.0;
  }
};
