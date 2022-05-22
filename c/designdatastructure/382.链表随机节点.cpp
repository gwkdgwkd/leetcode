/*
给你一个单链表，随机选择链表的一个节点，并返回相应的节点值。每个节点被选中的概率一样。
实现Solution类：Solution(ListNode head)使用整数数组初始化对象。
int getRandom()从链表中随机选择一个节点并返回该节点的值。
链表中所有节点被选中的概率相等。

示例：
输入
["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
输出
[null, 1, 3, 2, 2, 3]

解释
Solution solution = new Solution([1, 2, 3]);
solution.getRandom(); // 返回1
solution.getRandom(); // 返回3
solution.getRandom(); // 返回2
solution.getRandom(); // 返回2
solution.getRandom(); // 返回3
getRandom()方法应随机返回1、2、3中的一个，每个元素被返回的概率相等。

提示：
链表中的节点数在范围[1, 10^4]内
-10^4 <= Node.val <= 10^4
至多调用getRandom方法10^4次

进阶：
如果链表非常大且长度未知，该怎么处理？
你能否在不使用额外空间的情况下解决此问题？
*/

typedef struct SNode {
  struct ListNode* head;
  int length;
} Solution;
Solution* solutionCreate(struct ListNode* head) {
  Solution* slt = malloc(sizeof(struct SNode));
  slt->head = head;
  slt->length = 0;
  while (head) {
    (slt->length)++;
    head = head->next;
  }
  return slt;
}
int solutionGetRandom(Solution* obj) {
  if (!obj->head) return -1;

  int len = obj->length;
  int randomNum = rand() % len;  // 产生0～len-1的随机数
  struct ListNode* ptr = obj->head;
  for (int i = 0; i < randomNum && ptr; i++) {
    ptr = ptr->next;
  }
  return ptr->val;
}
void solutionFree(Solution* obj) {
  obj->length = 0;
  obj->head = NULL;
}

class Solution {
  vector<int> arr;

 public:
  Solution(ListNode* head) {
    while (head) {
      arr.emplace_back(head->val);
      head = head->next;
    }
  }

  int getRandom() { return arr[rand() % arr.size()]; }
};
