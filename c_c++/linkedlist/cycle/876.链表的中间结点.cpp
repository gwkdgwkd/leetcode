/*
给定一个头结点为head的非空单链表，返回链表的中间结点。
如果有两个中间结点，则返回第二个中间结点。

示例1：
输入：[1,2,3,4,5]
输出：此列表中的结点3(序列化形式：[3,4,5])
返回的结点值为3。(测评系统对该结点序列化表述是[3,4,5])。
注意，我们返回了一个ListNode类型的对象ans，这样：
ans.val = 3,ans.next.val = 4,ans.next.next.val = 5,
以及ans.next.next.next = NULL.

示例2：
输入：[1,2,3,4,5,6]
输出：此列表中的结点4(序列化形式：[4,5,6])
由于该列表有两个中间结点，值分别为3和4，我们返回第二个结点。

提示：给定链表的结点数介于1和100之间。
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

// 快慢指针
struct ListNode* middleNode(struct ListNode* head) {
  // 寻找链表中点的一个重要作用是对链表进行归并排序。
  // 回想数组的归并排序：
  // 求中点索引递归地把数组二分，最后合并两个有序数组。
  // 对于链表，合并两个有序链表是很简单的，难点就在于二分。
  struct ListNode* fast = head;
  struct ListNode* slow = head;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  // 当链表的长度是奇数时，slow恰巧停在中点位置；
  // 如果长度是偶数，slow最终的位置是中间偏右。
  return slow;
}

class Solution {
 public:
  ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    return slow;
  }
};