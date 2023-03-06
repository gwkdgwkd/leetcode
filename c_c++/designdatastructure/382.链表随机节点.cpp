/*
一个单链表，随机选择链表的一个节点，并返回相应的节点值，每个节点被选中的概率一样。
实现Solution类：Solution(ListNode head)使用整数数组初始化对象。
int getRandom()从链表中随机选择一个节点并返回该节点的值。
链表中所有节点被选中的概率相等。

示例：
输入
["Solution", "getRandom", "getRandom",
 "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
输出
[null, 1, 3, 2, 2, 3]

解释
Solution solution = new Solution([1, 2, 3]);
solution.getRandom(); // 返回1
solution.getRandom(); // 返回3
solution.getRandom(); // 返回2
solution.getRandom(); // 返回2
solution.getRandom(); // 返回3
getRandom()方法应随机返回1、2、3中的一个，每个元素被返回的概率相等。

提示：
链表中的节点数在范围[1, 10^4]内
-10^4 <= Node.val <= 10^4
至多调用getRandom方法10^4次

进阶：
如果链表非常大且长度未知，该怎么处理？
你能否在不使用额外空间的情况下解决此问题？
*/

typedef struct SNode {
  struct ListNode* head;
  int length;
} Solution;
Solution* solutionCreate(struct ListNode* head) {
  Solution* slt = malloc(sizeof(struct SNode));
  slt->head = head;
  slt->length = 0;
  while (head) {
    (slt->length)++;
    head = head->next;
  }
  return slt;
}
int solutionGetRandom(Solution* obj) {
  if (!obj->head) return -1;

  int len = obj->length;
  int randomNum = rand() % len;  // 产生0～len-1的随机数
  struct ListNode* ptr = obj->head;
  for (int i = 0; i < randomNum && ptr; i++) {
    ptr = ptr->next;
  }
  return ptr->val;
}
void solutionFree(Solution* obj) {
  obj->length = 0;
  obj->head = NULL;
}

class Solution {
  vector<int> arr;

 public:
  Solution(ListNode* head) {
    while (head) {
      arr.emplace_back(head->val);
      head = head->next;
    }
  }

  int getRandom() { return arr[rand() % arr.size()]; }
};

// 水塘抽样
// 对一个数量未知的样本，希望只经过一次遍历就完成随机抽样，即时间复杂度O(n)。
// 因为样本数量未知，因此就不能通过random函数直接随机抽样。
// 算法：
// 希望在n个样本中随机抽取k个数据，即每个数据被抽取的概率为k/n。
// 首先创建一个k个成员的数组out，用来存放预期抽出的样本。
// 1.当k>=n时，每一个样本被抽取的概率都为100%，因此都可以直接放入数组out。
// 2.当k<n时，对于第n个样本，希望其被抽取的概率为k/n，
//   因此需要设计出k/n的概率将其放入数组out，创建一个0-n之间的随机数，
//   判断其大于k的概率就是k/n，同时out中会有一个数据会被踢出。
// 3.当k<n时，对于数组out中已存的数据，其在上一轮被留下的概率为k/(n-1)，
//   这一轮发生不抽样的概率(n-k)/n，发生抽样的概率为k/n，
//   发生抽样不被抽走的概率为(k-1)/k，因此其被抽取的概率为也为k/n：
//   上一轮抽中的概率 * （不发生抽样的概率 + 发生抽样的概率 * 不被抽走的概率）
//   k/(n-1) * ((n-k)/n + k/n * (k-1)/k) = k/n
class Solution {
  ListNode* head;

 public:
  Solution(ListNode* head) { this->head = head; }
  int getRandom() {
    int i = 1, ans = 0;
    // 从链表头开始遍历整个链表，对第i个节点，随机选择区间[0,i)内的一个整数，
    // 如果其等于0，则将答案置为该节点值，否则答案不变。
    // 该算法会保证每个节点的值成为最后被返回的值的概率均为1/n：
    for (auto node = head; node; node = node->next) {
      if (rand() % i == 0) {  // 1/i的概率选中（替换为答案）
        ans = node->val;
      }
      ++i;
    }
    return ans;
  }
};
