/*
给定一个整数数据流和一个窗口大小，根据该滑动窗口的大小，计算滑动窗口里所有数字的平均值。
实现 MovingAverage 类：
MovingAverage(int size) 用窗口大小size初始化对象。
double next(int val) 成员函数next每次调用的时候都会往滑动窗口增加一个整数，
请计算并返回数据流中最后size个值的移动平均值，即滑动窗口里所有数字的平均值。

示例：
输入：
inputs = ["MovingAverage", "next", "next", "next", "next"]
inputs = [[3], [1], [10], [3], [5]]
输出：
[null, 1.0, 5.5, 4.66667, 6.0]
解释：
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // 返回 1.0 = 1 / 1
movingAverage.next(10); // 返回 5.5 = (1 + 10) / 2
movingAverage.next(3); // 返回 4.66667 = (1 + 10 + 3) / 3
movingAverage.next(5); // 返回 6.0 = (10 + 3 + 5) / 3

提示：
1 <= size <= 1000
-10^5 <= val <= 10^5
最多调用next方法10^4次

注意：本题与346题相同
*/

typedef struct {
  int *nums;
  int head;
  int tail;
  int size;
  int sum;
} MovingAverage;
MovingAverage *movingAverageCreate(int size) {
  MovingAverage *obj = (MovingAverage *)malloc(sizeof(MovingAverage));
  obj->size = size + 1;
  obj->nums = (int *)malloc(obj->size * sizeof(int));
  obj->head = 0;
  obj->tail = 0;
  obj->sum = 0;
  return obj;
}
double movingAverageNext(MovingAverage *obj, int val) {
  if (((obj->tail + 1) % obj->size) == obj->head) {
    obj->sum -= obj->nums[obj->head];
    obj->head = (obj->head + 1) % obj->size;
  }
  obj->nums[obj->tail] = val;
  obj->tail = (obj->tail + 1) % obj->size;
  obj->sum += val;
  int cnt = (obj->tail < obj->head) ? (obj->tail + obj->size - obj->head)
                                    : (obj->tail - obj->head);
  return (double)obj->sum / cnt;
}
void movingAverageFree(MovingAverage *obj) {
  free(obj->nums);
  free(obj);
  return;
}