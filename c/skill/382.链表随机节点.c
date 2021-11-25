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
  int randomNum = rand() % len;  // 产生0 ～ len - 1的随机数
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