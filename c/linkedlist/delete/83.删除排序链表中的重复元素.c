/*
给定一个已排序的链表的头head，删除所有重复的元素，使每个元素只出现一次。返回已排序的链表。

示例1：
输入：head = [1,1,2]
输出：[1,2]

示例2：
输入：head = [1,1,2,3,3]
输出：[1,2,3]

提示：
链表中节点数目在范围[0, 300]内
-100 <= Node.val <= 100
题目数据保证链表已经按升序排列
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

// 双指针，与26题相同，只不过由数组变成了链表
struct ListNode* deleteDuplicates(struct ListNode* head) {
  if (!head) return head;
  struct ListNode* fast = head;
  struct ListNode* slow = head;
  while (fast) {
    if (fast->val != slow->val) {
      slow->next = fast;  // nums[slow] = nums[fast];
      slow = slow->next;  // slow++;
    }
    fast = fast->next;  // fast++
  }

  slow->next = NULL;  // 断开与后面重复元素的连接
  return head;
}

// 面试题0201移除重复节点
// 编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。
// 进阶：如果不得使用临时缓冲区，该怎么解决？
struct ListNode* removeDuplicateNodes(struct ListNode* head) {
  struct ListNode* h1 = head;
  while (h1) {
    struct ListNode* h2 = h1;
    while (h2->next) {
      if (h2->next->val == h1->val) {
        h2->next = h2->next->next;
      } else {
        h2 = h2->next;
      }
    }
    h1 = h1->next;
  }
  return head;
