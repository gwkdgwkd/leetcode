/*
动物收容所。有家动物收容所只收容狗与猫，且严格遵守“先进先出”的原则。
在收养该收容所的动物时，收养人只能收养所有动物中“最老”（由其进入收容所的时间长短而定）的动物，
或者可以挑选猫或狗（同时必须收养此类动物中“最老”的）。
换言之，收养人不能自由挑选想收养的对象。
请创建适用于这个系统的数据结构，实现各种操作方法，比如enqueue、dequeueAny、dequeueDog和dequeueCat。
允许使用Java内置的LinkedList数据结构。
enqueue方法有一个animal参数，animal[0]代表动物编号，animal[1]代表动物种类，其中0代表猫，1代表狗。
dequeue*方法返回一个列表[动物编号, 动物种类]，若没有可以收养的动物，则返回[-1,-1]。

示例1:
输入：
["AnimalShelf", "enqueue", "enqueue", "dequeueCat", "dequeueDog", "dequeueAny"]
[[], [[0, 0]], [[1, 0]], [], [], []]
输出：
[null,null,null,[0,0],[-1,-1],[1,0]]

示例2:
输入：
["AnimalShelf", "enqueue", "enqueue", "enqueue", "dequeueDog", "dequeueCat", "dequeueAny"]
[[], [[0, 0]], [[1, 0]], [[2, 1]], [], [], []]
输出：
[null,null,null,null,[2,1],[0,0],[1,0]]

说明:收纳所的最大容量为20000
*/

typedef struct {
  int order;
  int kinds
} AnimalShelf;
AnimalShelf g_queue[20000];
int g_right;
int g_left;
AnimalShelf* animalShelfCreate() {
  AnimalShelf* aniShelf = malloc(sizeof(AnimalShelf));
  g_right = 0;
  g_left = 0;
  for (int i = 0; i < 20000; i++) {
    g_queue[i].order = -1;
    g_queue[i].kinds = -1;
  }
  return aniShelf;
}
void animalShelfEnqueue(AnimalShelf* obj, int* animal, int animalSize) {
  obj->order = animal[0];
  obj->kinds = animal[1];
  g_queue[g_right++] = *obj;
  return;
}
int* animalShelfDequeueAny(AnimalShelf* obj, int* retSize) {
  *retSize = 2;
  int* ret = (int*)malloc(sizeof(int) * (*retSize));
  ret[0] = -1;
  ret[1] = -1;
  if (g_right - g_left == 0) {  //动物收容所没有动物时，g_left不能执行自加
    return ret;
  }
  ret[0] = g_queue[g_left].order;
  ret[1] = g_queue[g_left].kinds;
  g_left++;

  return ret;
}
int* animalShelfDequeueDog(AnimalShelf* obj, int* retSize) {
  *retSize = 2;
  int* ret = (int*)malloc(sizeof(int) * (*retSize));
  ret[0] = -1;
  ret[1] = -1;
  for (int i = g_left; i < g_right; i++) {
    if (g_queue[i].kinds == 1) {
      ret[0] = g_queue[i].order;
      ret[1] = g_queue[i].kinds;
      for (int j = i; j < g_right; j++) {
        g_queue[j] = g_queue[j + 1];
      }
      g_right--;
      return ret;
    }
  }
  return ret;
}
int* animalShelfDequeueCat(AnimalShelf* obj, int* retSize) {
  *retSize = 2;
  int* ret = (int*)malloc(sizeof(int) * (*retSize));
  ret[0] = -1;
  ret[1] = -1;
  for (int i = g_left; i < g_right; i++) {
    if (g_queue[i].kinds == 0) {
      ret[0] = g_queue[i].order;
      ret[1] = g_queue[i].kinds;
      for (int j = i; j < g_right; j++) {
        g_queue[j] = g_queue[j + 1];
      }
      g_right--;
      return ret;
    }
  }
  return ret;
}
void animalShelfFree(AnimalShelf* obj) {
  free(obj);
  obj = NULL;
  return;
}