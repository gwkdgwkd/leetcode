// 快慢指针
struct ListNode* middleNode(struct ListNode* head) {
  // 寻找链表中点的一个重要作用是对链表进行归并排序。
  // 回想数组的归并排序：求中点索引递归地把数组二分，最后合并两个有序数组。对于链表，合并两个有序链表是很简单的，难点就在于二分。
  struct ListNode* fast = head;
  struct ListNode* slow = head;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  // 当链表的长度是奇数时，slow恰巧停在中点位置；如果长度是偶数，slow最终的位置是中间偏右。
  return slow;
}