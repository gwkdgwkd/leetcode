/*
给你一个长度为n的链表，每个节点包含一个额外增加的随机指针random，
该指针可以指向链表中的任何节点或空节点。
构造这个链表的深拷贝。
深拷贝应该正好由n个全新节点组成，其中每个新节点的值都设为其对应的原节点的值。
新节点的next指针和random指针也都应指向复制链表中的新节点，
并使原链表和复制链表中的这些指针能够表示相同的链表状态。
复制链表中的指针都不应指向原链表中的节点。
例如，如果原链表中有X和Y两个节点，其中X.random --> Y。
那么在复制链表中对应的两个节点x和y，同样有x.random --> y。
返回复制链表的头节点。
用一个由n个节点组成的链表来表示输入/输出中的链表。
每个节点用一个[val, random_index]表示：
val：一个表示Node.val的整数。
random_index：随机指针指向的节点索引（范围从0到n-1）；
如果不指向任何节点，则为null。
你的代码只接受原链表的头节点head作为传入参数。

示例1：
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

示例2：
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]

示例3：
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]

提示：
0 <= n <= 1000
-10^4 <= Node.val <= 10^4
Node.random为null或指向链表中的节点。
*/

// 剑指Offer35复杂链表的复制

// 回溯 + 哈希表
// 时间复杂度：O(n)
// 空间复杂度：O(n)
struct HashTable {
  struct Node *key, *val;
  UT_hash_handle hh;
} * cachedNode;
struct Node* deepCopy(struct Node* head) {
  if (head == NULL) {
    return NULL;
  }
  struct HashTable* tmp;
  HASH_FIND_PTR(cachedNode, &head, tmp);
  if (tmp == NULL) {
    struct Node* headNew = malloc(sizeof(struct Node));
    headNew->val = head->val;
    tmp = malloc(sizeof(struct HashTable));
    tmp->key = head, tmp->val = headNew;
    HASH_ADD_PTR(cachedNode, key, tmp);
    headNew->next = deepCopy(head->next);
    headNew->random = deepCopy(head->random);
  }
  return tmp->val;
}
struct Node* copyRandomList(struct Node* head) {
  cachedNode = NULL;
  return deepCopy(head);
}

// 迭代 + 节点拆分
// 时间复杂度：O(n)
// 空间复杂度：O(1)
struct Node* copyRandomList(struct Node* head) {
  if (head == NULL) {
    return NULL;
  }
  for (struct Node* node = head; node != NULL; node = node->next->next) {
    struct Node* nodeNew = malloc(sizeof(struct Node));
    nodeNew->val = node->val;
    nodeNew->next = node->next;
    node->next = nodeNew;
  }
  for (struct Node* node = head; node != NULL; node = node->next->next) {
    struct Node* nodeNew = node->next;
    nodeNew->random = (node->random != NULL) ? node->random->next : NULL;
  }
  struct Node* headNew = head->next;
  for (struct Node* node = head; node != NULL; node = node->next) {
    struct Node* nodeNew = node->next;
    node->next = node->next->next;
    nodeNew->next = (nodeNew->next != NULL) ? nodeNew->next->next : NULL;
  }
  return headNew;
}

class Node {
 public:
  int val;
  Node* next;
  Node* random;

  Node(int _val) {
    val = _val;
    next = nullptr;
    random = nullptr;
  }
};
class Solution {
 public:
  Node* copyRandomList(Node* head) {
    if (head == nullptr) return nullptr;

    Node* cur = head;
    // 1.复制各节点，并构建拼接链表
    while (cur != nullptr) {
      Node* tmp = new Node(cur->val);
      tmp->next = cur->next;
      cur->next = tmp;
      cur = tmp->next;
    }
    // 2.构建各新节点的random指向
    cur = head;
    while (cur != nullptr) {
      if (cur->random != nullptr) cur->next->random = cur->random->next;
      cur = cur->next->next;
    }
    // 3.拆分两链表
    cur = head->next;
    Node *pre = head, *res = head->next;
    while (cur->next != nullptr) {
      pre->next = pre->next->next;
      cur->next = cur->next->next;
      pre = pre->next;
      cur = cur->next;
    }
    pre->next = nullptr;  // 单独处理原链表尾节点
    return res;           // 返回新链表头节点
  }
};