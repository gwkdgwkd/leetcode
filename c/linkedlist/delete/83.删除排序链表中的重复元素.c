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