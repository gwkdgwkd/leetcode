/*
设计一个找到数据流中第k大元素的类（class）。
注意是排序后的第k大元素，不是第k个不同的元素。
请实现KthLargest类：
KthLargest(int k, int[] nums) 使用整数k和整数流nums初始化对象。
int add(int val) 将val插入数据流nums后，返回当前数据流中第k大的元素。

示例：
输入：
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
输出：
[null, 4, 5, 5, 8, 8]
解释：
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8


提示：
1 <= k <= 10^4
0 <= nums.length <= 10^4
-104 <= nums[i] <= 10^4
-104 <= val <= 10^4
最多调用add方法10^4次
题目数据保证，在查找第k大元素时，数组中至少有k个元素
*/

// 剑指OfferII059数据流的第K大数值

// 优先级队列
typedef struct {
  int *heap;     // 小顶堆
  int size;      // 当前大小
  int capacity;  // 可用容量
} KthLargest;
int getLeft(int i) { return 2 * i + 1; }
int getRight(int i) { return 2 * i + 2; }
int getParent(int i) { return (i - 1) / 2; }
void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
// 插入当堆没有满时，插入到最后，然后上浮函数
void shifUp(int *array, int index) {
  while (index > 0 && array[getParent(index)] > array[index]) {
    swap(&array[getParent(index)], &array[index]);
    index = getParent(index);
  }
}
// 插入当堆已经满了时，替换头节点，然后下浮函数
void shifDown(int *array, int size, int index) {
  int smallest = index;
  int left = getLeft(index);
  int right = getRight(index);

  // 下浮时，将当前节点与其左右子节点中的较大值进行交换
  if (left < size && array[left] < array[smallest]) {
    smallest = left;
  }
  if (right < size && array[right] < array[smallest]) {
    smallest = right;
  }
  if (index != smallest) {
    swap(&array[index], &array[smallest]);
    shifDown(array, size, smallest);
  }
}
// 往堆中增加元素，并按照顺序排序
void heapAdd(KthLargest *obj, int val) {
  if (obj->size < obj->capacity) {
    // 堆未满, 插入到最后然后上浮
    obj->heap[obj->size++] = val;
    shifUp(obj->heap, obj->size - 1);
  } else if (obj->heap[0] < val) {
    // 堆已满，判断最小堆头节点是不是比val小，如果不是不处理，如果是需要替换头，然后下浮
    obj->heap[0] = val;
    shifDown(obj->heap, obj->size, 0);
  }
}
KthLargest *kthLargestCreate(int k, int *nums, int numsSize) {
  KthLargest *obj = (KthLargest *)malloc(sizeof(KthLargest));
  if (obj == NULL) return NULL;
  obj->heap = (int *)malloc(sizeof(int) * k);
  if (obj->heap == NULL) return NULL;

  obj->size = 0;
  obj->capacity = k;

  for (int i = 0; i < numsSize; ++i) {
    heapAdd(obj, nums[i]);
  }

  return obj;
}
int kthLargestAdd(KthLargest *obj, int val) {
  heapAdd(obj, val);
  return obj->heap[0];
}
void kthLargestFree(KthLargest *obj) {
  free(obj->heap);
  free(obj);
}