/*
给你两个非空链表来代表两个非负整数。
数字最高位位于链表开始位置。
它们的每个节点只存储一位数字。
将这两数相加会返回一个新的链表。
你可以假设除了数字0之外，这两个数字都不会以零开头。

示例1：
输入：l1 = [7,2,4,3], l2 = [5,6,4]
输出：[7,8,0,7]

示例2：
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[8,0,7]

示例3：
输入：l1 = [0], l2 = [0]
输出：[0]

提示：
链表的长度范围为[1, 100]
0 <= node.val <= 9
输入数据保证链表代表的数字无前导0

进阶：如果输入链表不能翻转该如何解决？
*/

struct ListNode {
  int val;
  struct ListNode* next;
};
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  int stack1[100];
  int stack2[100];
  int top1 = 0;
  int top2 = 0;

  while (l1) {
    stack1[top1++] = l1->val;
    l1 = l1->next;
  }
  while (l2) {
    stack2[top2++] = l2->val;
    l2 = l2->next;
  }
  int flag = 0;
  struct ListNode* head = NULL;
  while (top1 > 0 || top2 > 0 || flag) {
    int sum = flag;
    if (top1 > 0) {
      sum += stack1[--top1];
    }
    if (top2 > 0) {
      sum += stack2[--top2];
    }
    flag = sum / 10;
    struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
    tmp->val = sum % 10;
    tmp->next = head;
    head = tmp;
  }

  return head;
}