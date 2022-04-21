/*
用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail和deleteHead，
分别完成在队列尾部插入整数和在队列头部删除整数的功能。
若队列中没有元素，deleteHead操作返回-1

示例1：
输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]

示例2：
输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]

提示：
1 <= values <= 10000
最多会对appendTail、deleteHead进行10000次调用
*/

typedef struct {
  int* stack1;
  int top1;
  int* stack2;
  int top2;
} CQueue;
CQueue* cQueueCreate() {
  CQueue* q = (CQueue*)malloc(sizeof(CQueue));
  q->stack1 = (int*)malloc(sizeof(int) * 10000);
  q->stack2 = (int*)malloc(sizeof(int) * 10000);
  q->top1 = 0;
  q->top2 = 0;
  return q;
}
void cQueueAppendTail(CQueue* obj, int value) {
  obj->stack1[obj->top1++] = value;
}
int cQueueDeleteHead(CQueue* obj) {
  if (obj->top2 == 0) {
    while (obj->top1 > 0) {
      obj->stack2[obj->top2++] = obj->stack1[obj->top1 - 1];
      --obj->top1;
    }
  }
  if (obj->top2 > 0) {
    --obj->top2;
    return obj->stack2[obj->top2];
  }
  return -1;
}
void cQueueFree(CQueue* obj) {
  free(obj->stack1);
  free(obj->stack2);
  free(obj);
}