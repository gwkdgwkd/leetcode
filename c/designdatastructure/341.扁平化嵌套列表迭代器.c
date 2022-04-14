/*
给你一个嵌套的整数列表nestedList。
每个元素要么是一个整数，要么是一个列表；该列表的元素也可能是整数或者是其他列表。
请你实现一个迭代器将其扁平化，使之能够遍历这个列表中的所有整数。
实现扁平迭代器类NestedIterator：
NestedIterator(List<NestedInteger> nestedList)用嵌套列表nestedList初始化迭代器。
int next()返回嵌套列表的下一个整数。
boolean hasNext()如果仍然存在待迭代的整数，返回true；否则，返回false。
你的代码将会用下述伪代码检测：
initialize iterator with nestedList
res = []
while iterator.hasNext()
    append iterator.next() to the end of res
return res
如果res与预期的扁平化列表匹配，那么你的代码将会被判为正确。

示例1：
输入：nestedList = [[1,1],2,[1,1]]
输出：[1,1,2,1,1]
解释：通过重复调用next直到hasNext返回false，next返回的元素的顺序应该是:[1,1,2,1,1]。

示例2：
输入：nestedList = [1,[4,[6]]]
输出：[1,4,6]
解释：通过重复调用next直到hasNext返回false，next返回的元素的顺序应该是:[1,4,6]。

提示：
1 <= nestedList.length <= 500
嵌套列表中的整数值在范围[-106, 106]内
*/

struct NestedIterator {
  int *vals;
  int size;
  int cur;
};
void dfs(struct NestedIterator *iter, struct NestedInteger **nestedList,
         int nestedListSize) {
  for (int i = 0; i < nestedListSize; i++) {
    if (NestedIntegerIsInteger(nestedList[i])) {
      (iter->vals)[(iter->size)++] = NestedIntegerGetInteger(nestedList[i]);
    } else {
      dfs(iter, NestedIntegerGetList(nestedList[i]),
          NestedIntegerGetListSize(nestedList[i]));
    }
  }
}
struct NestedIterator *nestedIterCreate(struct NestedInteger **nestedList,
                                        int nestedListSize) {
  struct NestedIterator *ret = malloc(sizeof(struct NestedIterator));
  ret->vals = malloc(sizeof(int) * 20001);
  ret->size = 0;
  ret->cur = 0;
  dfs(ret, nestedList, nestedListSize);
  return ret;
}
bool nestedIterHasNext(struct NestedIterator *iter) {
  return iter->cur != iter->size;
}
int nestedIterNext(struct NestedIterator *iter) {
  return (iter->vals)[(iter->cur)++];
}
void nestedIterFree(struct NestedIterator *iter) {
  free(iter->vals);
  free(iter);
}