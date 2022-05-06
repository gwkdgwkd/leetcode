/*
有个马戏团正在设计叠罗汉的表演节目，一个人要站在另一人的肩膀上。
出于实际和美观的考虑，在上面的人要比下面的人矮一点且轻一点。
已知马戏团每个人的身高和体重，请编写代码计算叠罗汉最多能叠几个人。

示例：
输入：height = [65,70,56,75,60,68] weight = [100,150,90,190,95,110]
输出：6
解释：从上往下数，叠罗汉最多能叠6层：
     (56,90), (60,95), (65,100), (68,110), (70,150), (75,190)

提示：height.length == weight.length <= 10000
*/

struct Person {  // 定义一个身高体重的结构体
  int height;
  int weight;
};
struct Person person[10000];  // 结构体Person变量person
int arr[10000];
int temp;
int cmp(const void* a, const void* b) {
  struct Person* m = (struct Person*)a;
  struct Person* n = (struct Person*)b;

  if (m->height != n->height)
    return m->height - n->height;  // 按照身高升序排序
  else {
    return n->weight - m->weight;  // 身高相同，按照体重降序排序
  }
}
int BinarySearch(int aim, int left, int right) {  // 二分搜索
  int mid;
  while (left < right) {
    mid = (left + right) >> 1;  // 执行速度更快，其等同于(left + right)/2;
    if (arr[mid] >= aim)
      right = mid;
    else
      left = mid + 1;
  }
  return left;  // 目标值的位置
}
int bestSeqAtIndex(int* height, int heightSize, int* weight, int weightSize) {
  if (height == NULL || heightSize == 0 || weight == NULL || weightSize == 0) {
    return 0;
  }

  for (int i = 0; i < heightSize; i++) {  // 保存人相应的身高体重
    person[i].height = height[i];
    person[i].weight = weight[i];
  }

  qsort(person, heightSize, sizeof(struct Person), cmp);  // 快速排序

  arr[1] = person[0].weight;  // 初始值为最轻的体重
  int index = 1;              // 层数初始一个人，初始值为1

  // 接下来寻找一个最长递增子序列  arr[index]保存的是末尾元素的值
  for (int i = 1; i < heightSize; i++) {  // 遍历
    if (person[i].weight > arr[index]) {  // 是递增的
      index++;                            // 子序列长度+1
      arr[index] = person[i].weight;      // 末尾数值更新为更大的
    } else {                              // 不递增
      temp =
          BinarySearch(person[i].weight, 1, index);  // 二分查找需要插入的位置
      arr[temp] = person[i].weight;  // 末尾值更新为目标值
    }
  }

  return index;
}