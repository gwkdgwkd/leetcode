/*
给你单链表的头指针head和两个整数left和right，其中left<=right。
请你反转从位置left到位置right的链表节点，返回反转后的链表。

示例1：
输入：head = [1,2,3,4,5], left = 2, right = 4
输出：[1,4,3,2,5]

示例2：
输入：head = [5], left = 1, right = 1
输出：[5]

提示：
链表中节点数目为n
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n

进阶：你可以使用一趟扫描完成反转吗？
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

// 递归
struct ListNode* successor = NULL;  // 后驱节点
// 反转以head为起点的n个节点，返回新的头结点
struct ListNode* reverseN(struct ListNode* head, int n) {
  if (n == 1) {
    // 记录第n+1个节点
    successor = head->next;
    return head;
  }
  // 以head.next为起点，需要反转前n-1个节点
  struct ListNode* last = reverseN(head->next, n - 1);

  head->next->next = head;
  // 让反转之后的head节点和后面的节点连起来
  head->next = successor;
  return last;
}
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
  // base case
  if (left == 1) {
    return reverseN(head, right);
  }
  // 前进到反转的起点触发base case
  head->next = reverseBetween(head->next, left - 1, right - 1);
  return head;
}

// 迭代
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
  struct ListNode dummy;
  dummy.next = head;
  struct ListNode* preTmp = &dummy;
  for (int i = 1; i < left; ++i) {
    // 找到翻转区间的pre节点：
    preTmp = preTmp->next;
  }

  // 对翻转区间进行翻转：
  struct ListNode* pre = preTmp;
  struct ListNode* cur = pre->next;
  struct ListNode* next = NULL;
  for (int i = left; i <= right; ++i) {
    next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
  }

  // 将翻转区间与前后链表相连
  preTmp->next->next = cur;
  preTmp->next = pre;

  return dummy.next;
}

class Solution {
 public:
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummy(0, head);
    ListNode* pre = &dummy;
    int i = 1;
    while (i++ < left) {
      pre = pre->next;
    }

    ListNode* leftNode = pre;
    ListNode* currNode = pre->next;
    ListNode* rightNode;
    for (i = left; i <= right; ++i) {
      rightNode = currNode->next;
      currNode->next = leftNode;
      leftNode = currNode;
      currNode = rightNode;
    }

    pre->next->next = currNode;
    pre->next = leftNode;
    return dummy.next;
  }
};

// 迭代
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
  // left, right相等或链表只有一个结点可以直接返回结果：
  if (head->next == NULL || left == right) return head;

  // 设置头结点可以将left为1的情况一般化：
  int i;
  struct ListNode *p, *q, *r, h;
  h.next = head;

  // q对应left位置的结点, p指向其前一个结点：
  for (p = &h, i = 0; i < left - 1; i++, p = p->next)
    ;
  q = p->next;

  for (i = left; i < right; i++) {
    r = q->next;
    q->next = r->next;  // 取下结点
    r->next = p->next;
    p->next = r;  // 头插法插入结点
  }

  return h.next;
}