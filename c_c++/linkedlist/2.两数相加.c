/*
给你两个非空的链表，表示两个非负的整数。
它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字0之外，这两个数都不会以0开头。

示例1：
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.

示例2：
输入：l1 = [0], l2 = [0]
输出：[0]

示例3：
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]

提示：
每个链表中的节点数在范围[1, 100]内
0 <= Node.val <= 9
题目数据保证列表表示的数字不含前导零
*/

// 面试题0205链表求和

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  if (l1 == NULL) return l2;
  if (l2 == NULL) return l1;

  struct ListNode* h1 = l1;
  struct ListNode* h2 = l2;

  int t = 0;          // 是否有进位的1
  while (h1 && h2) {  // 两个链表都有数字时
    int temp = h1->val + h2->val + t;
    h1->val = temp % 10;
    t = temp / 10;

    // h1和h2都用完了，但是有进位
    if (h1->next == NULL && h2->next == NULL && t) {
      struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
      node->val = 1;
      node->next = NULL;
      h1->next = node;
      return l1;
    }

    if (h1->next == NULL && h2->next != NULL) {  // h1用完了，把h2接到h1上
      h1->next = h2->next;
      h2->next = NULL;
    }

    h1 = h1->next;
    h2 = h2->next;
  }

  while (h1) {  // 对h1单独处理
    int temp = h1->val + t;
    h1->val = temp % 10;
    t = temp / 10;
    if (h1->next == NULL && t) {  // h1处理完了，但是有进位
      struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
      node->val = 1;
      node->next = NULL;
      h1->next = node;
      t = 0;
      break;
    } else {
      h1 = h1->next;
    }
  }

  return l1;
}

// 官方题解
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode *head = NULL, *tail = NULL;
  int carry = 0;
  while (l1 || l2) {
    int n1 = l1 ? l1->val : 0;
    int n2 = l2 ? l2->val : 0;
    int sum = n1 + n2 + carry;
    if (!head) {
      head = tail = malloc(sizeof(struct ListNode));
      tail->val = sum % 10;
      tail->next = NULL;
    } else {
      tail->next = malloc(sizeof(struct ListNode));
      tail->next->val = sum % 10;
      tail = tail->next;
      tail->next = NULL;
    }
    carry = sum / 10;
    if (l1) {
      l1 = l1->next;
    }
    if (l2) {
      l2 = l2->next;
    }
  }
  if (carry > 0) {
    tail->next = malloc(sizeof(struct ListNode));
    tail->next->val = carry;
    tail->next->next = NULL;
  }
  return head;
}