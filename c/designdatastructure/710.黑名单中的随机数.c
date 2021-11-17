typedef struct {
  int key;
  int pos;
  UT_hash_handle hh;
} BlackHashData;

typedef struct {
  BlackHashData *data;
  int dataLen;
  int *nums;
  int numsLen;
} Solution;

Solution *solutionCreate(int n, int *blacklist, int blacklistSize) {
  Solution *obj = (Solution *)malloc(sizeof(Solution));
  obj->data = NULL;
  obj->dataLen = blacklistSize;
  obj->nums = (int *)malloc(sizeof(int) * n);
  obj->numsLen = n;

  for (int i = 0; i < blacklistSize; i++) {
    BlackHashData *b = (BlackHashData *)malloc(sizeof(BlackHashData));
    b->key = blacklist[i];
    b->pos = blacklist[i];
    HASH_ADD_INT(obj->data, key, b);
  }

  int sz = n - blacklistSize;
  int last = n - 1;
  for (int i = 0; i < blacklistSize; i++) {
    if (blacklist[i] >= sz) {
      continue;
    }
    BlackHashData *b = NULL;
    HASH_FIND_INT(obj->data, &blacklist[i], b);
    BlackHashData *s = NULL;
    HASH_FIND_INT(obj->data, &last, s);
    while (s != NULL) {
      last--;
      HASH_FIND_INT(obj->data, &last, s);
    }
    b->pos = last;
    last--;
  }
  return obj;
}

int solutionPick(Solution *obj) {
  int sz = obj->numsLen - obj->dataLen;
  int index = rand() % sz;
  BlackHashData *b = NULL;
  HASH_FIND_INT(obj->data, &index, b);
  if (b != NULL) {
    return b->pos;
  }
  return index;
}

void solutionFree(Solution *obj) {
  BlackHashData *s = NULL;
  BlackHashData *tmp = NULL;
  free(obj->nums);
  HASH_ITER(hh, obj->data, s, tmp) {
    HASH_DEL(obj->data, s);
    free(s);
  }
  free(obj);
}
