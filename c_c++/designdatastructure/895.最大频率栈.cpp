/*
设计一个类似堆栈的数据结构，将元素推入堆栈，并从堆栈中弹出出现频率最高的元素。
实现FreqStack类：
FreqStack()
构造一个空的堆栈。
void push(int val)
将一个整数val压入栈顶。
int pop()
删除并返回堆栈中出现频率最高的元素。
如果出现频率最高的元素不只一个，则移除并返回最接近栈顶的元素。

示例1：
输入：
["FreqStack","push","push","push","push",
 "push","push","pop","pop","pop","pop"],
[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
输出：[null,null,null,null,null,null,null,5,7,5,4]
解释：
FreqStack = new FreqStack();
freqStack.push(5); // 堆栈为[5]
freqStack.push(7); // 堆栈是[5,7]
freqStack.push(5); // 堆栈是[5,7,5]
freqStack.push(7); // 堆栈是[5,7,5,7]
freqStack.push(4); // 堆栈是[5,7,5,7,4]
freqStack.push(5); // 堆栈是[5,7,5,7,4,5]
freqStack.pop();   // 返回5，因为5出现频率最高。
堆栈变成[5,7,5,7,4]。
freqStack.pop();   // 返回7，因为5和7出现频率最高，但7最接近顶部。
堆栈变成[5,7,5,4]。
freqStack.pop();   // 返回5，因为5出现频率最高。
堆栈变成[5,7,4]。
freqStack.pop();   // 返回4，因为4,5和7出现频率最高，但4是最接近顶部的。
堆栈变成[5,7]。

提示：
0 <= val <= 10^9
push和pop的操作数不大于2 * 10^4。
输入保证在调用pop之前堆栈中至少有一个元素。
*/

// hash表+单调栈+插入排序+链表
typedef struct num {
  int val;   // 数字值
  int freq;  // 出现次数
  struct num *next;
} Num;
typedef struct {
  Num head;  // 链表头，最终的栈顶就在链表头
} FreqStack;
typedef struct myStruct {
  int val;
  int cnt;
  UT_hash_handle hh;
} Node;
Node *map;  // hash表，保存出现次数
Num *tail;  // 链表尾部，其实也可以不用设置，直接用curr的pre来操作也可以
FreqStack *freqStackCreate() {
  map = NULL;
  FreqStack *root = calloc(1, sizeof(FreqStack));
  tail = &root->head;
  return root;
}
void freqStackPush(FreqStack *obj, int x) {
  Node *s = NULL;
  // 查找当前x之前出现几次，如果有就+1，没有就创建，并赋值出现次数为1
  HASH_FIND_INT(map, &x, s);
  if (s == NULL) {
    s = calloc(1, sizeof(Node));
    s->val = x;
    s->cnt++;
    HASH_ADD_INT(map, val, s);
  } else {
    s->cnt++;
  }
  Num *node = calloc(1, sizeof(Num));
  node->val = x;
  node->freq = s->cnt;
  Num *curr = obj->head.next;
  Num *pre = &obj->head;
  // 在链表中做插入排序，排序关键字就是出现次数freq，
  // 找到第1个不大于当前x的，插入此位置
  while (curr != NULL) {
    if (node->freq < curr->freq) {
      pre = curr;
      curr = curr->next;
    } else {
      node->next = curr;
      pre->next = node;
      break;
    }
  }
  if (curr == NULL) {
    tail->next = node;
    tail = tail->next;
  }
}
int freqStackPop(FreqStack *obj) {
  int res;
  // 当前链表头的一定是出现次数最多且之前最后出现的，就是结果
  Num *pop = obj->head.next;
  if (pop != NULL) {
    res = pop->val;
  }
  Node *s = NULL;
  HASH_FIND_INT(map, &res, s);  // 调整hash表中此项的值
  if (s->cnt == 1) {
    HASH_DEL(map, s);
    free(s);
  } else {
    s->cnt--;
  }
  obj->head.next = pop->next;
  free(pop);
  return res;
}
void freqStackFree(FreqStack *obj) {  // 释放整个链表，释放hash表
  Num *del, *pre;
  del = obj->head.next;
  pre = &obj->head;
  while (del != NULL) {
    pre->next = del->next;
    free(del);
    del = pre->next;
  }
  tail = NULL;
  free(obj);
  Node *s, *tmp;
  HASH_ITER(hh, map, s, tmp) {
    HASH_DEL(map, s);
    free(s);
  }
}

// 哈希表+数组
typedef struct {
  int value;
  int freq;
  UT_hash_handle hh;
} FreqStack;
int freqmap[10001][10000] = {0};
int maxfreq = 0;
int mapcolsize[10001] = {0};
FreqStack *freqStackCreate() {
  FreqStack *init = NULL;
  FreqStack *temp = (FreqStack *)malloc(sizeof(FreqStack));
  temp->value = -1;
  temp->freq = 0;
  HASH_ADD_INT(init, value, temp);
  return init;
}
void freqStackPush(FreqStack *obj, int val) {
  FreqStack *temp;
  HASH_FIND_INT(obj, &val, temp);
  if (temp == NULL) {
    temp = (FreqStack *)malloc(sizeof(FreqStack));
    temp->value = val;
    temp->freq = 1;
    HASH_ADD_INT(obj, value, temp);
  } else
    temp->freq++;
  if (temp->freq > maxfreq) maxfreq = temp->freq;
  freqmap[temp->freq][mapcolsize[temp->freq]] = val;
  mapcolsize[temp->freq]++;
  return;
}
int freqStackPop(FreqStack *obj) {
  int ans = freqmap[maxfreq][mapcolsize[maxfreq] - 1];
  mapcolsize[maxfreq]--;
  while (mapcolsize[maxfreq] == 0) {
    maxfreq--;
  }
  FreqStack *temp;
  HASH_FIND_INT(obj, &ans, temp);
  temp->freq--;
  return ans;
}
void freqStackFree(FreqStack *obj) { HASH_CLEAR(hh, obj); }

class FreqStack {
 public:
  // frequency, timestamp, value
  // 如果frequency相同，则timestamp大的优先级高
  priority_queue<tuple<int, int, int>> pq;
  // <val,freq>
  unordered_map<int, int> val2freq;
  int ts;
  FreqStack() : ts(0) {}
  void push(int val) {
    int freq = ++val2freq[val];
    pq.emplace(freq, ts++, val);
  }
  int pop() {
    int val = get<2>(pq.top());
    pq.pop();
    --val2freq[val];
    return val;
  }
};