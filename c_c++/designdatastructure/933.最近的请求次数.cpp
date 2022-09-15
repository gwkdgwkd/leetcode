/*
写一个RecentCounter类来计算特定时间范围内最近的请求。
请你实现RecentCounter类：
RecentCounter()
初始化计数器，请求数为0。
int ping(int t)
在时间t添加一个新请求，其中t表示以毫秒为单位的某个时间，
并返回过去3000毫秒内发生的所有请求数（包括新请求）。
确切地说，返回在[t-3000, t]内发生的请求数。
保证每次对ping的调用都使用比之前更大的t值。

示例1：
输入：
["RecentCounter", "ping", "ping", "ping", "ping"]
[[], [1], [100], [3001], [3002]]
输出：
[null, 1, 2, 3, 3]

解释：
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);
requests = [1]，范围是[-2999,1]，返回1
recentCounter.ping(100);
requests = [1, 100]，范围是[-2900,100]，返回2
recentCounter.ping(3001);
requests = [1, 100, 3001]，范围是[1,3001]，返回3
recentCounter.ping(3002);
requests= [1,100,3001,3002]，范围是[2,3002]，返回3

提示：
1 <= t <= 10^9
保证每次对ping调用所使用的t值都严格递增
至多调用ping方法10^4次
*/

// 剑指OfferII042最近请求次数

typedef struct {
  int dat[10001];
  int queueFront;
  int queueRear;
  int maxGap;
  int count;
} RecentCounter;
RecentCounter* recentCounterCreate() {
  RecentCounter* newCounter = (RecentCounter*)malloc(sizeof(RecentCounter));
  newCounter->queueFront = 0;
  newCounter->queueRear = 0;
  newCounter->maxGap = 3000;
  newCounter->count = 0;
  return newCounter;
}
int recentCounterPing(RecentCounter* obj, int t) {
  if (obj->count == 0) {
    obj->dat[obj->queueRear++] = t;
    obj->count++;
  } else {
    obj->dat[obj->queueRear++] = t;
    obj->count++;
    int tail = obj->dat[obj->queueRear - 1];
    while ((tail - obj->dat[obj->queueFront]) > obj->maxGap) {
      obj->queueFront++;
      obj->count--;
    }
  }
  return obj->count;
}
void recentCounterFree(RecentCounter* obj) { free(obj); }

class RecentCounter {
  queue<int> q;

 public:
  RecentCounter() {}
  int ping(int t) {
    q.push(t);
    while (q.front() < t - 3000) {
      q.pop();
    }
    return q.size();
  }
};
