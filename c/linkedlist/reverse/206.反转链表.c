/*
给你单链表的头节点head，请你反转链表，并返回反转后的链表。

示例1：
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]

示例2：
输入：head = [1,2]
输出：[2,1]

示例3：
输入：head = []
输出：[]

提示：
链表中节点的数目范围是[0, 5000]
-5000 <= Node.val <= 5000

进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
*/

// 剑指Offer24反转链表
// 剑指OfferII024反转链表

struct ListNode {
  int val;
  struct ListNode* next;
};

// 迭代
// 该算法的实现思想非常直接，就是从当前链表的首元节点开始，一直遍历至链表的最后一个节点，
// 这期间会逐个改变所遍历到的节点的指针域，另其指向前一个节点
struct ListNode* reverseList(struct ListNode* head) {
  struct ListNode* left = NULL;
  struct ListNode* mid = head;
  struct ListNode* right;  // 保存mid的下一个节点

  while (mid) {
    right = mid->next;  // 保存mid的下一个节点，因为接下来要改变mid->next
    mid->next = left;  // 翻转操作
    left = mid;        // 更新left
    mid = right;       // 更新right
  }

  return left;
}

// 头插法反转链表
// 所谓头插法，是指在原有链表的基础上，依次将位于链表头部的节点摘下，
// 然后采用从头部插入的方式生成一个新链表，则此链表即为原链表的反转版。
struct ListNode* reverseList(struct ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  struct ListNode* new_head = NULL;
  struct ListNode* temp = NULL;
  while (head) {
    temp = head;
    head = head->next;      // 将temp从head中摘除
    temp->next = new_head;  // 将temp插入到new_head的头部
    new_head = temp;
  }
  return new_head;
}

// 就地逆置法反转链表
// 就地逆置法和头插法的实现思想类似，唯一的区别在于，头插法是通过建立一个新链表实现的，
// 而就地逆置法则是直接对原链表做修改，从而实现将原链表反转。
struct ListNode* reverseList(struct ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }
  struct ListNode* beg = head;
  struct ListNode* end = head->next;
  while (end) {
    beg->next = end->next;  // 将end从链表中摘除
    end->next = head;       // 将end移动至链表头
    head = end;
    // 调整end的指向，另其指向beg后的一个节点，为反转下一个节点做准备
    end = beg->next;
  }
  return head;
}

// 递归
struct ListNode* reverse(struct ListNode* pre, struct ListNode* cur) {
  if (cur == NULL) return pre;
  struct ListNode* temp = cur->next;
  cur->next = pre;
  return reverse(cur, temp);
}
struct ListNode* reverseList(struct ListNode* head) {
  return reverse(NULL, head);
}

// 递归
struct ListNode* reverseList(struct ListNode* head) {
  if (head == NULL || head->next == NULL) return head;
  struct ListNode* last = reverseList(head->next);
  head->next->next = head;
  head->next = NULL;
  return last;
}
