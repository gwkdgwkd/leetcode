/*
0,1,···,n-1这n个数字排成一个圆圈，从数字0开始，
每次从这个圆圈里删除第m个数字（删除后从下一个数字开始计数）。
求出这个圆圈里剩下的最后一个数字。
例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，
则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

示例1：
输入: n = 5, m = 3
输出: 3

示例2：
输入: n = 10, m = 17
输出: 2

限制：
1 <= n <= 10^5
1 <= m <= 10^6
*/

// 这个问题实际上是约瑟夫问题，从最终活着的人编号的反推
int lastRemaining(int n, int m) {
  int ret = 0;  // 最终活下来那个人的初始位置，只有一个人，下标为0
  for (int i = 2; i <= n; ++i) {  // 每次计算i，m的值
    ret = (ret + m) % i;          // 每次循环右移
  }

  // n = 5, m = 3
  // 第一轮：[0 1 (2) 3 4][0 1 2 3 4]，从0开始，删除2
  // 第二轮：[3 4 (0) 1][3 4 0 1]，从3开始，删除0
  // 第三轮：[1 3 (4)][1 3 4]，从1开始，删除4
  // 第四轮：[1 3][(1) 3]，从1开始，删除1
  // 第五轮：[3]，只有1个元素，从3开始，删除3

  // 反着来：
  // 最后剩下的3的下标是0
  // 第四轮反推，补上m个位置，然后模上当时的数组大小2，位置是(0 + 3) % 2 = 1
  // 第三轮反推，补上m个位置，然后模上当时的数组大小3，位置是(1 + 3) % 3 = 1
  // 第二轮反推，补上m个位置，然后模上当时的数组大小4，位置是(1 + 3) % 4 = 0
  // 第一轮反推，补上m个位置，然后模上当时的数组大小5，位置是(0 + 3) % 5 = 3
  // 所以最终剩下的数字的下标就是3。
  // 因为数组是从0开始的，所以最终的答案就是3。
  // 总结一下反推的过程，就是(当前index + m) % 上一轮剩余数字的个数。

  return ret;
}

// 环形链表，超时
typedef struct node {
  int number;
  struct node* next;
} person;
person* initLink(int n) {
  person* head = (person*)malloc(sizeof(person));
  head->number = 0;
  head->next = NULL;
  person* cyclic = head;
  for (int i = 1; i < n; i++) {
    person* body = (person*)malloc(sizeof(person));
    body->number = i;
    body->next = NULL;
    cyclic->next = body;
    cyclic = cyclic->next;
  }
  cyclic->next = head;  // 首尾相连
  return head;
}
int findAndKillK(person* head, int k, int m) {
  person* tail = head;
  // 找到链表第一个结点的上一个结点，为删除操作做准备
  while (tail->next != head) {
    tail = tail->next;
  }
  person* p = head;
  // 找到编号为k的人
  while (p->number != k) {
    tail = p;
    p = p->next;
  }
  // 从编号为k的人开始，只有符合p->next==p时，说明链表中除了p结点，所有编号都出列了，
  while (p->next != p) {
    // 找到从p报数1开始，报m的人，并且还要知道数m-1的人的位置tail，方便做删除操作。
    for (int i = 0; i < m - 1; i++) {
      tail = p;
      p = p->next;
    }
    tail->next = p->next;  // 从链表上将p结点摘下来
    // printf("出列人的编号为:%d,\n", p->number);
    free(p);
    p = tail->next;  // 继续使用p指针指向出列编号的下一个编号，游戏继续
  }
  //   printf("出列人的编号为:%d\n", p->number);
  int ret = p->number;
  free(p);

  return ret;
}
int lastRemaining(int n, int m) {
  person* c = initLink(n);

  return findAndKillK(c, 0, m);
}