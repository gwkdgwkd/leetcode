/*
给你链表的头节点head，每k个节点一组进行翻转，请你返回修改后的链表。
k是一个正整数，它的值小于或等于链表的长度。
如果节点总数不是k的整数倍，那么请将最后剩余的节点保持原有顺序。
不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

示例1：
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]

示例2：
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]

提示：
链表中的节点数目为n
1 <= k <= n <= 5000
0 <= Node.val <= 1000

进阶：你可以设计一个只用O(1)额外内存空间的算法解决此问题吗？
*/

// 反转区间[a, b)的元素，注意是左闭右开
struct ListNode* reverse(struct ListNode* start, struct ListNode* end) {
  struct ListNode* pre = NULL;
  struct ListNode* cur = start;
  struct ListNode* next;

  while (cur != end) {
    next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
  }

  // 返回反转后的头结点
  return pre;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
  if (!head) return head;

  struct ListNode* next_head = head;
  for (int i = 0; i < k; ++i) {
    // 不足k个，不需要反转，base case
    if (!next_head) return head;
    next_head = next_head->next;
  }

  // 区间[head，next_head)包含k个待反转元素
  struct ListNode* res = reverse(head, next_head);
  // 递归反转后续链表并连接起来
  head->next = reverseKGroup(next_head, k);

  return res;
}

class Solution {
  ListNode* reverse(ListNode* start, ListNode* end) {
    ListNode* left = nullptr;
    ListNode* curr = start;
    ListNode* right;
    while (curr != end) {
      right = curr->next;
      curr->next = left;
      left = curr;
      curr = right;
    }
    return left;
  }

 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* curr = head;
    for (int i = 0; i < k; ++i) {
      if (!curr) {
        return head;
      }
      curr = curr->next;
    }

    ListNode* ans = reverse(head, curr);
    // head此时变成了链表尾了：
    head->next = reverseKGroup(curr, k);

    return ans;
  }
};