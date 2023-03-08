/*
请定义一个队列并实现函数max_value得到队列里的最大值，
要求函数max_value、push_back和pop_front的均摊时间复杂度都是O(1)。
若队列为空，pop_front和max_value需要返回-1。

示例1：
输入：["MaxQueue","push_back","push_back",
      "max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出： [null,null,null,2,1,2]

示例2：
输入：
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出： [null,-1,-1]

限制：
1 <= push_back,pop_front,max_value的总操作数 <= 10000
1 <= value <= 10^5
*/

#define MAXSIZE 10000
typedef struct {
  int queue[MAXSIZE];
  int front1;
  int tail1;
  int max[MAXSIZE];  // 单调递减的队列
  int front2;
  int tail2;
} MaxQueue;
MaxQueue* maxQueueCreate() { return (MaxQueue*)calloc(1, sizeof(MaxQueue)); }
int maxQueueMax_value(MaxQueue* obj) {
  return obj->tail2 != obj->front2 ? obj->max[obj->front2] : -1;
}
void maxQueuePush_back(MaxQueue* obj, int value) {
  obj->queue[obj->tail1++] = value;

  while (obj->tail2 != obj->front2 && obj->max[obj->tail2 - 1] < value) {
    --obj->tail2;
  }
  obj->max[obj->tail2++] = value;
}
int maxQueuePop_front(MaxQueue* obj) {
  if (obj->front1 == obj->tail1) {
    return -1;
  }

  int res = obj->queue[obj->front1++];
  if (res == obj->max[obj->front2]) {
    ++obj->front2;
  }

  return res;
}
void maxQueueFree(MaxQueue* obj) { free(obj); }

class MaxQueue {
  queue<int> que;
  deque<int> max;

 public:
  MaxQueue() {}
  int max_value() { return max.empty() ? -1 : max.front(); }
  void push_back(int value) {
    while (!max.empty() && max.back() < value) {
      max.pop_back();
    }
    max.push_back(value);
    que.push(value);
  }
  int pop_front() {
    if (que.empty()) {
      return -1;
    }
    int ans = que.front();
    que.pop();

    if (ans == max.front()) {
      max.pop_front();
    }

    return ans;
  }
};
